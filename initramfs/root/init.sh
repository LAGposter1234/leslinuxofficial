#!/bin/bash
# Start any needed services here.
# We dont need any yet, so a shell
# is everything.

# Move scripts from non-persistent nerd root to persistent chad home directory

# Make sure the home directories exist
mkdir -p /home/root
mkdir -p /home/user

cp /root/init.sh /home/root/init.bash
cp /root/.bashrc /home/root/.bashrc
cp /root/* /home/root/

leslogin