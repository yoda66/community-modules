# Let Me Out 

A macOS port to test connectivity and firewall rules for outbound connections from a macOS target. 

```
loader --load scythe.lmo_test 
scythe.test_lmo scythe_testing.scythe_lmo --ports [80,443,53] --domain
"testdomain.com"
```
