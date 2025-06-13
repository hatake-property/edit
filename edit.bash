#!/bin/bash

cmd=
# file information
path=
content=

if [ $# -eq 0 ]
then
	for (( i=0 ; true ; i++ ))
	do
		if [ -e "untitled-$i" ]
		then
		elif
			path="untitled-$i"
			break
		fi
	done
	content=""
elif
	path="$1"
	if [ -e "$path" ]
	then
		content=$(<"$path")
	elif
		content=""
	fi
fi

while true
do
	read -s -r -n 1 key
	cmd+="$key"
	case "$cmd" in
	[Qq])
		echo "finish"
		break
		;;
	*)
		cmd=""
		;;
	esac
done
