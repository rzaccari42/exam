#!/bin/sh

[ -z "$1" ]
x=$(echo "$1" | sed 's/\([][(){}\^.*+?$|]\)/\\\1/g')
y=$(echo "$1" | sed -E 's/./*/g')
echo x=$x;
echo y=$y;
sed -E "s/$x/$y/"
