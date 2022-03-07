#!/usr/bin/env python3
from subprocess import STDOUT, Popen, PIPE, run
from tempfile import mkstemp
import tempfile
from os import remove

# Global Variables
verbose = False
# Global Array to collect results
result = []

# Verbosity - set to False above if you don't want output

def vprint(status):
    global result
    result.append(status)
    if verbose:
        print(status)

def runScript(args):
    try:
        process = run(args,
            encoding='utf-8',
            stdout=PIPE,
            stderr=STDOUT,
            universal_newlines=True,
            text=True)
        data = process.stdout
        vprint(data)
    except Exception as e:
        vprint(f"Exception Raised: {e} ")
    
def main(filename,vfs):
    global result
    result = []
    args = []
    if vfs:
        args = ["osascript","-l","JavaScript","-e",filename]
    else:
        args = ["osascript","-l","JavaScript", filename]
    runScript(args)
    return result

if __name__ == "__main__":
    main("/Users/bradosev/Downloads/console.js",False)