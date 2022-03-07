# Persist module on macOS

Persistence module for macOS, using Launch Agents. 

Loading the persistence module from the SCYTHE server shell. 

```bash
loader --load scythe.persist
```

## Scythe Persistent Implant

```
scythe.persist --command "/Users/<username>/Downloads/<implant-name>_scythe_client64.osx
```
## Notes & Warnings.

In order to remove persistence, the following command must be issued at the end of a campaign. 

```bash
loader --unload scythe.persist
```

If for some reason the implant is not shutdown properly, the agent will continue persisting. 

To manually remove the agent you can also run these commands from a shell.

First, we can check if the `com.scythe.persist.plist` is under `~/Library/LaunchAgents/`
```bash
ls ~/Library/LaunchAgents/
..
.
com.scythe.persist.plist
```
Next we can check to see if the `plist` is loaded by the `launch` daemon. 

```bash
launchctl list com.scythe.persist
```
If we get output, then we know that the `plist` is loaded into memory. 

We can now remove this by running two commands. 

```bash
rm -f  ~/Library/LaunchAgents/com.scythe.persist.plist
# This will remove the plist from being loaded into launchd on boot. 
launchtl remove com.persist.scythe
# This will unload the plist from the launch daemon. 
```
