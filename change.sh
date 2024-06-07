#!/bin/bash
#@tyro436
#@ITACHIUCHIHASENSEI

# Define variables
variable=$(dropbear -V 2>&1) 
number=$(echo "$variable" | grep -oE '[0-9]+([.][0-9]+)?') 
DV=$(echo "$variable" | awk '{print $2}' | cut -c2-)
echo "$DV"
DROPBEAR_URL="https://matt.ucc.asn.au/dropbear/releases/dropbear-$DV.tar.bz2"  # Replace with actual URL
DROPBEAR_TAR="dropbear.tar.bz2"
DROPBEAR_FOLDER="dropbear-$DV"
DROPBEAR_BINARY="dropbear"
SYSOPTIONS_FILE="sysoptions.h"
#NEW_DROPBEAR_VERSION=" <b><i><font color='red'>WELCOME TO NETWORK TWEAKER</font></b> "
echo "Enter banner:"
read NEW_DROPBEAR_VERSION

# Add spaces around the input
NEW_DROPBEAR_VERSION=" $NEW_DROPBEAR_VERSION "

# Download Dropbear tar file
wget "$DROPBEAR_URL" -O "$DROPBEAR_TAR"

# Extract Dropbear tar file
tar -jxvf "$DROPBEAR_TAR"

# Navigate into the extracted folder
cd "$DROPBEAR_FOLDER"
sudo sed -i "s@^#define DROPBEAR_VERSION \".*\"@#define DROPBEAR_VERSION \"$NEW_DROPBEAR_VERSION\"@" "$SYSOPTIONS_FILE"
sudo sed -i "s/\"SSH-2.0-dropbear_\" DROPBEAR_VERSION/\"SSH-2.0 \" DROPBEAR_VERSION/" "$SYSOPTIONS_FILE"

# Configure Dropbear
./configure

# Make Dropbear
make

sudo systemctl stop dropbear 
# Move Dropbear binary to /usr/sbin with sudo
sudo mv "$DROPBEAR_BINARY" /usr/sbin/

# Change permissions to 777 on the binary
sudo chmod 777 "/usr/sbin/$DROPBEAR_BINARY"

sudo systemctl restart dropbear