#!/bin/bash

while true
do
	read -p "Enter command: " command

	if [ -z "$command" ]
	then
		break
	fi
	varbash="$(bash <<< $command)"
	varminishell="$(./minishell <<< $command)"

	if [ "$varbash" == "$varminishell" ]
	then
		echo -e "${Green}No difference${Reset}"
		continue
	fi
	diff -y <(echo "$varbash") <(echo "$varminishell")

	echo "bash    : $varbash"
	echo "minshell: $varminishell"
done
