# PHollowing

The Process Hollowing module replaces a target process with a new executable image stored on the Virtual File System (VF S) or local computer. This module currently supports native applications only.

## Credits and References

Author: SCYTHE

## Installation

Please reference our module [installation guide](https://github.com/scythe-io/community-modules/wiki) on the wiki.

##  Manual

```
usage: phollowing [-h] --target path --src path

Replace a target process with a new executable image stored on the Virtual File System (VFS) or local computer. Support is currently for native applications only.

optional arguments:
  -h, --help     show this help message and exit
  --target path  Filepath of the target executable that will be modified.
  --src path     Filepath of the source executable to replace target (Path can
                 also be a VFS Path). If the filesize of source executable is
                 too large, process hollowing may fail.

Examples:
  phollowing --target C:\Windows\System32\calc.exe --src VFS:/users/LOCAL/test/scythe_client.exe
  phollowing --target C:\Windows\System32\calc.exe --src C:\Users\scytheuser\scythe_client.exe
```

## FAQ:

No questions yet!
