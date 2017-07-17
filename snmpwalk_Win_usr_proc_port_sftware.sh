#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "This script requires a file with IP's to run against"
fi

cat $1 | while read line
do
	echo $line
	echo Windows Users;echo
	snmpwalk -c public $line -v1 1.3.6.1.4.1.77.1.2.25 | cut -d":" -f2 | cut -d'"' -f2
	echo;echo Windows Processes;echo
	snmpwalk -c public $line -v1 1.3.6.1.2.1.25.4.2.1.2 | cut -d":" -f2 | cut -d'"' -f2
	echo;echo Windows Open TCP Ports;echo
	snmpwalk -c public $line -v1 1.3.6.1.2.1.6.13.1.3 | cut -d":" -f2 | cut -d'"' -f2
	echo;echo Windows Installed Software;echo
	snmpwalk -c public $line -v1 1.3.6.1.2.1.25.6.3.1.2
done

