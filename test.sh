#!/bin/bash

testFile() {
echo -e "\nTEST "$1".txt"
./tp0 test-files/$1.txt | ./tp0 > output/$1.txt
res1=($(md5sum test-files/$1.txt))
res2=($(md5sum output/$1.txt))
if [ $res1 == $res2 ]; 
then
	echo -e "OK\n"
else
	echo -e "ERROR\n"
fi
}

echo Compilando...
gcc -o tp0 main.c

testFile empty
testFile basic
testFile empty-lines
testFile large-file

