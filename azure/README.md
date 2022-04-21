# Azure

This Azure module assumes the Azure CLI is pre-installed on the system and provides rudimentary validation functionality.

## Credits and References

Author: SCYTHE

## Installation

Please reference our module [installation guide](https://github.com/scythe-io/community-modules/wiki) on the wiki.

##  Manual

```
usage: azure [-h] [--createuser CREATEUSER] [--password PASSWORD]
             [--userprincipalname USERPRINCIPALNAME] [--deleteuser DELETEUSER]
             [--listvms] [--execvm EXECVM] [--command COMMAND] [--rg RG]
             [--cli CLI]

Run Azure cloud commands

optional arguments:
  -h, --help            show this help message and exit
  --createuser CREATEUSER
                        Username for the new user
  --password PASSWORD   Password of the user
  --userprincipalname USERPRINCIPALNAME
                        User Principal Name for the new user
  --deleteuser DELETEUSER
                        Username to delete
  --listvms             List all VMs
  --execvm EXECVM       Name of the vm to execute command on
  --command COMMAND     Command to execute on the vm
  --rg RG               Resource Group Name of the vm
  --cli CLI             Azure CLI (az.exe is prepended)

  scythe.azure --execvm test-vm --command whoami --rg test-rg
  scythe.azure --createuser testuser --password 1a2b3C4d5e6f! --userprincipalname testuser@gilgamesh.pw
  scythe.azure --cli "group list"
```

## FAQ:

No questions yet!
