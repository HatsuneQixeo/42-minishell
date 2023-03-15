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

	echo -e "command: ${Bold}${Cyan}${command}${Reset}"
	echo "bash    : $varbash"
	echo "minshell: $varminishell"
	if [ "$varbash" == "$varminishell" ]
	then
		echo -e "${Green}No difference${Reset}"
	else
		diff -y <(echo "$varbash") <(echo "$varminishell")
	fi

done
