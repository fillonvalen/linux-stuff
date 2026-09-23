# This is a file that I did 'cause I want to avoid doing all the same damn things every time I change the distro
# The user may add "void" as a parameter, but by default the operations will be made for mint, ubuntu or debian.

CYAN="\033[0;96m"
WHT="\033[0;97m"
CLR="\033[0m"
OS=$(cat /etc/os-release | grep 'PRETTY_NAME' | sed -e "s/^.*=//g" -e 's/"//g')

# Welcome message
echo -en "This is a setup for your current OS: $CYAN$OS$CLR\n$WHT$(uname -s)$CLR version: $CYAN$(uname -r)$CLR\n"

# Alias
echo -en "$CYAN--> Setting alias...$CLR\n"
cat alias/galias > ~/.bash_aliases
if [[ $1 == "void" ]]; then
  cat alias/void-alias >> ~/.bash_aliases
else 
  cat alias/apt-alias >> ~/.bash_aliases
fi
source ~/.bash_aliases
echo "source ~/.bash_aliases" >> ~/.bashrc

# Installing
echo -en "$CYAN--> Installing programs, cozy up...$CLR\n"
if [[ $1 == "void" ]]; then
  sudo xbps-install wget tmux pavucontrol time ncurses-libtinfo-devel libselinux-devel fzf fcft libX11 libX11-devel dhcpcd unzip zip firefox thunderbird leafpad i3 i3-status xorg dmenu xfce4-terminal alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin eog gnome-calculator -y > /dev/null 2>&1
else
  sudo apt install tmux wget time fzf firefox xfce4-terminal alacritty virtualbox virtualbox-dkms clementine vlc dolphin -y > /dev/null 2>&1
fi

# Moving some stuff
echo -en "$CYAN--> Moving and renaming stuff...$CLR\n"
sudo mv pinc/* /usr/include/
mv pi ~
mv gl_notes ~
mv vimrc ~/.vimrc
sudo rm /usr/bin/vi
sudo mv xs/vi /usr/bin/
sudo chmod +x /usr/bin/vi
sudo mv xs/pal /usr/bin/
sudo chmod +x /usr/bin/pal

# Creating fonts directory if doesn't exist
if [[ ! -d /usr/share/fonts ]]; then
  sudo mkdir /usr/share/fonts
fi

# Getting obsidian
echo -en "$CYAN--> Getting Obsidian...$CLR\n"
wget https://github.com/obsidianmd/obsidian-releases/releases/download/v1.12.7/Obsidian-1.12.7.AppImage > /dev/null 2>&1
sudo mv Obsidian-1.12.7.AppImage /bin/osd
sudo chmod +x /bin/osd

# Creating folders
echo -en "$CYAN--> Creating folders...$CLR\n"
directories="Downloads Documents Desktop Pictures Videos"
for dir in $directories; do
        if [[ ! -d ~/$dir ]]; then
                mkdir ~/$dir
        fi
done

# i3 (if we are talking about void)
if [[ $1 == "void" ]]; then
	echo -en "$CYAN--> Configuring i3...$CLR\n"
	yes | sudo mv i3_stuff/i3status.conf /etc/i3status.conf
	cat i3_stuff/i3_conf_extra >> ~/.config/i3/config
fi

# Setting .xinitrc and .Xresources (same as before)
if [[ $1 == "void" ]]; then
  echo -en "$CYANConfiguring .xinitrc and .Xresources...$CLR\n"
  echo -en "exec i3\nxrdb -merge .Xresources\nsource .bashrc" >> ~/.xinitrc
  echo -en "Xft.dpi: 196\nXcursor.theme: Adwaita\nXcursor.size: 32" >> ~/.Xresources
fi

# Configuring tmux
echo -en "$CYAN--> Configuring tmux...$CLR\n"
mv tmux.conf ~/.tmux.conf

# Cleaning
echo -en "$CYAN--> Cleaning...$CLR\n"
cd ~
rm -rf ~/linux-stuff/
if [[ $1 == "void" ]]; then
  sudo xbps-remove -yoO > /dev/null 2>&1
else
  apt autoremove -y > /dev/null 2>&1
fi

echo -en "$CYAN--> Ready!$CLR\n"
