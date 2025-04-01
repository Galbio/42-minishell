#!/bin/bash

test_values=(
	"*"
	"[a-z][a-z]*"
	"[a-z][ie]*"
	"[a-z]*[j]*"
	"[a-z][a-z][j]*"
	"[o][j]*"
	"[o][b][j]*"
	"*[M]*"
	"*[Z-a]*"
	"[a-z]*"
	"*[a-z]*"
	"[[[[[[A-z]"
	"[[[[[[A-z][A-z][A-z]"
	"[a-z]*[a-z]*[a-z]*[a-z]*[a-z]*[a-z]"
	"[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]"
	"*a-z]]"
	"[[[a-z][a-z]**[a-z][[[a-z]"
	"[[[a-z][a-z]*?*[a-z][[[a-z]"
	"??"
	"??*"
	"?*??*?"
	"[a]??*"
	"?*?*[a-z][a-z][a-z]***"
	"***[a-z][a-z][a-z]*?*?"
	"??*??*??"
	"**[a-z][a-z]*[a-z][a-z][a-z]*??*"
	"?"
"*?"
"*??*"
"[A-Z]*"
"[0-9]*"
"[!a-z]*"
"[!A-Z]*"
"[!0-9]*"
"[a-zA-Z]*"
"[a-zA-Z0-9]*"
"[a-z]*[0-9]*"
"[0-9]*[a-z]*"
"[0-9][a-z][0-9]*"
"[a-z][0-9][a-z]*"
"*[a-z]*[0-9]*"
"*[0-9]*[a-z]*"
"**[0-9]*[a-z]*"
"??[0-9][a-z]??"
"[a-z]??[0-9]?"
"[a-z]*[0-9]?*"
"[a-z]*[A-Z]*[0-9]*"
"[a-zA-Z0-9][a-zA-Z0-9]*"
"[a-zA-Z][!a-zA-Z]*"
"[a-z]*[!a-z]*"
"[a-zA-Z]*[!0-9]*"
"*[!a-zA-Z0-9]*"
"[A-Z][a-z][0-9]*[!a-zA-Z0-9]"
"*[!A-Za-z0-9]*"
"[A-Z]?*[0-9][a-z]*?"
"?[a-z]?*[0-9][A-Z]*"
"*[A-Z]*[a-z]*[0-9]*[!a-zA-Z0-9]*"
"[[[[[[[[[]]]]]]]]"
"[a-z][^a-z]*"
"[0-9][^0-9]*"
"[A-Z][^A-Z]*"
"[a-zA-Z][^a-zA-Z]*"
"**[a-zA-Z0-9][^a-zA-Z0-9]**"

)

for input in "${test_values[@]}"; do
    expected_output=$(echo $input)
    actual_output=$(./minishell "$input")
    
    if [ "$expected_output" == "$actual_output" ]; then
        echo -e "\033[0;32m✅ Test réussi : '$input'\033[0m"
    else
        echo -e "\033[0;31m❌ Test échoué : '$input'"
        echo "   Attendu : '$expected_output'"
        echo -e "   Obtenu  : '$actual_output'\033[0m"
    fi
    sleep .1
done

