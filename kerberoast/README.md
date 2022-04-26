# Kerberoast

This modules identifies executes the Kerberoast attack based on the work of Tim Medin. It identifies SPNs mapped to user accounts and requests Kerberos tickets for the service associated with the SPN. This module does not perform cracking as that is exteremly resource intensive.

## Credits and References

Author: Tim Medin / RedSiege 

## Installation

Please reference our module [installation guide](https://github.com/scythe-io/community-modules/wiki) on the wiki.

##  Manual

```
usage: kerberoast [-h] [-u USERNAME] [-p PASSWORD] [-c 1.1.1.1] [--display]
                  [--discover]
This module finds SPNs and then requests tickets for each user SPN
optional arguments:
  -h, --help            show this help message and exit
  -u USERNAME, --username USERNAME
                        User to authenticate as (do not prefix with domain).
                        If not provided the current user context will be used
  -p PASSWORD, --password PASSWORD
                        Password of user to authenticate as
  -c 1.1.1.1, --dc 1.1.1.1
                        IP address of domain controller. If not provided the
                        DC will be be lookedup
  --display             Display tickets after requesting.
  --discover            Discovery only. Find the SPNs, don't request the
                        tickets.
```

## FAQ:

No questions yet!
