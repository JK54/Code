#!/bin/sh

echo "count the line number."
find ~/Code -name "*" -path "/home/JK54/Code/.git" -prune -o -print|xargs cat|wc -l