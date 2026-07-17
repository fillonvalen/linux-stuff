#alias
cat alias > ~/.bash_aliases
cat void-alias >> ~/.bash_aliases
source ~/.bash_aliases
echo "source ~/.bash_aliases" >> ~/.bashrc

#installing 
sudo xbps-install tmux time ncurses-libtinfo-devel libselinux-devel fzf fcft wget libX11 libX11-devel dhcpcd unzip zip firefox leafpad dwm st alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin dmenu eog gnome-calculator -y

#moving some stuff
mv -v pinc/* /usr/#alias
cat alias > ~/.bash_aliases
cat void-alias >> ~/.bash_aliases
source ~/.bash_aliases
echo "source ~/.bash_aliases" >> ~/.bashrc

#installing
echo -en "\033[0;96mInstalling programs, cozy up...\033[0m"
xbps-install wget tmux time ncurses-libtinfo-devel libselinux-devel fzf fcft wget libX11 libX11-devel dhcpcd unzip zip firefox leafpad dwm st alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin dmenu eog gnome-calculator -y > /dev/null 2>&1

#moving some stuff
echo -en "\033[0;96mMoving and renaming stuff...\033[0m"
mv -v pinc/* /usr/include/
mv -v {pi,gl_notes} ~
mkdir -p ~/.config/alacritty/
mv alacritty.toml ~/.config/alacritty/
rm /usr/bin/vi
mv vi /usr/bin/
chmod +x /usr/bin/
cd ~
cp ~/pi/pal/pcal /usr/bin/pal

#cleaning
echo -en "\033[0;96mCleaning...\033[0m"
rm -rf linux-stuff
xbps-remove -yoO
find ~/pi/ -name .gitkeep | xargs rm -v

#getting font and obsidian
mkdir -v /usr/share/fonts
echo -en "\033[0;96mGetting comic shanns...\033[0m"
git clone https://github.com/shannpersand/comic-shanns && mv comic-shanns/v2/*.ttf /usr/share/fonts/ && rm -rf comic-shanns && fc-cache -f
echo -en "\033[0;96mGetting Obsidian...\033[0m"
wget https://github.com/obsidianmd/obsidian-releases/releases/download/v1.12.7/Obsidian-1.12.7.AppImage

#creating folders
echo -en "\033[0;96mCreating folders\033[0m"
mkdir -v Desktop Downloads Documents Pictures Videos
mv -v Obsidian-1.12.7.AppImage Desktop/Obsidian/
mv -v {pi,gl_notes} ~
mkdir -p ~/.config/alacritty/
mv alacritty.toml ~/.config/alacritty/
mv vi /usr/bin/mvi
cd ~
sudo cp ~/pi/pal/pcal /usr/bin/pal

#cleaning
rm -rf linux-stuff
sudo xbps-remove -yoO
find ~/pi/ -name .gitkeep | xargs rm -v

#getting font and obsidian
mkdir -v /usr/share/fonts
git clone https://github.com/shannpersand/comic-shanns && mv comic-shanns/v2/*.ttf /usr/share/fonts/ && rm -rf comic-shanns && fc-cache -f
wget https://github.com/obsidianmd/obsidian-releases/releases/download/v1.12.7/Obsidian-1.12.7.AppImage

#creating folders
mkdir -v Downloads Documents Pictures Videos
mv -v Obsidian-1.12.7.AppImage Desktop/Obsidian
