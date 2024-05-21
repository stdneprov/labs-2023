#!/bin/bash
find . -type f -name "*.$1" -atime +$2 -delete
