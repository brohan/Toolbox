#!/usr/bin/python

import sys
import smtplib

if len(sys.argv) !=3:
    print "Usage: smpt_user_enum <server file> <username file>"
    sys.exit(0)

print "Welcome to the smtp user verify script"
print "This can take a few seconds to connect to each server, please wait"

with open(sys.argv[1]) as server:
    for addy in server:
        try:
            #iterate over list conecting to server
            print addy
            server = smtplib.SMTP(addy)
            server.set_debuglevel(True)
            with open(sys.argv[2]) as username:
                try:
                    #iterate over names to verify
                    for name in username:
                        print name
                        server.verify(name)
                except:
                    print "Something went awry with username VRFY"
                    #no continue here, if server doesn't reply, no need to try another name
        except:
            print "Something went awry in the server connection, possible timeout"
            continue
