#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
RESET="\033[0;0m"

TEST1="this is a test :)"
TEST2="this is another test "
STDIN="stdin test 1234*!√≤µ˜∫"
OPT_P="Test option -p"
STRING1='Testing strings'
STRING2='1moreTest'
STRING3="string"

counter=0
TEST_NUM=10

#############################----------1----------##############################
echo $TEST1 > file
if ./ft_ssl md5 file | grep -q "$(md5 file)" ; then
	echo -e "$GREEN OK: $RESET" "$(./ft_ssl md5 file)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 file ## file: \"this is a test :)\""
fi
#############################----------2----------##############################
if echo $STDIN | ./ft_ssl md5 | grep -q "$(echo $STDIN | md5)" ; then
	echo -e "$GREEN OK: $RESET" "$(echo $STDIN | ./ft_ssl md5)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo $STDIN | ./ft_ssl md5"
fi
#############################----------3----------##############################
if echo $TEST2 | ./ft_ssl md5 -q -r | grep -q "$(echo $TEST2 | md5 -q -r)" ; then
	echo -e "$GREEN OK: $RESET" "$(echo $TEST2 | ./ft_ssl md5 -q -r)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo '$TEST2' | ./ft_ssl md5 -q -r"
fi
#############################----------4----------##############################
if ./ft_ssl md5 -r file | grep -q "$(md5 -r file)" ; then
	echo -e "$GREEN OK: $RESET" "$(./ft_ssl md5 -r file)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -r file ## file: \"this is a test :)\""
fi
#############################----------5----------##############################
if ./ft_ssl md5 -s "$STRING1" | grep -q "$(md5 -s "$STRING1")" ; then
	echo -e "$GREEN OK: $RESET" "$(./ft_ssl md5 -s "$STRING1")"
	counter=$((counter+1))
else
	echo  -e "$RED KO: $RESET" "./ft_ssl md5 -s '$STRING1'"
fi
#############################----------6----------##############################
if ./ft_ssl md5 -s$STRING2 | grep -q "$(md5 -s$STRING2)" ; then
	echo -e "$GREEN OK: $RESET" "$(./ft_ssl md5 -s$STRING2)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -s$STRING2"
fi
#############################----------7----------##############################
if ./ft_ssl md5 -s "" | grep -q "$(md5 -s "")" ; then
	echo -e "$GREEN OK: $RESET" "$(./ft_ssl md5 -s "")"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -s \"\""
fi
#############################----------8----------##############################
FT_SSL_MD5=$(echo $OPT_P | ./ft_ssl md5 -p)
MD5=$(echo $OPT_P | md5 -p)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" ; echo "$(echo $OPT_P | ./ft_ssl md5 -p)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"$OPT_P\" | ./ft_ssl md5 -p"
fi
#############################----------9----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -s $STRING3 file)
MD5=$(md5 -s $STRING3 file)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" ; echo "$(./ft_ssl md5 -s $STRING3 file)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -s $STRING file"
fi
#############################---------10----------##############################







#############################---------??----------##############################
echo "this" > this && echo "is" > is && echo "a" > a && echo "test" > test
if ./ft_ssl md5 this is a test | grep -q "$(md5 this is a test)" ; then
	echo -e "$GREEN OK: $RESET" ; echo "$(./ft_ssl md5 this is a test)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET"
fi

rm this is a test

if [ "$counter" -eq $TEST_NUM ]; then
	echo -e "$GREEN [ $counter / $TEST_NUM ] $RESET"
else
	echo -e "$RED [ $counter / $TEST_NUM ] $RESET"
fi
counter=0

echo "Random strings:"
sleep 2.5
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 100 > file
	if ./ft_ssl md5 -q file | grep -q "$(md5 -q file)"; then
		echo -e "$GREEN OK $RESET"
		counter=$((counter+1))
	else
		echo -e "$RED KO $RESET" "## file: " && cat file
	fi
done

if [ "$counter" -eq 100 ]; then
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
rm file
