#!/bin/bash

cmd=

while true; do
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
