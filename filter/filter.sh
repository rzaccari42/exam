#!/bin/sh

[ -z "$1" ]

arg=$(echo "$1" | sed 's/\([][(){}\^.*+?$|]\)/\\\1/g')
echo "escaped arg : [$arg]"
stared=$(echo "$1" | sed -E 's/./*/g')
echo "stared arg : [$stared]\n"
sed -E "s/$arg/$stared/g"

