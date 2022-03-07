# JXA Loader

Execute arbitrary JavaScript for Automation on a macOS target. 

To run a script already present on the target macOS. 
```bash
loader --load scythe.jxa_loader
scythe.jxa_loader --filename "Absolute Path to file"
```
or if you want to run a path from VFS. 
```bash
loader --load scythe.jxa_loader
scythe.jxa_loader --filename "VFS:/shared/<path>/<to>/<file>"
```
