#!/bin/bash

cmd=""
carret=0
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
elsed
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
	for (( i=0; i<${#token[@]}; i++ )); do
		if [ $i -eq $carret ]; then
			echo -n "\033[7m"
		fi
		echo -n "${token[$i]}"
		if [ $i -eq $carret ]; then
			echo -n "\033[0m"
		fi
	done
	read -s -n 1 key
	cmd+="$key"
	case "$cmd" in
	[Ff])
		# tap easy
		# move carret to the left
		if [ carret -ne 0 ]; then
			(( carret-- ))
		fi
		;;
	[Jj])
		# tap easy
		# move the carret to the right
		if [ carret -ne (( ${#token[@]} - 1 )) ]; then
			(( carret++ ))
		fi
		;;
	[Qq])
		# omit `quit'
		# finish program
		break
		;;
	*)
		cmd=""
		;;
	esac
done
