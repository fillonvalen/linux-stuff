cat alias > ~/.bash_aliases
cat void-alias >> ~/.bash_aliases
sudo xbps-install -Su
sudo xbps-install libX11 libX11-devel dhcpcd unzip zip firefox leafpad dwm st alacritty virtualbox-ose virtualbox-dkms clementine vlc dolphin dmenu eog gnome-calculator
mv -v pinc/* /usr/include/
rm -rv pinc/ 
mv -v pi/ ~
mv -v gnu-linux_pi/ ~
cd ~
rm -rf linux-blog
sudo xbps-remove -yoO
