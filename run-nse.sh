#!/bin/bash

# script by deep-ping

if [ $# -ne 3 ]; then
    echo "usage:"
    echo "run-nse.sh <ip> <port> <key>"
    echo "run-nse.sh 10.11.1.223 135,139,445 smb"
    exit 1
fi

targ=$1
port=$2
key=$3

echo TARG=$targ
echo PORT=$port
echo KEY=$key

ls /usr/share/nmap/scripts/ | grep $key |
while read line
do
    #echo line=$line
    read -p "Scan with $line? " -n 1 -r </dev/tty
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        nmap -v -Pn -p $port $targ --script $line 2>&1 | tee nse-$line-$targ.txt
    fi
done
