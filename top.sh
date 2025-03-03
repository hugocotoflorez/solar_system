#!/bin/bash

htop --pid $(ps -u | grep $1 | grep -o -e "[0-9]*" -m1 | head -n1)
