#!/bin/bash
#Nishesh Shukla

if [ $# -lt 1 ]
then
echo "Usage: GradesAwk.sh filename"
exit 1
fi

awk '{sum= $4+$5+$6; sum= sum/3; print sum, "[" $1 "]", $3 ",", $2}' $1 | sort -d -k3,4
