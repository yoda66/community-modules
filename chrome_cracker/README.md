# Chrome Cracker

Chrome Cracker nicknamed DeSpell, is a password cracker for Google Chromes locally stored passwords. It will look for three files; chrome.exe, Local State, and Login Data. Chrome.exe just ensures that Chrome is present, Local state hosts the encrypted BLOB key, and Login Data is the database file that hosts the usernames, URLS, and encrypted passwords that Chrome stores locally.

## Credits and References

Author: SCYTHE

Additional credits and references:
* Chrome Cracker was developed by Brandon Dupree for SCYTHE.

## Installation

Please reference our module [installation guide](https://github.com/scythe-io/community-modules/wiki) on the wiki.

##  Manual

```
usage: despell [-h]

Returns Usernames, Passwords, and Websites

optional arguments:
  -h, --help  show this help message and exit

scythe.despell
```

## FAQ:

No questions yet!
