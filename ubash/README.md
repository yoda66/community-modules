# Ubash

Run `bash` and `shell` scripts from memory without invoking `bash -c`. 

## To Run

```bash
loader --load scythe.ubash
scythe.ubash --filename "VFS:/users/BUILTIN/scythe/enum.sh
# You can also run inline shell commands;
scythe.ubash --filename "#!/bin/bash\n whoami\n ip a\n cat /etc/passwd\n"
```
