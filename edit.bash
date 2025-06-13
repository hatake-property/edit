#!/bin/bash

cmd=
# file information
path=
token=()

if [ $# -eq 0 ]
then
	for (( i=0 ; true ; i++ ))
	do
		if [ ! -e "untitled-$i" ]
        then
			path="untitled-$i"
			break
		fi
	done
	content=""
else
	path="$1"
	if [ -e "$path" ]
	then
		s=
		for (( i=1 ; i -le ${#$(<"$path")} ; i++ ))
		do
			c=$(<"$path")|cat -c i
			case "$c" in
			\n)
				token+=("$s")
				s+="$c"
				;;
			[\s])
				if [ "$s"|cat -c 0 != [ ] ]
				then
					token+=("$s")
					s=""
				fi
				s+="$c"
				;;
			*)
				if [ "$s"|cat -c 0 = [ ] ] || [ "$s"|cat -c 0 = [ ] ]
				then
					token+=("$s")
					s=""
				fi
				s+="$c"
				;;
			esac
		done
		token+=("$s")
	else
		content=""
	fi
fi

while true
do
	clear
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
