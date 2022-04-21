# Yarascan

The Yarascan module allows users to scan files and directories with Yara rules.

## Credits and References

Author: SCYTHE

##  Manual

```
usage: yarascan [-h] --rule RULE [--filename FILENAME] [--directory DIRECTORY]
                [--recurse RECURSE]

Echo the request back as response

optional arguments:
  -h, --help            show this help message and exit
  --rule RULE           Yara rule file which is currently located on your
                        SCYTHE VFS share.
  --filename FILENAME   The file you want to scan with the yara rule.
  --directory DIRECTORY
                        The directory you want to scan with the yara rule.
  --recurse RECURSE     Search directory recursively.

scythe.yarascan --rule "VFS:\yara_rule.yara --file file_to_scan.exe"
```

## FAQ:

No questions yet!