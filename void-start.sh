CYAN="\033[0;96m"
WHT="\033[0;97m"
CLR="\033[0m"
OS=$(cat /etc/os-release | grep 'PRETTY_NAME' | sed -e "s/^.*=//g" -e 's/"//g')
echo -en "This is a setup for your current OS: $(CYAN)$OS$(CLR).\n$(WHT)$(uname -s)$(CLR) version: $(CYAN)$(uname -r)$(CLR)\n"

chmod +x {alias,stuff-move,osd,tmux-conf}.sh

#alias
echo -en "$(CYAN)Setting alias...$(CLR)\n"
./alias.sh > /dev/null 2>&1  

#installing
echo -en "$(CYAN)Installing programs, cozy up...$(CLR)\n"
if [ $1 == "void" ]; then
  sudo xbps-install wget tmux pavucontrol time ncurses-libtinfo-devel libselinux-devel fzf fcft libX11 libX11-devel dhcpcd unzip zip firefox thunderbird leafpad i3 i3-status xorg dmenu xfce4-terminal alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin eog gnome-calculator -y > /dev/null 2>&1
else
  sudo apt install tmux wget time fzf firefox xfce4-terminal alacritty virtualbox-ose virtualbox-ose-dkms clementine vlc dolphin -y > /dev/null 2>&1
fi

#moving some stuff
./stuff-move.sh

#creating fonts directory if doesn't exist
if [ ! -d /usr/share/fonts ]; then
  sudo mkdir /usr/share/fonts
fi

#getting obsidian
./osd.sh

#creating folders
echo -en "$(CYAN)Creating folders...$(CLR)\n"
directories="Downloads Documents Desktop Pictures Videos"
for dir in $directories; do
        if [ ! -d ~/$dir ]; then
                mkdir ~/$dir
        fi
done

#i3
echo -en "$(CYAN)Configuring i3...$(CLR)\n"
yes | sudo mv i3_stuff/i3status.conf /etc/i3status.conf
cat i3_stuff/i3_conf_extra >> ~/.config/i3/config

#setting .xinitrc and .Xresources
if [ $1 == "void" ]; then
  echo -en "$(CYAN)Configuring .xinitrc and .Xresources...$(CLR)\n"
  echo -en "exec i3\nxrdb -merge .Xresources\nsource .bashrc" >> ~/.xinitrc
  echo -en "Xft.dpi: 196\nXcursor.theme: Adwaita\nXcursor.size: 32" >> ~/.Xresources
fi

#configuring tmux
./tmux-conf.sh

#cleaning
./clean.sh

echo -en "$(CYAN)Ready!$(CLR)\n"
