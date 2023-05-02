# my setup has msys2 installed via scoop on windows
echo "Run this in a mingw shell"
set -x
pacman -S --needed gcc ncurses ncurses-devel
make clean
make -j8
mv kabmat.exe dist
set +x
echo "Can use .\\kabmat.bat now"
