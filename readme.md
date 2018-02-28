![Screen1](/screens/Untitled%201.jpg)
## about 
 json demo  
   sends request of action to a wallet and then receives smth .  
 - windows version configured to use with btx now  
 for btc change bitcore to bitcoin and 8556 to 8332  
## how to:
 1) run `bitcore-qt -server`  
 2) this app   
 
## windows build:
req : ms visual studio 2010 (C++)  
nmake holds well on non-2010 too  
  
vs win64 command prompt (standard command prompt works too if env tuned right ) 
```
nmake
```
  
## linux build:
openssl installed

```
cd json_c_linux
make
```
