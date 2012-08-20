libp4shim
=========

LD_PRELOAD library for running 2012.1 p4 clients on Linux 2.4.

##Build

<tt>gcc -Wall -O2 -fpic -shared -ldl -o libp4shim.so libp4shim.c</tt>

##Usage

<tt>LD_PRELOAD=libp4shim.so p4</tt>

##Tested on
- Redhat 8, p4 version 2012.1/473528

