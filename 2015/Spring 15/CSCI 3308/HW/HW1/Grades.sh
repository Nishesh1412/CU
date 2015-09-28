#!/bin/bash
#Nishesh Shukla

if [ $# -lt 1 ]
then
echo "Usage: Grades.sh filename"
exit 1
fi

while read -r ID first last h1 h2 h3;do
	sum=$(expr $h1 + $h2 + $h3)
	avg=$(expr $sum / 3)
	printf '%d [%d] %s, %s\n' $avg $ID $last $first
done <"$1" | sort -k3 -k4 -k2
