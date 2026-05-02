rem set "PATH=%PATH%;C:\TelinkIoTStudio\bin;C:\TelinkIoTStudio\opt\tc32\bin;C:\Program Files\Python3;C:\Program Files\Git\bin"
make clean
make bootloader -f makefile.bootloader
make clean
make -f makefile
pause
