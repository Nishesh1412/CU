#!/bin/bash
#Nishesh Shukla

if [ $# -lt 1 ]
then 
echo "Usage: RegexAnswers.sh filename"
exit 1
fi

#1
egrep '[0-9]$' $1| wc -l
#2
egrep '^[^aeiouAEIOU]' $1| wc -l
#3
egrep '^[a-zA-Z]{12}$' $1| wc -l
#4
egrep '^[0-9]{3}-[0-9]{3}-[0-9]{4}$' $1| wc -l
#5
egrep '^303-441-[0-9]{4}$' $1| wc -l
#6
egrep '[a-zA-Z0-9.-_]+@[a-zA-Z0-9.-_]+\.[a-zA-Z]{1,3}$' $1 | wc -l
#7
egrep '[a-zA-Z0-9.-_]+@[a-zA-Z0-9.-_]+\.gov$' $1| wc -l 
