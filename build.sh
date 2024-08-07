#!/bin/bash

rm ./ok

gcc main.c -o ok -L. -lringbuffer -Wl,-rpath,.
