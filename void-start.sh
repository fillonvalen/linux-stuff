cat alias > ~/.bash_aliases
cat void-alias >> ~/.bash_aliases

sudo xbps-install time fzf wget libX11 libX11-devel dhcpcd unzip zip firefox leafpad dwm st alacritty virtualbox-ose virtualbox-dkms clementine vlc dolphin dmenu eog gnome-calculator -y

mv -v pinc/* /usr/include/
rm -rv pinc/ 
mv -v {pi,gl_notes} ~
cd ~

rm -rf linux-blog
sudo xbps-remove -yoO

git clone https://github.com/shannpersand/comic-shanns && mv comic-shanns/v2/*.ttf /usr/share/fonts/
wget https://github.com/obsidianmd/obsidian-releases/releases/download/v1.12.7/Obsidian-1.12.7.AppImage

mkdir -v Downloads Documents Pictures Videos
mv -v Obsidian-1.12.7.AppImage Desktop/Obsidian
fc-cache -f
