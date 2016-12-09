#!/bin/bash
set -eu

cd ~

# Check bash files
if [ -f .bash_profile ]; then
    echo "Use existed .bash_profile"
else
    touch .bash_profile
    chmod 644 .bash_profile
    echo "Created .bash_profile"
fi

if [ -f .bashrc ]; then
    echo "Use existed .bashrc" 
else
    touch .bashrc
    chmod 644 .bashrc
    echo "Created .bashrc"
fi

# Install Homebrew and commands
./installbrew.sh

# Install applications by homebrew-cask
./installapps.sh

# Install anyenv
./installanyenv.sh

# Set configration
./setbash.sh $1 $2
