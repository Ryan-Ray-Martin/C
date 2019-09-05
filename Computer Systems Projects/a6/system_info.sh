// Author: Ryan Martin
// Date: 3/16/2019
// Dr. Slaughter
// CS 5007


#!/bin/bash

clear

#number of cores
echo "Number of cores:"
nproc --all
echo

#Showing free memory
echo "Memory:"
echo "free:" $(free -m | grep "Mem" | awk '{print $4}') "GB"
echo "total:" $(free -m | grep "Mem" | awk '{print $2}') "GB"
echo

#disk space
echo "Primary Partition Storage:"
df -h --output=size /dev/sda1
df -h --output=avail /dev/sda1
echo
