#! /bin/bash

while true
do
	read -p "Enter command: " command

	if [ -z "$command" ]
	then
		break
	fi
	varbash="$(bash <<< $command)"
	varminishell="$(./minishell <<< $command)"

	echo "bash    : ][ $varbash ]["
	echo "minshell: ][ $varminishell ]["

	diff -y <(echo "$varbash") <(echo "$varminishell")

done
