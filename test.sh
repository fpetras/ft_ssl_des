#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
WHITE="\033[1;37m"
RESET="\033[0;0m"
CLEAR_LINE="\033[2K\c"

TEST1="this is a test :)"
TEST2="this is another test "
STDIN="stdin test 1234*!√≤µ˜∫"
OPT_P="Test option -p"
STRING1='Testing strings'
STRING2='1moreTest'
STRING3="string"

counter=0
TEST_NUM=11

#############################----------1----------##############################
echo $TEST1 > file
FT_SSL_MD5=$(./ft_ssl md5 file)
MD5=$(md5 file)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"$TEST1\" > file ; ./ft_ssl md5 file"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"$TEST1\" > file ; ./ft_ssl md5 file"
fi
#############################----------2----------##############################
FT_SSL_MD5=$(echo $STDIN | ./ft_ssl md5)
MD5=$(echo $STDIN | md5)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"$STDIN\" | ./ft_ssl md5"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"$STDIN\" | ./ft_ssl md5"
fi
#############################----------3----------##############################
FT_SSL_MD5=$(echo $TEST2 | ./ft_ssl md5 -q -r)
MD5=$(echo $TEST2 | md5 -q -r)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"$TEST2\" | ./ft_ssl md5 -q -r"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"$TEST2\" | ./ft_ssl md5 -q -r"
fi
#############################----------4----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -r file)
MD5=$(md5 -r file)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"$TEST1\" > file ; ./ft_ssl md5 -r file"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"$TEST1\" > file ; ./ft_ssl md5 -r file"
fi
#############################----------5----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -s "$STRING1")
MD5=$(md5 -s "$STRING1")
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl md5 -s \"$STRING1\""
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo  -e "$RED KO: $RESET" "./ft_ssl md5 -s \"$STRING1\""
fi
#############################----------6----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -s$STRING2)
MD5=$(md5 -s $STRING2)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl md5 -s$STRING2"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -s$STRING2"
fi
#############################----------7----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -s "")
MD5=$(md5 -s "")
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl md5 -s \"\""
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -s \"\""
fi
#############################----------8----------##############################
FT_SSL_MD5=$(echo $OPT_P | ./ft_ssl md5 -p)
MD5=$(echo $OPT_P | md5 -p)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"$OPT_P\" | ./ft_ssl md5 -p"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"$OPT_P\" | ./ft_ssl md5 -p"
fi
#############################----------9----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -s $STRING3 file)
MD5=$(md5 -s $STRING3 file)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl md5 -s \"$STRING3\" file"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -s \"$STRING3\" file"
fi
#############################---------10----------##############################
FT_SSL_MD5=$(echo "tough one" | ./ft_ssl md5 -r -p -s 'foo' file -s "bar")
MD5=$(echo "tough one" | md5 -r -p -s 'foo' file -s "bar")
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \""tough one\"" | ./ft_ssl md5 -r -p -s 'foo' file -s 'bar'"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"tough one\" | ./ft_ssl md5 -r -p -s 'foo' file -s 'bar'"
fi
#############################---------11----------##############################
echo "this" > this && echo "is" > is && echo "a" > a && echo "test" > test
FT_SSL_MD5=$(./ft_ssl md5 this is a test)
MD5=$(md5 this is a test)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" 'echo "this" > this && echo "is" > is && echo "a" > a && echo "test" > test' "./ft_ssl md5 this is a test"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" 'echo "this" > this && echo "is" > is && echo "a" > a && echo "test" > test' "./ft_ssl md5 this is a test"
fi
rm file
rm this is a test


if [ "$counter" -eq $TEST_NUM ]; then
	echo -e "$GREEN [ $counter / $TEST_NUM ] $RESET"
else
	echo -e "$RED [ $counter / $TEST_NUM ] $RESET"
fi

################################################################################
counter=0
echo -e "$WHITE Test binary files: $RESET"
sleep 2.5
#############################----------1----------##############################
FT_SSL_MD5=$(cat $(whereis ls) | ./ft_ssl md5)
MD5=$(cat $(whereis ls) | md5)
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis ls) | ./ft_ssl md5"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis ls) | ./ft_ssl md5"
fi
#############################----------2----------##############################
FT_SSL_MD5=$(./ft_ssl md5 -r $(whereis cat))
MD5=$(md5 -r $(whereis cat))
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl md5 -r $(whereis cat)"
	echo "$FT_SSL_MD5"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl md5 -r $(whereis cat)"
fi
#############################----------3----------##############################
FT_SSL_MD5=$(cat $(whereis bash) | ./ft_ssl md5 -p -r $(whereis ln) $(whereis echo) $(whereis rm))
MD5=$(cat $(whereis bash) | md5 -p -r $(whereis ln) $(whereis echo) $(whereis rm))
if [ "$FT_SSL_MD5" == "$MD5" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis bash) | ./ft_ssl md5 -p -r $(whereis ln) $(whereis echo) $(whereis rm)"
	echo "(output not displayed, too large)"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis bash) | ./ft_ssl md5 -p -r $(whereis ln) $(whereis echo) $(whereis rm)"
fi


if [ "$counter" -eq 3 ]; then
	echo -e "$GREEN [ $counter / 3 ] $RESET"
else
	echo -e "$RED [ $counter / 3 ] $RESET"
fi

################################################################################
counter=0
echo -e "$WHITE Test random strings: $RESET"
sleep 2.5
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_MD5=$(./ft_ssl md5 -q file1)
	MD5=$(md5 -q file1)
	if [ "$FT_SSL_MD5" == "$MD5" ] ; then
		cat file1
		echo -e $CLEAR_LINE
		echo -n -e "$FT_SSL_MD5\r\c"
		echo -e "$GREEN $counter OK $RESET\r\c"
		counter=$((counter+1))
	else
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
counter=0
echo -e "$WHITE Test random binary data: $RESET"
sleep 2.5
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_MD5=$(./ft_ssl md5 -q file2)
	MD5=$(md5 -q file2)
	if [ "$FT_SSL_MD5" == "$MD5" ] ; then
		cat file1
		echo -e $CLEAR_LINE
		echo -n -e "$FT_SSL_MD5\r\c"
		echo -e "$GREEN $counter OK $RESET\r\c"
		counter=$((counter+1))
	else
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
	fi
done
rm file1 file2


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
