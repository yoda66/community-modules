#!/usr/bin/env python3
import requests
import base64
import socket
import random
import string

# Global variables
verbose = False
# Global Array to collect results
result = []


# Verbosity - set to False above if you don't want output

def vprint(status):
    global result
    result.append(status)
    
    if verbose == True:
        print(status)


def check(base, domain, port):
    port = str(port)
    vprint(f"Testing: {base}{domain}:{port} - ")
    try:
        r = requests.get(base + domain + ":" + port, timeout=1)
        result = r.text.strip()
        vprint(f"{result} |  ")
        # Removed the OOB part, as results are returned via SCYTHE C2
    except requests.exceptions.ConnectionError:
        vprint("Failed to connect")


def main(ports, domain):
    # Setup the Array of Values
    global result
    result = []
    for port in ports:
        # Test HTTP
        base = "http://"
        check(base, domain, port)
        # Test HTTPS
        base = "https://"
        check(base, domain, port)
    return result


if __name__== "__main__":
    main()
