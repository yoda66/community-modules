# GCP

Enumerate member permissions, retrieve access token, or issue CLI commands. Assumes CLI from gcloud sdk is preinstalled on device.

## Credits and References

Author: SCYTHE

## Installation

Please reference our module [installation guide](https://github.com/scythe-io/community-modules/wiki) on the wiki.

##  Manual

```
usage: gcp [-h]
           (--cli ... | --print-access-token | --enumerate-permissions ENUMERATE_PERMISSIONS)
           [--token TOKEN]

Enumerate member permissions, retrieve access token, or issue CLI commands.
Assumes CLI from gcloud sdk is preinstalled on device.

optional arguments:
  -h, --help            show this help message and exit
  --cli ...             Use gcloud cli on device to process remaining
                        arguments
  --print-access-token  Retrieve access token
  --enumerate-permissions ENUMERATE_PERMISSIONS
                        Enumerate permissions for a project id
  --token TOKEN         token to use for --enumerate-permissions

Example: scythe.gcp --enumerate-permissions monkey-magic-1129
```

## FAQ:

No questions yet!
