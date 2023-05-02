@echo off
pushd dist
set KABMAT_DATA_DIR=kabmat
set TERM=xterm-256color
set TERMINFO=terminfo
.\kabmat.exe
popd
