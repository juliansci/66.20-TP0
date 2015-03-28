#!/bin/bash

testFile() {
	echo -e "\nTEST "$1".txt"
	./tp0 test-files/$1.txt | ./tp0 > output/$1.txt
	res1=($(md5sum test-files/$1.txt))
	res2=($(md5sum output/$1.txt))
	
	echo "md5 de $1: $res2"
	if [ $res1 == $res2 ]; 
	then
		echo -e "OK\n"
	else
		echo -e "ERROR\n"
	fi
}

testWords() {
	echo -e "\nTEST WORDS"
	res1=($(cat '/usr/share/dict/words' | md5sum))
	res2=($(./tp0 '/usr/share/dict/words' | ./tp0 | md5sum))
	
	echo "md5 de words: $res2"
	if [ $res1 == $res2 ]; 
	then
		echo -e "OK\n"
	else
		echo -e "ERROR\n"
	fi
}

echo Compilando...
gcc -o tp0 main.c

FILES=(empty basic empty-lines large-file return status)

for i in ${FILES[@]}; do
	testFile ${i}
done

testWords
