sudo apt update
sudo apt install make gcc libx11-dev libxft-dev libxinerama-dev xorg flameshot xfce4-appfinder tty-clock feh picom neofetch cmatrix
cd dwm
sudo make clean install

cd ..
cd dmenu
sudo make clean install

cd ..
cd st
sudo make clean install

cd .. && cd ..
echo "exec dwm" >> ~/.xinitrc
mv picom.conf /home/$USER/.config/

clear
echo "
  _______          ____  __   _       _____           _        _ _          _                    
 |  __ \ \        / /  \/  | (_)     |_   _|         | |      | | |        | |                   
 | |  | \ \  /\  / /| \  / |  _ ___    | |  _ __  ___| |_ __ _| | | ___  __| |                   
 | |  | |\ \/  \/ / | |\/| | | / __|   | | | '_ \/ __| __/ _` | | |/ _ \/ _` |                   
 | |__| | \  /\  /  | |  | | | \__ \  _| |_| | | \__ \ || (_| | | |  __/ (_| |                   
 |_____/_  \/  \/   |_|  |_| |_|___/ |_____|_| |_|___/\__\__,_|_|_|\___|\__,_|             _     
 |__   __|                   | |           | |        | |        | |                      | |    
    | |_   _ _ __   ___   ___| |_ __ _ _ __| |___  __ | |_ ___   | | __ _ _   _ _ __   ___| |__  
    | | | | | '_ \ / _ \ / __| __/ _` | '__| __\ \/ / | __/ _ \  | |/ _` | | | | '_ \ / __| '_ \ 
    | | |_| | |_) |  __/ \__ \ || (_| | |  | |_ >  <  | || (_) | | | (_| | |_| | | | | (__| | | |
    |_|\__, | .__/ \___| |___/\__\__,_|_|   \__/_/\_\  \__\___/  |_|\__,_|\__,_|_| |_|\___|_| |_|
        __/ | |                                                                                  
       |___/|_|                                                                                  "
