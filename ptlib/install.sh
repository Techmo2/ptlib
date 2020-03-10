#!/bin/bash
LIB_FILE_OLD=/usr/local/lib/libpt.so
LIB_FILE_NEW=./libpt.so

if [[ -f "$LIB_FILE_OLD" ]]; then
        echo "Removing old installation"
        sudo rm -f /usr/local/lib/libpt.so
fi

if [[ -f "$LIB_FILE_NEW" ]]; then
        echo "Copying new installation"
        sudo mv -n libpt.so /usr/local/lib/libpt.so
        sudo ldconfig
else
        echo "Could not find libpt.so. Please run make before installing."
fi



