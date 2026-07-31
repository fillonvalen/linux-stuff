CYAN="\033[0;96m"
CLR="\033[0m"

#alias
cat alias > ~/.bash_aliases
cat void-alias >> ~/.bash_aliases
source ~/.bash_aliases
echo "source ~/.bash_aliases" >> ~/.bashrc

#installing
echo -en "$(CYAN)Installing programs, cozy up...$(CLR)\n"
sudo xbps-install wget tmux pavucontrol time ncurses-libtinfo-devel libselinux-devel fzf fcft wget libX11 libX11-devel dhcpcd unzip zip firefox leafpad i3 i3-status xorg xfce4-terminal alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin dmenu eog gnome-calculator -y > /dev/null 2>&1

#moving some stuff
echo -en "$(CYAN)Moving and renaming stuff...$(CLR)\n"
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
echo -en "$(CYAN)Cleaning...$(CLR)\n"
rm -rf linux-stuff/
sudo xbps-remove -yoO > /dev/null 2>&1
find pi/ -name .gitkeep > /dev/null 2>&1 | xargs -I{} rm {}

#getting font and obsidian
if [ ! -d /usr/share/fonts ]; then
  sudo mkdir /usr/share/fonts
fi
echo -en "$(CYAN)Getting comic shanns...$(CLR)\n"
git clone https://github.com/shannpersand/comic-shanns > /dev/null 2>&1 && sudo mv comic-shanns/v2/*.ttf /usr/share/fonts/ && rm -rf comic-shanns && fc-cache -f
echo -en "$(CYAN)Getting Obsidian...$(CLR)\n"
wget https://github.com/obsidianmd/obsidian-releases/releases/download/v1.12.7/Obsidian-1.12.7.AppImage > /dev/null 2>&1

#creating folders
echo -en "$(CYAN)Creating folders...$(CLR)\n"
mkdir Desktop Downloads Documents Pictures Videos
mv Obsidian-1.12.7.AppImage Desktop/Obsidian
echo -en "$(CYAN)Ready!$(CLR)"

#setting .xinitrc and .Xresources
echo -en "$(CYAN)Configuring .xinitrc and .Xresources...$(CLR)"
echo -en "exec i3\nxrdb -merge .Xresources\nsource .bashrc" >> ~/.xinitrc
echo -en "Xft.dpi: 196\nXcursor.theme: Adwaita\nXcursor.size: 32" >> ~/.Xresources
