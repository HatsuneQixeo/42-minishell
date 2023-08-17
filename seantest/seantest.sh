#!/bin/bash

Reset='\033[0m'
Bold='\033[1m'
Cyan='\033[36m'
Green='\033[32m'
Red='\033[31m'

# Customization
LOGFILE="diff.log"
PRGPATH=".."

# Setup
make -C "$PRGPATH"  && > "$LOGFILE" || exit 1

function ohno()
{
	local	prompt="🐚$ "
	local	errorPrompt="🐚:"

	varMini="${varMini#$prompt$command$'\n'}"
	varMini="${varMini%$prompt}"
	varMini="${varMini%$'\n'}"
	varMini="${varMini/$errorPrompt/bash: line 1:}"
	if [ "$varBash" == "$varMini" ]
	then
		echo -e $Green"$where"$Reset
		return 0
	else
		echo -e $Red"$where"$Reset
		logs+=("$where")
		logs+=("	bash     : \`$varBash'")
		logs+=("	minishell: \`$varMini'")
		return 1
	fi
}

# Bug: Due to invoking multiple command multiple times,
# 	It could yield different result from different invocation
# I could make use of tmpfile to invoke all of them at once, but nah
function minitest()
{
	local	errnoBash
	local	errnoMini

	where="$1"
	if [ "$where" == "Stdout" ]
	then
		varBash="$(bash <<< "$command" 2> /dev/null)"
		errnoBash=$?
		varMini="$(${PRGPATH}/minishell <<< "$command" 2> /dev/null)"
		errnoMini=$?
	elif [ "$where" == "Stderr" ]
	then
		varBash="$(bash <<< "$command" 2>&1 > /dev/null)"
		errnoBash=$?
		varMini="$(${PRGPATH}/minishell <<< "$command" 2>&1 > /dev/null)"
		errnoMini=$?
	else
		echo "Where is this?: $where"
		exit 39
	fi
	ohno
	local	err=$?

	if [ $errnoBash -ne $errnoMini ]
	then
		logs+=("Unsynced exit status: bash($errnoBash) | mini($errnoMini)")
		if [ $errnoMini -eq 139 ]
		then
			echo -e $Red"	Segfault?:)"$Reset
		fi
		return 1
	fi
	return $err
}

function minidiff()
{
	echo "$1 test:" >> "$LOGFILE"
	while read command
	do
		local	err=0

		echo -e "command: ${Bold}${Cyan}${command}${Reset}"
		logs=()
		logs+=("Command: $command")
		# Shows the difference in stdout
		minitest "Stdout" || err=1
		# Shows the difference in stderr
		minitest "Stderr" || err=1
		# Continue if no error
		[ $err -eq 0 ] && continue
		# Otherwise prints out all the saved logs
		for line in "${logs[@]}"
		do
			echo "$line" >> "$LOGFILE"
		done
		echo "================================================================================" >> "$LOGFILE"
	done
}

# First test: quote 
touch libft srcs minishell objs

minidiff << "eof" "First"
echo hi
echo "'hi" "hi'"
echo '"hi' 'hi"'
echo ""
echo ''
echo '' "" hi''hi hi""hi h"i" 'h'i "h"'i' 'h'i ''"h"''""'i'""'' '"hello"'"'hello'" "'" '"'
eof

# Second test: variable expansion and parse
export A="hi" B="ho hi" C=""

minidiff << "eof" "Second"
echo $A "$A" '$A'
echo $A"hi" $A'hi' $'A' $"A" $""A $''A $A'' $A"" '$'A "$"A '"$A"' "'$A'" '$'"A" "$"'A' "$'A'" '$"A"' "'$'"A"" '"$"'A'"'ec$B
ec$B$B$B$B$B$B$B$B$B$B
ec$B$A$C$D$C$B$A
ec"$B"
ec"$B$A$C$D$C$B$A"
ec'$B'
ec'$B$A$C$D$C$B$A'
ec"$B"$A'$C'
ec$B"$B"
ec$B"42"
ec'$B'$A"$C"
ec''$B
ec""$B
e'c'$B
e"c"$B
"ec"$B
'ec'$B
'ec$B'
"ec$B"
'ec$B42'
"ec$B42"
eof

export A="     "
minidiff << "eof" "Third export space"
echo a $A "$A" $C "$C" $D "$C" a
eof

export A=$B
minidiff << "eof" "Third export assignment"
echo $A
eof

# Third test: wildcard
export B="ho *"
minidiff << "eof" "Third"
ec$B
ec$B$B$B$B$B$B$B$B$B$B
ec$B$A$C$D$C$B$A
ec"$B"
ec"$B$A$C$D$C$B$A"
ec'$B'
ec'$B$A$C$D$C$B$A'
ec"$B"$A'$C'
ec$B"$B"
ec$B"42"
ec'$B'$A"$C"
ec''$B
ec""$B
e'c'$B
e"c"$B
"ec"$B
'ec'$B
eof

# Fourth test: Hohohohohohohohoho
touch sxsxs $ "sp ce" testho testftho testft$C testft42 *s testftatest
minidiff << "eof" "Fourth"
echo * "*" '*'
echo * *ft *s *s* s* s*s *P "* " " *" "* *" *$ $'*' $"*"
ec$B ec$B$B$B$B$B$B$B$B$B$B ec$B$A$C$D$C$B$A ec"$B" ec"$B$A$C$D$C$B$A" ec'$B' ec'$B$A$C$D$C$B$A' ec"$B"$A'$C' ec$B"$B" ec$B"42" ec'$B'$A"$C" ec''$B ec""$B e'c'$B e"c"$B "ec"$B 'ec'$B 'ec$B' "ec$B" 'ec$B42' "ec$B42"
ec$B"a"*
ec$B""*
ec$B''*
ec$B'*'
ec$B"*"
eof

export B="ho *ft"
minidiff << "eof" "Fourth export *"
ec$B ec$B$B$B$B$B$B$B$B$B$B ec$B$A$C$D$C$B$A ec"$B" ec"$B$A$C$D$C$B$A" ec'$B' ec'$B$A$C$D$C$B$A' ec"$B"$A'$C' ec$B"$B" ec$B"42" ec'$B'$A"$C" ec''$B ec""$B e'c'$B e"c"$B "ec"$B 'ec'$B 'ec$B' "ec$B" 'ec$B42' "ec$B42"
ec$B"a"*
ec$B""*
ec$B''*
ec$B'*'
ec$B"*"
eof

rm libft minishell $ "sp ce" testho testftho testft$C testft42 *s testftatest
