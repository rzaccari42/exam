#!/bin/sh

[ -z "$1" ]

arg=$(echo "$1" | sed 's/\([][(){}\^.*+?$|]\)/\\\1/g')
stared=$(echo "$1" | sed -E 's/./*/g')
sed -E "s/$arg/$stared/"

