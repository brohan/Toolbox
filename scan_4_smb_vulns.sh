#!/bin/bash

for host in $(cat smb_discovered.txt); do
	nmap $host --script "smb-vuln-*"
done 
