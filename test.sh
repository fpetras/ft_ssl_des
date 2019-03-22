#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
WHITE="\033[1;37m"
RESET="\033[0;0m"
CLEAR_SCREEN="\033[2J"
CLEAR_LINE="\033[2K\c"

TEST1="this is a test :)"
TEST2="this is another test "
STDIN="stdin test 1234*!√≤µ˜∫"
OPT_P="Test option -p"
STRING1='Testing strings'
STRING2='1moreTest'
STRING3="string"

counter=0
md5_total=0
sha256_total=0
TEST_NUM=11

md5_set=0
sha256_set=0

function print_usage {
	echo "usage: $0 [md5 | sha256 | all] ..."
	echo ""
	echo "available tests: md5"
	echo "                 sha256"
	echo "                 all"
}

function md5_header {
	echo -e -n "$WHITE"
	echo "███╗   ███╗██████╗ ███████╗
████╗ ████║██╔══██╗██╔════╝
██╔████╔██║██║  ██║███████╗
██║╚██╔╝██║██║  ██║╚════██║
██║ ╚═╝ ██║██████╔╝███████║
╚═╝     ╚═╝╚═════╝ ╚══════╝"
	echo -e -n "$RESET"
}

function sha256_header {
	echo -e -n "$WHITE"
	echo "███████╗██╗  ██╗ █████╗       ██████╗ ███████╗ ██████╗
██╔════╝██║  ██║██╔══██╗      ╚════██╗██╔════╝██╔════╝
███████╗███████║███████║█████╗ █████╔╝███████╗███████╗
╚════██║██╔══██║██╔══██║╚════╝██╔═══╝ ╚════██║██╔═══██╗
███████║██║  ██║██║  ██║      ███████╗███████║╚██████╔╝
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝      ╚══════╝╚══════╝ ╚═════╝"
	echo -e -n "$RESET"
}

if [ $# -eq 0 ] ; then
	print_usage
	exit
fi

for arg in "$@" ; do
	case $arg in
		md5)
			md5_set=1
			;;
		sha256)
			sha256_set=1
			;;
		all)
			md5_set=1
			sha256_set=1
			;;
		*)
			print_usage
	esac
done

#############################---------MD5---------##############################
if [ $md5_set -eq 1 ] ; then

echo -e -n $CLEAR_SCREEN
md5_header
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
md5_total=$(($md5_total+$counter))
counter=0
echo -e "$WHITE MD5: Test binary files: $RESET"
sleep 2
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
md5_total=$(($md5_total+$counter))
counter=0
echo -e "$WHITE MD5: Test random strings: $RESET"
sleep 2
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
		echo -e $CLEAR_LINE
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
md5_total=$(($md5_total+$counter))
counter=0
echo -e "$WHITE MD5: Test random binary data: $RESET"
sleep 2
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
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
	fi
done
rm file1 file2
md5_total=$(($md5_total+$counter))


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
fi



#############################-------SHA-256-------##############################
if [[ $md5_set -eq 1 && $sha256_set -eq 1 ]] ; then
	echo ""
	sha256_header
	sleep 2.5
elif [ $sha256_set -eq 1 ] ; then
	echo -e $CLEAR_SCREEN
	sha256_header
fi

if [ $sha256_set -eq 1 ] ; then

echo "test" | openssl sha256 > openssl_valid 2>&-
if [ -s openssl_valid ] ; then
	CMD="openssl sha256"
else
	CMD="shasum -a 256"
fi
rm openssl_valid

#############################----------1----------##############################
counter=0
FT_SSL_SHA256=$(echo "This is a simple test" | ./ft_ssl sha256)
if [ "$CMD" == "shasum -a 256" ] ; then
	FT_SSL_SHA256=$FT_SSL_SHA256"  -"
fi
SHA256=$(echo "This is a simple test" | $CMD)
if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha256"
	echo "$FT_SSL_SHA256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha256"
fi
#############################----------2----------##############################
FT_SSL_SHA256=$(./ft_ssl sha256 -q -s "String test")
if [ "$CMD" == "shasum -a 256" ] ; then
	FT_SSL_SHA256=$FT_SSL_SHA256"  -"
fi
SHA256=$(echo -n "String test" | $CMD)
if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha256 -q -s \"String test\""
	echo "$FT_SSL_SHA256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha256 -q -s \"String test\""
fi
#############################----------3----------##############################
FT_SSL_SHA256=$(cat $(whereis shasum) | ./ft_ssl sha256)
if [ "$CMD" == "shasum -a 256" ] ; then
	FT_SSL_SHA256=$FT_SSL_SHA256"  -"
fi
SHA256=$(cat $(whereis shasum) | $CMD)
if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis shasum) | ./ft_ssl sha256"
	echo "$FT_SSL_SHA256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis shasum) | ./ft_ssl sha256"
fi
#############################----------4----------##############################
FT_SSL_SHA256=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | ./ft_ssl sha256)
if [ "$CMD" == "shasum -a 256" ] ; then
	FT_SSL_SHA256=$FT_SSL_SHA256"  -"
fi
SHA256=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | $CMD)
if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
	echo -e "$GREEN OK: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha256"
	echo "$FT_SSL_SHA256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha256"
fi



if [ "$counter" -eq 4 ]; then
	echo -e "$GREEN [ $counter / 4 ] $RESET"
else
	echo -e "$RED [ $counter / 4 ] $RESET"
fi

################################################################################
sha256_total=$(($sha256_total+$counter))
counter=0
echo -e "$WHITE SHA-256: Test random strings: $RESET"
sleep 2
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA256=$(./ft_ssl sha256 -q file1)
	if [ "$CMD" == "shasum -a 256" ] ; then
		FT_SSL_SHA256=$FT_SSL_SHA256"  -"
	fi
	SHA256=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
		echo -e $CLEAR_LINE
		echo -n -e "$FT_SSL_SHA256\r\c"
		echo -e "$GREEN $counter OK $RESET\r\c"
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
		echo $FT_SSL_SHA256
		echo $SHA256
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
sha256_total=$(($sha256_total+$counter))
counter=0
echo -e "$WHITE SHA-256: Test random binary data: $RESET"
sleep 2
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA256=$(./ft_ssl sha256 -q file2)
	if [ "$CMD" == "shasum -a 256" ] ; then
		FT_SSL_SHA256=$FT_SSL_SHA256"  -"
	fi
	SHA256=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
		echo -e $CLEAR_LINE
		echo -n -e "$FT_SSL_SHA256\r\c"
		echo -e "$GREEN $counter OK $RESET\r\c"
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
		echo $FT_SSL_SHA256
		echo $SHA256
fi
done
rm file1 file2
sha256_total=$(($sha256_total+$counter))


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
fi



echo "┌──────────────────────────────────────────────────────┐"

if [ $md5_set -eq 1 ] ; then
	if [ $md5_total -eq 214 ] ; then
		echo -e -n "│ MD5 score: $GREEN     [ $md5_total / 214 ] $RESET"
		if [ $md5_total -lt 10 ] ; then
			echo "                         │"
		elif [[ $md5_total -gt 9 && $md5_total -lt 100 ]] ; then
			echo "                        │"
		elif [ $md5_total -gt 99 ] ; then
			echo "                       │"
		fi
	else
		echo -e -n "│ MD5 score: $RED     [ $md5_total / 214 ] $RESET"
		if [ $md5_total -lt 10 ] ; then
			echo "                         │"
		elif [[ $md5_total -gt 9 && $md5_total -lt 100 ]] ; then
			echo "                        │"
		elif [ $md5_total -gt 99 ] ; then
			echo "                       │"
		fi
fi
fi

if [ $sha256_set -eq 1 ] ; then
	if [ $sha256_total -eq 204 ] ; then
		echo -e -n "│ SHA-256 score: $GREEN [ $sha256_total / 204 ] $RESET"
		if [ $sha256_total -lt 10 ] ; then
			echo "                         │"
		elif [[ $sha256_total -gt 9 && $sha256_total -lt 100 ]] ; then
			echo "                        │"
		elif [ $sha256_total -gt 99 ] ; then
			echo "                       │"
		fi
	else
		echo -e -n "│ SHA-256 score: $RED [ $sha256_total / 204 ] $RESET"
		if [ $sha256_total -lt 10 ] ; then
			echo "                         │"
		elif [[ $sha256_total -gt 9 && $sha256_total -lt 100 ]] ; then
			echo "                        │"
		elif [ $sha256_total -gt 99 ] ; then
			echo "                       │"
		fi
fi
fi

echo "└──────────────────────────────────────────────────────┘"
