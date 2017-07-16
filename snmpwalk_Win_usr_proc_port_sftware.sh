#!/bin/bash

if [ $# -eq 0]
	then
		echo "This script requires a file with IP's to run against"
fi

for ip in $1
do
	echo $ip
	echo Windows Users;echo
	snmpwalk -c public $1 -v1 1.3.6.1.4.1.77.1.2.25 | cut -d":" -f2 | cut -d'"' -f2
	echo;echo Windows Processes;echo
	snmpwalk -c public $1 -v1 1.3.6.1.2.1.25.4.2.1.2 | cut -d":" -f2 | cut -d'"' -f2
	echo;echo Windows Open TCP Ports;echo
	snmpwalk -c public $1 -v1 1.3.6.1.2.1.6.13.1.3 | cut -d":" -f2 | cut -d'"' -f2
	echo;echo Windows Installed Software;echo
	snmpwalk -c public $1 -v1 1.3.6.1.2.1.25.6.3.1.2
done

