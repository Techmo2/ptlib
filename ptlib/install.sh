#!/bin/bash
LIB_FILE_LOC=/usr/lib/libpt.so
LIB_FILE_NEW=./libpt.so

if [[ -f "$LIB_FILE_LOC" ]]; then
        echo "Removing old installation"
        sudo rm -f ${LIB_FILE_LOC}
fi

if [[ -f "$LIB_FILE_NEW" ]]; then
        echo "Copying new installation"
        sudo mv -n libpt.so ${LIB_FILE_LOC}
        sudo ldconfig
else
        echo "Could not find libpt.so. Please run make before installing."
fi



