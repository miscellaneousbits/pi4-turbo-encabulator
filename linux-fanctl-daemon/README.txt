To build and install the fanmon daemon under Raspbian:

sudo make install

sudo cp fanmon.service /etc/systemd/system

sudo systemctl enable fanmon.service
sudo systemctl start fanmon.service
