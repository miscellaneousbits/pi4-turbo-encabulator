#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-daemon.h>
#include <unistd.h>

#include "fan.h"
#include "log.h"
#include "temp.h"

static float high_temp_threshold = 78.0; // Target max. die temp
static float low_temp_threshold = 67.0;  // Fan start temp.
static volatile uint8_t running = 1u;    // Abort (CTL-C) flag
static int logLevel = 0;                 // Log verbosity

// Catch terminal events
static void ctlc_handler(int s)
{
    running = 0;
}

// display help to stdout
static void help(char* av)
{
    printf(
        "\nUsage:\n\n"
        "%s [-v loglevel] [-l lowTemp] [-h highTemp] \n\n"
        "  -v Set log verbosity. 0 - quiet (default), 1-chatty, 2-debug\n"
        "  -l Low temperature threshold in Celcius (default - %d)\n"
        "  -m High temperature threshold in Celcius (default - %d)\n\n",
        av, (int)low_temp_threshold, (int)high_temp_threshold);
}

// Use exponential smoothing
static uint8_t Average(float p)
{
    static float sum = 0;
    sum = (sum + sum + p) / 3;
    return sum;
}

// Run once per sampling interval process
static int process_interval(void)
{
    uint32_t temp = getTemp();
    // Get the temperature and set the fan speed
    if (temp == 0)
    {
        Log(LOG_ERR, "%sError retrieving temperature\n");
        return -1;
    }
    // Calculate new fan speed in the 0-127 range
    float p;
    if (temp <= low_temp_threshold)
        p = 0;
    else if (temp >= high_temp_threshold)
        p = 127;
    else
        p = ((temp - low_temp_threshold) * 127.0) /
            (high_temp_threshold - low_temp_threshold);
    // Apply smoothing
    uint8_t ap = Average(p);
    // Set the fan speed
    fanPower(ap);
    // Conditionally log the full status
    static uint8_t lastP = 0;
    // for verbosity >= 1, log fan on/off transitions
    if (logLevel > 0)
    {
        if ((lastP && !ap) || (!lastP && ap))
            Log(LOG_INFO, "Fan o%s\n", ap ? "n" : "ff");
        lastP = ap;
    }
    // for verbosity > 1, log die temp and fan rpm at every interval
    if (logLevel > 1)
        Log(LOG_INFO, "FAN %u% TEMP %u RPM %u\n", (ap * 128) / 100, temp,
            fanRPM());
    return 0;
}

int main(int ac, char* av[])
{
    const uint32_t poll_interval = 2;

    LogInit();

    // Parse parameters
    int opt;
    while ((opt = getopt(ac, av, "v:l:m:h")) != -1)
    {
        switch (opt)
        {
        case 'v':
            logLevel = atoi(optarg);
            break;
        case 'l':
            low_temp_threshold = atoi(optarg);
            break;
        case 'm':
            high_temp_threshold = atoi(optarg);
            break;
        case 'h':
            help(av[0]);
            exit(0);
        case ':':
            Log(LOG_ERR, "option needs a value\n");
            help(av[0]);
            goto error;
        case '?':
            Log(LOG_ERR, "unknown option: %c\n", optopt);
            help(av[0]);
            goto error;
        }
    }

    // Starting
    Log(LOG_INFO, "Fan control starting, log level %d\n", logLevel);

    // Intercept sigterm
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = ctlc_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    sigaction(SIGHUP, &sigIntHandler, NULL);
    sigaction(SIGSTOP, &sigIntHandler, NULL);
    sigaction(SIGTERM, &sigIntHandler, NULL);
    sigaction(SIGKILL, &sigIntHandler, NULL);

    // Initialize the library
    if (fanInit() < 0)
    {
        Log(LOG_ERR, "Must run as ROOT\n");
        errno = EPERM;
        goto error;
    }

    if (tempOpen() < 0)
    {
        Log(LOG_ERR, "Can't init temperature sensor\n");
        errno = EPERM;
        goto error;
    }

    // Inform systemd we've started
    sd_notify(0, "READY=1");

    // Poll forever
    for (; running;)
    {
        if (process_interval())
            goto error;
        sleep(poll_interval);
    }

    // Time to exit...
    fanClose();
    tempClose();
    Log(LOG_INFO, "Stopped\n");
    return 0;

error:
  // Exit with error.
  fanClose();
  tempClose();
  Log(LOG_ERR, "Stopped with error\n");
  sd_notifyf(0,
             "STATUS=Failed: %s\n"
             "ERRNO=%d",
             strerror(errno), errno);
  return -1;
}
