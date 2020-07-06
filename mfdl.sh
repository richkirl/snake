#!/bin/sh
ldd $1 | awk '{print $3}' | cp $(awk '{print $1}') $PWD
