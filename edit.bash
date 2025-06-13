#!/bin/bash

cmd=""
# file information
path=""
token=()

if [ $# -eq 0 ]; then
	for (( i=0 ; true ; i++ )); do
		if [ ! -e "untitled-$i" ]; then
			path="untitled-$i"
			break
		fi
	done
	content=""
else
	path="$1"
	if [ -e "$path" ]; then
		s=""
		content=$(<"$path")
		for (( i=0; i<${#content}; i++ )); do
			c="${content:i:1}"
			case "$c" in
			$'\n')
				token+=("$s")
				s="$c"
				;;
			" ")
				if [ "${s:0:1}" != " " ]
				then
					token+=("$s")
					s=""
				fi
				s+="$c"
				;;
			*)
				if [ "${s:0:1}" = " " ] || [ "${s:0:1}" = $'\n' ]
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

while true; do
	clear
	for item in "${token[@]}"; do
		echo -n "$item"
	done
	read -s -n 1 key
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
