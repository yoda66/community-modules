# LNS

LNS is a native Scythe module written in C that performs simple TCP connect scan of the specified hosts and ports

## Credits and References

Author: GRIMM

## Installation

Please reference our module [installation guide](https://github.com/scythe-io/community-modules/wiki) on the wiki.

##  Manual

```
usage: grimm.lns [-h] --hosts HOSTS) (--connect [--ports PORTS]
Network Scanning and Enumeration
optional arguments:
  -h, --help     show this help message and exit
  --hosts HOSTS  Comma seperated list of IP addresses to scan e.g. --hosts
                 192.168.1.1,10.10.10.1,10.10.10.2
  --connect      Perform a TCP connect scan
  --ports PORTS  Comma seperated list of ports to scan e.g. --ports
                 23,22,80,139,443,445,3389
grimm.lns --connect --hosts 192.168.1.1,10.10.10.1,10.10.10.2 --ports
23,22,80,139,443,445,3389
```

## FAQ:

No questions yet!
