#alias
cat alias > ~/.bash_aliases
cat void-alias >> ~/.bash_aliases
source ~/.bash_aliases
echo "source ~/.bash_aliases" >> ~/.bashrc

#installing
echo -en "\033[0;96mInstalling programs, cozy up...\033[0m\n"
sudo xbps-install wget tmux time ncurses-libtinfo-devel libselinux-devel fzf fcft wget libX11 libX11-devel dhcpcd unzip zip firefox leafpad i3 i3-status xorg xfce4-terminal alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin dmenu eog gnome-calculator -y > /dev/null 2>&1

#moving some stuff
echo -en "\033[0;96mMoving and renaming stuff...\033[0m\n"
sudo mv pinc/* /usr/include/
mv pi ~
mv gl_notes ~
mkdir -p ~/.config/alacritty/
mv alacritty.toml ~/.config/alacritty/
sudo rm /usr/bin/vi
sudo mv vi /usr/bin/
sudo chmod +x /usr/bin/vi
cd ~
sudo cp ~/pi/pal/pcal /usr/bin/pal

#cleaning
echo -en "\033[0;96mCleaning...\033[0m\n"
rm -rf linux-stuff/
sudo xbps-remove -yoO > /dev/null 2>&1
find pi/ -name .gitkeep > /dev/null 2>&1 | xargs -I{} rm {}

#getting font and obsidian
if [ ! -d /usr/share/fonts ]; then
  sudo mkdir /usr/share/fonts
fi
echo -en "\033[0;96mGetting comic shanns...\033[0m\n"
git clone https://github.com/shannpersand/comic-shanns > /dev/null 2>&1 && sudo mv comic-shanns/v2/*.ttf /usr/share/fonts/ && rm -rf comic-shanns && fc-cache -f
echo -en "\033[0;96mGetting Obsidian...\033[0m\n"
wget https://github.com/obsidianmd/obsidian-releases/releases/download/v1.12.7/Obsidian-1.12.7.AppImage > /dev/null 2>&1

#creating folders
echo -en "\033[0;96mCreating folders...\033[0m\n"
mkdir Desktop Downloads Documents Pictures Videos
mv Obsidian-1.12.7.AppImage Desktop/Obsidian
echo -en "\033[0;96mReady!\033[0m"

