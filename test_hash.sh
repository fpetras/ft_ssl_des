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
sha224_total=0
sha256_total=0
sha384_total=0
sha512_total=0
sha512224_total=0
sha512256_total=0
TEST_NUM=11

md5_set=0
sha224_set=0
sha256_set=0
sha384_set=0
sha512_set=0
sha512224_set=0
sha512256_set=0

function ctrl_c {
	rm -f file file1 file2
	exit $?
}

trap ctrl_c SIGINT
trap ctrl_c SIGTERM

function print_usage {
	echo "usage: $0 <test>..."
	echo ""
	echo "available tests: md5"
	echo "                 sha224"
	echo "                 sha256"
	echo "                 sha384"
	echo "                 sha512"
	echo "                 sha512224"
	echo "                 sha512256"
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

function sha224_header {
	echo -e -n "$WHITE"
	echo "███████╗██╗  ██╗ █████╗       ██████╗ ██████╗ ██╗  ██╗
██╔════╝██║  ██║██╔══██╗      ╚════██╗╚════██╗██║  ██║
███████╗███████║███████║█████╗ █████╔╝ █████╔╝███████║
╚════██║██╔══██║██╔══██║╚════╝██╔═══╝ ██╔═══╝ ╚════██║
███████║██║  ██║██║  ██║      ███████╗███████╗     ██║
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝      ╚══════╝╚══════╝     ╚═╝"
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

function sha384_header {
	echo -e -n "$WHITE"
	echo "███████╗██╗  ██╗ █████╗      ██████╗  █████╗ ██╗  ██╗
██╔════╝██║  ██║██╔══██╗     ╚════██╗██╔══██╗██║  ██║
███████╗███████║███████║█████╗█████╔╝╚█████╔╝███████║
╚════██║██╔══██║██╔══██║╚════╝╚═══██╗██╔══██╗╚════██║
███████║██║  ██║██║  ██║     ██████╔╝╚█████╔╝     ██║
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝     ╚═════╝  ╚════╝      ╚═╝"
	echo -e -n "$RESET"
}

function sha512_header {
	echo -e -n "$WHITE"
	echo "███████╗██╗  ██╗ █████╗       ███████╗ ██╗██████╗
██╔════╝██║  ██║██╔══██╗      ██╔════╝███║╚════██╗
███████╗███████║███████║█████╗███████╗╚██║ █████╔╝
╚════██║██╔══██║██╔══██║╚════╝╚════██║ ██║██╔═══╝
███████║██║  ██║██║  ██║      ███████║ ██║███████╗
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝      ╚══════╝ ╚═╝╚══════╝"
	echo -e -n "$RESET"
}

function sha512224_header {
	echo -e -n "$WHITE"
	echo "███████╗██╗  ██╗ █████╗      ███████╗ ██╗██████╗     ██╗██████╗ ██████╗ ██╗  ██╗
██╔════╝██║  ██║██╔══██╗     ██╔════╝███║╚════██╗   ██╔╝╚════██╗╚════██╗██║  ██║
███████╗███████║███████║████╗███████╗╚██║ █████╔╝  ██╔╝  █████╔╝ █████╔╝███████║
╚════██║██╔══██║██╔══██║╚═══╝╚════██║ ██║██╔═══╝  ██╔╝  ██╔═══╝ ██╔═══╝ ╚════██║
███████║██║  ██║██║  ██║     ███████║ ██║███████╗██╔╝   ███████╗███████╗     ██║
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝     ╚══════╝ ╚═╝╚══════╝╚═╝    ╚══════╝╚══════╝     ╚═╝"
	echo -e -n "$RESET"
}

function sha512256_header {
	echo -e -n "$WHITE"
	echo "███████╗██╗  ██╗ █████╗      ███████╗ ██╗██████╗     ██╗██████╗ ███████╗ ██████╗
██╔════╝██║  ██║██╔══██╗     ██╔════╝███║╚════██╗   ██╔╝╚════██╗██╔════╝██╔════╝
███████╗███████║███████║████╗███████╗╚██║ █████╔╝  ██╔╝  █████╔╝███████╗███████╗
╚════██║██╔══██║██╔══██║╚═══╝╚════██║ ██║██╔═══╝  ██╔╝  ██╔═══╝ ╚════██║██╔═══█║
███████║██║  ██║██║  ██║     ███████║ ██║███████╗██╔╝   ███████╗███████║╚██████║
╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝     ╚══════╝ ╚═╝╚══════╝╚═╝    ╚══════╝╚══════╝ ╚═════╝"
	echo -e -n "$RESET"
}


if [ $# -eq 0 ] ; then
	print_usage
	exit 1
fi

for arg in "$@" ; do
	case $arg in
		md5)
			md5_set=1
			;;
		sha224)
			sha224_set=1
			;;
		sha256)
			sha256_set=1
			;;
		sha384)
			sha384_set=1
			;;
		sha512)
			sha512_set=1
			;;
		sha512224)
			sha512224_set=1
			;;
		sha512256)
			sha512256_set=1
			;;
		all)
			md5_set=1
			sha224_set=1
			sha256_set=1
			sha384_set=1
			sha512_set=1
			sha512224_set=1
			sha512256_set=1
			;;
		*)
			print_usage
			exit 1
	esac
done

if [ ! -f ft_ssl ]; then
	make 2>&-
fi
if [ ! -f ft_ssl ]; then
	echo "ft_ssl not found"
	exit 1
fi

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
sleep 1
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
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_MD5=$(./ft_ssl md5 -q file1)
	MD5=$(md5 -q file1)
	if [ "$FT_SSL_MD5" == "$MD5" ] ; then
		echo -e "       " $CLEAR_LINE
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
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_MD5=$(./ft_ssl md5 -q file2)
	MD5=$(md5 -q file2)
	if [ "$FT_SSL_MD5" == "$MD5" ] ; then
		echo -e "       " $CLEAR_LINE
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



#############################-------SHA-224-------##############################
if [[ $md5_set -eq 1 && $sha224_set -eq 1 ]] ; then
	echo ""
	sha224_header
	sleep 1.5
elif [ $sha224_set -eq 1 ] ; then
	echo -e $CLEAR_SCREEN
	sha224_header
fi

if [ $sha224_set -eq 1 ] ; then

echo "test" | openssl sha224 > openssl_valid 2>&-
if [ -s openssl_valid ] ; then
	CMD="openssl sha224"
else
	CMD="shasum -a 224"
fi
rm openssl_valid

#############################----------1----------##############################
counter=0
FT_SSL_SHA224=$(echo "This is a simple test" | ./ft_ssl sha224)
if [ "$CMD" == "shasum -a 224" ] ; then
	FT_SSL_SHA224=$FT_SSL_SHA224"  -"
fi
SHA224=$(echo "This is a simple test" | $CMD)
if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha224"
	echo "$FT_SSL_SHA224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha224"
fi
#############################----------2----------##############################
FT_SSL_SHA224=$(./ft_ssl sha224 -q -s "String test")
if [ "$CMD" == "shasum -a 224" ] ; then
	FT_SSL_SHA224=$FT_SSL_SHA224"  -"
fi
SHA224=$(echo -n "String test" | $CMD)
if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha224 -q -s \"String test\""
	echo "$FT_SSL_SHA224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha224 -q -s \"String test\""
fi
#############################----------3----------##############################
FT_SSL_SHA224=$(cat $(whereis shasum) | ./ft_ssl sha224)
if [ "$CMD" == "shasum -a 224" ] ; then
	FT_SSL_SHA224=$FT_SSL_SHA224"  -"
fi
SHA224=$(cat $(whereis shasum) | $CMD)
if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis shasum) | ./ft_ssl sha224"
	echo "$FT_SSL_SHA224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis shasum) | ./ft_ssl sha224"
fi
#############################----------4----------##############################
FT_SSL_SHA224=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | ./ft_ssl sha224)
if [ "$CMD" == "shasum -a 224" ] ; then
	FT_SSL_SHA224=$FT_SSL_SHA224"  -"
fi
SHA224=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | $CMD)
if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
	echo -e "$GREEN OK: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha224"
	echo "$FT_SSL_SHA224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha224"
fi
#############################----------5----------##############################
FT_SSL_SHA224=$(./ft_ssl sha224 -qs "")
if [ "$CMD" == "shasum -a 224" ] ; then
	FT_SSL_SHA224=$FT_SSL_SHA224"  -"
fi
SHA224=$(echo -n "" | $CMD)
if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha224 -qs \"\""
	echo "$FT_SSL_SHA224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha224 -qs \"\""
fi



if [ "$counter" -eq 5 ]; then
	echo -e "$GREEN [ $counter / 5 ] $RESET"
else
	echo -e "$RED [ $counter / 5 ] $RESET"
fi

################################################################################
sha224_total=$(($sha224_total+$counter))
counter=0
echo -e "$WHITE SHA-224: Test random strings: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA224=$(./ft_ssl sha224 -q file1)
	if [ "$CMD" == "shasum -a 224" ] ; then
		FT_SSL_SHA224=$FT_SSL_SHA224"  -"
	fi
	SHA224=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
		echo -e "       " $CLEAR_LINE
		echo -n -e "$FT_SSL_SHA224\r\c"
		echo -e "$GREEN $counter OK $RESET\r\c"
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
		echo $FT_SSL_SHA224
		echo $SHA224
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
sha224_total=$(($sha224_total+$counter))
counter=0
echo -e "$WHITE SHA-224: Test random binary data: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA224=$(./ft_ssl sha224 -q file2)
	if [ "$CMD" == "shasum -a 224" ] ; then
		FT_SSL_SHA224=$FT_SSL_SHA224"  -"
	fi
	SHA224=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA224" == "$SHA224" ] ; then
		echo -e $CLEAR_LINE
		echo -n -e "$FT_SSL_SHA224\r\c"
		echo -e "$GREEN $counter OK $RESET\r\c"
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
		echo $FT_SSL_SHA224
		echo $SHA224
fi
done
rm file1 file2
sha224_total=$(($sha224_total+$counter))


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
fi



#############################-------SHA-256-------##############################
if [[ ($md5_set -eq 1 || $sha224_set -eq 1) && $sha256_set -eq 1 ]] ; then
	echo ""
	sha256_header
	sleep 1.5
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
#############################----------5----------##############################
FT_SSL_SHA256=$(./ft_ssl sha256 -qs "")
if [ "$CMD" == "shasum -a 256" ] ; then
	FT_SSL_SHA256=$FT_SSL_SHA256"  -"
fi
SHA256=$(echo -n "" | $CMD)
if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha256 -qs \"\""
	echo "$FT_SSL_SHA256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha256 -qs \"\""
fi



if [ "$counter" -eq 5 ]; then
	echo -e "$GREEN [ $counter / 5 ] $RESET"
else
	echo -e "$RED [ $counter / 5 ] $RESET"
fi

################################################################################
sha256_total=$(($sha256_total+$counter))
counter=0
echo -e "$WHITE SHA-256: Test random strings: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA256=$(./ft_ssl sha256 -q file1)
	if [ "$CMD" == "shasum -a 256" ] ; then
		FT_SSL_SHA256=$FT_SSL_SHA256"  -"
	fi
	SHA256=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
		echo -e "       " $CLEAR_LINE
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
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA256=$(./ft_ssl sha256 -q file2)
	if [ "$CMD" == "shasum -a 256" ] ; then
		FT_SSL_SHA256=$FT_SSL_SHA256"  -"
	fi
	SHA256=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA256" == "$SHA256" ] ; then
		echo -e "       " $CLEAR_LINE
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



#############################-------SHA-384-------##############################
if [[ ($md5_set -eq 1 || $sha224_set -eq 1 || $sha256_set -eq 1) && $sha384_set -eq 1 ]] ; then
	echo ""
	sha384_header
	sleep 1.5
elif [ $sha384_set -eq 1 ] ; then
	echo -e $CLEAR_SCREEN
	sha384_header
fi

if [ $sha384_set -eq 1 ] ; then

echo "test" | openssl sha384 > openssl_valid 2>&-
if [ -s openssl_valid ] ; then
	CMD="openssl sha384"
else
	CMD="shasum -a 384"
fi
rm openssl_valid

#############################----------1----------##############################
counter=0
FT_SSL_SHA384=$(echo "This is a simple test" | ./ft_ssl sha384)
if [ "$CMD" == "shasum -a 384" ] ; then
	FT_SSL_SHA384=$FT_SSL_SHA384"  -"
fi
SHA384=$(echo "This is a simple test" | $CMD)
if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha384"
	echo "$FT_SSL_SHA384"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha384"
fi
#############################----------2----------##############################
FT_SSL_SHA384=$(./ft_ssl sha384 -q -s "String test")
if [ "$CMD" == "shasum -a 384" ] ; then
	FT_SSL_SHA384=$FT_SSL_SHA384"  -"
fi
SHA384=$(echo -n "String test" | $CMD)
if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha384 -q -s \"String test\""
	echo "$FT_SSL_SHA384"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha384 -q -s \"String test\""
fi
#############################----------3----------##############################
FT_SSL_SHA384=$(cat $(whereis shasum) | ./ft_ssl sha384)
if [ "$CMD" == "shasum -a 384" ] ; then
	FT_SSL_SHA384=$FT_SSL_SHA384"  -"
fi
SHA384=$(cat $(whereis shasum) | $CMD)
if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis shasum) | ./ft_ssl sha384"
	echo "$FT_SSL_SHA384"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis shasum) | ./ft_ssl sha384"
fi
#############################----------4----------##############################
FT_SSL_SHA384=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | ./ft_ssl sha384)
if [ "$CMD" == "shasum -a 384" ] ; then
	FT_SSL_SHA384=$FT_SSL_SHA384"  -"
fi
SHA384=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | $CMD)
if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
	echo -e "$GREEN OK: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha384"
	echo "$FT_SSL_SHA384"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha384"
fi
#############################----------5----------##############################
FT_SSL_SHA384=$(./ft_ssl sha384 -qs "")
if [ "$CMD" == "shasum -a 384" ] ; then
	FT_SSL_SHA384=$FT_SSL_SHA384"  -"
fi
SHA384=$(echo -n "" | $CMD)
if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha384 -qs \"\""
	echo "$FT_SSL_SHA384"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha384 -qs \"\""
fi



if [ "$counter" -eq 5 ]; then
	echo -e "$GREEN [ $counter / 5 ] $RESET"
else
	echo -e "$RED [ $counter / 5 ] $RESET"
fi

################################################################################
sha384_total=$(($sha384_total+$counter))
counter=0
echo -e "$WHITE SHA-384: Test random strings: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA384=$(./ft_ssl sha384 -q file1)
	if [ "$CMD" == "shasum -a 384" ] ; then
		FT_SSL_SHA384=$FT_SSL_SHA384"  -"
	fi
	SHA384=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA384\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
		echo $FT_SSL_SHA384
		echo $SHA384
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
sha384_total=$(($sha384_total+$counter))
counter=0
echo -e "$WHITE SHA-384: Test random binary data: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA384=$(./ft_ssl sha384 -q file2)
	if [ "$CMD" == "shasum -a 384" ] ; then
		FT_SSL_SHA384=$FT_SSL_SHA384"  -"
	fi
	SHA384=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA384" == "$SHA384" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA384\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
		echo $FT_SSL_SHA384
		echo $SHA384
fi
done
rm file1 file2
sha384_total=$(($sha384_total+$counter))


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
fi



#############################-------SHA-512-------##############################
if [[ ($md5_set -eq 1 || $sha224_set -eq 1 || $sha256_set -eq 1 || $sha384_set -eq 1) && $sha512_set -eq 1 ]] ; then
	echo ""
	sha512_header
	sleep 1.5
elif [ $sha512_set -eq 1 ] ; then
	echo -e $CLEAR_SCREEN
	sha512_header
fi

if [ $sha512_set -eq 1 ] ; then

echo "test" | openssl sha512 > openssl_valid 2>&-
if [ -s openssl_valid ] ; then
	CMD="openssl sha512"
else
	CMD="shasum -a 512"
fi
rm openssl_valid

#############################----------1----------##############################
counter=0
FT_SSL_SHA512=$(echo "This is a simple test" | ./ft_ssl sha512)
if [ "$CMD" == "shasum -a 512" ] ; then
	FT_SSL_SHA512=$FT_SSL_SHA512"  -"
fi
SHA512=$(echo "This is a simple test" | $CMD)
if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha512"
	echo "$FT_SSL_SHA512"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha512"
fi
#############################----------2----------##############################
FT_SSL_SHA512=$(./ft_ssl sha512 -q -s "String test")
if [ "$CMD" == "shasum -a 512" ] ; then
	FT_SSL_SHA512=$FT_SSL_SHA512"  -"
fi
SHA512=$(echo -n "String test" | $CMD)
if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha512 -q -s \"String test\""
	echo "$FT_SSL_SHA512"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha512 -q -s \"String test\""
fi
#############################----------3----------##############################
FT_SSL_SHA512=$(cat $(whereis shasum) | ./ft_ssl sha512)
if [ "$CMD" == "shasum -a 512" ] ; then
	FT_SSL_SHA512=$FT_SSL_SHA512"  -"
fi
SHA512=$(cat $(whereis shasum) | $CMD)
if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis shasum) | ./ft_ssl sha512"
	echo "$FT_SSL_SHA512"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis shasum) | ./ft_ssl sha512"
fi
#############################----------4----------##############################
FT_SSL_SHA512=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | ./ft_ssl sha512)
if [ "$CMD" == "shasum -a 512" ] ; then
	FT_SSL_SHA512=$FT_SSL_SHA512"  -"
fi
SHA512=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | $CMD)
if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
	echo -e "$GREEN OK: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha512"
	echo "$FT_SSL_SHA512"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha512"
fi
#############################----------5----------##############################
FT_SSL_SHA512=$(./ft_ssl sha512 -qs "")
if [ "$CMD" == "shasum -a 512" ] ; then
	FT_SSL_SHA512=$FT_SSL_SHA512"  -"
fi
SHA512=$(echo -n "" | $CMD)
if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha512 -qs \"\""
	echo "$FT_SSL_SHA512"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha512 -qs \"\""
fi



if [ "$counter" -eq 5 ]; then
	echo -e "$GREEN [ $counter / 5 ] $RESET"
else
	echo -e "$RED [ $counter / 5 ] $RESET"
fi

################################################################################
sha512_total=$(($sha512_total+$counter))
counter=0
echo -e "$WHITE SHA-512: Test random strings: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA512=$(./ft_ssl sha512 -q file1)
	if [ "$CMD" == "shasum -a 512" ] ; then
		FT_SSL_SHA512=$FT_SSL_SHA512"  -"
	fi
	SHA512=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA512\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
		echo $FT_SSL_SHA512
		echo $SHA512
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
sha512_total=$(($sha512_total+$counter))
counter=0
echo -e "$WHITE SHA-512: Test random binary data: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA512=$(./ft_ssl sha512 -q file2)
	if [ "$CMD" == "shasum -a 512" ] ; then
		FT_SSL_SHA512=$FT_SSL_SHA512"  -"
	fi
	SHA512=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA512" == "$SHA512" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA512\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
		echo $FT_SSL_SHA512
		echo $SHA512
fi
done
rm file1 file2
sha512_total=$(($sha512_total+$counter))


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
fi



#############################-------SHA-512/224-------##########################
if [[ ($md5_set -eq 1 || $sha224_set -eq 1 || $sha256_set -eq 1 || $sha384_set -eq 1 || $sha512_set -eq 1) && $sha512224_set -eq 1 ]] ; then
	echo ""
	sha512224_header
	sleep 1.5
elif [ $sha512224_set -eq 1 ] ; then
	echo -e $CLEAR_SCREEN
	sha512224_header
fi

if [ $sha512224_set -eq 1 ] ; then

echo "test" | openssl sha512224 > openssl_valid 2>&-
if [ -s openssl_valid ] ; then
	CMD="openssl sha512224"
else
	CMD="shasum -a 512224"
fi
rm openssl_valid

#############################----------1----------##############################
counter=0
FT_SSL_SHA512224=$(echo "This is a simple test" | ./ft_ssl sha512224)
if [ "$CMD" == "shasum -a 512224" ] ; then
	FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
fi
SHA512224=$(echo "This is a simple test" | $CMD)
if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha512224"
	echo "$FT_SSL_SHA512224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha512224"
fi
#############################----------2----------##############################
FT_SSL_SHA512224=$(./ft_ssl sha512224 -q -s "String test")
if [ "$CMD" == "shasum -a 512224" ] ; then
	FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
fi
SHA512224=$(echo -n "String test" | $CMD)
if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha512224 -q -s \"String test\""
	echo "$FT_SSL_SHA512224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha512224 -q -s \"String test\""
fi
#############################----------3----------##############################
FT_SSL_SHA512224=$(cat $(whereis shasum) | ./ft_ssl sha512224)
if [ "$CMD" == "shasum -a 512224" ] ; then
	FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
fi
SHA512224=$(cat $(whereis shasum) | $CMD)
if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis shasum) | ./ft_ssl sha512224"
	echo "$FT_SSL_SHA512224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis shasum) | ./ft_ssl sha512224"
fi
#############################----------4----------##############################
FT_SSL_SHA512224=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | ./ft_ssl sha512224)
if [ "$CMD" == "shasum -a 512224" ] ; then
	FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
fi
SHA512224=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | $CMD)
if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
	echo -e "$GREEN OK: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha512224"
	echo "$FT_SSL_SHA512224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha512224"
fi
#############################----------5----------##############################
FT_SSL_SHA512224=$(./ft_ssl sha512224 -qs "")
if [ "$CMD" == "shasum -a 512224" ] ; then
	FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
fi
SHA512224=$(echo -n "" | $CMD)
if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha512224 -qs \"\""
	echo "$FT_SSL_SHA512224"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha512224 -qs \"\""
fi



if [ "$counter" -eq 5 ]; then
	echo -e "$GREEN [ $counter / 5 ] $RESET"
else
	echo -e "$RED [ $counter / 5 ] $RESET"
fi

################################################################################
sha512224_total=$(($sha512224_total+$counter))
counter=0
echo -e "$WHITE SHA-512/224: Test random strings: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA512224=$(./ft_ssl sha512224 -q file1)
	if [ "$CMD" == "shasum -a 512224" ] ; then
		FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
	fi
	SHA512224=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA512224\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
		echo $FT_SSL_SHA512224
		echo $SHA512224
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
sha512224_total=$(($sha512224_total+$counter))
counter=0
echo -e "$WHITE SHA-512/224: Test random binary data: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA512224=$(./ft_ssl sha512224 -q file2)
	if [ "$CMD" == "shasum -a 512224" ] ; then
		FT_SSL_SHA512224=$FT_SSL_SHA512224"  -"
	fi
	SHA512224=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA512224" == "$SHA512224" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA512224\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
		echo $FT_SSL_SHA512224
		echo $SHA512224
fi
done
rm file1 file2
sha512224_total=$(($sha512224_total+$counter))


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi
fi



#############################-------SHA-512/256-------##########################
if [[ ($md5_set -eq 1 || $sha224_set -eq 1 || $sha256_set -eq 1 || $sha384_set -eq 1 || $sha512_set -eq 1 || $sha512224_set -eq 1) && $sha512256_set -eq 1 ]] ; then
	echo ""
	sha512256_header
	sleep 1.5
elif [ $sha512256_set -eq 1 ] ; then
	echo -e $CLEAR_SCREEN
	sha512256_header
fi

if [ $sha512256_set -eq 1 ] ; then

echo "test" | openssl sha512256 > openssl_valid 2>&-
if [ -s openssl_valid ] ; then
	CMD="openssl sha512256"
else
	CMD="shasum -a 512256"
fi
rm openssl_valid

#############################----------1----------##############################
counter=0
FT_SSL_SHA512256=$(echo "This is a simple test" | ./ft_ssl sha512256)
if [ "$CMD" == "shasum -a 512256" ] ; then
	FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
fi
SHA512256=$(echo "This is a simple test" | $CMD)
if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
	echo -e "$GREEN OK: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha512256"
	echo "$FT_SSL_SHA512256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo \"This is a simple test\" | ./ft_ssl sha512256"
fi
#############################----------2----------##############################
FT_SSL_SHA512256=$(./ft_ssl sha512256 -q -s "String test")
if [ "$CMD" == "shasum -a 512256" ] ; then
	FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
fi
SHA512256=$(echo -n "String test" | $CMD)
if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha512256 -q -s \"String test\""
	echo "$FT_SSL_SHA512256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha512256 -q -s \"String test\""
fi
#############################----------3----------##############################
FT_SSL_SHA512256=$(cat $(whereis shasum) | ./ft_ssl sha512256)
if [ "$CMD" == "shasum -a 512256" ] ; then
	FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
fi
SHA512256=$(cat $(whereis shasum) | $CMD)
if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
	echo -e "$GREEN OK: $RESET" "cat $(whereis shasum) | ./ft_ssl sha512256"
	echo "$FT_SSL_SHA512256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "cat $(whereis shasum) | ./ft_ssl sha512256"
fi
#############################----------4----------##############################
FT_SSL_SHA512256=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | ./ft_ssl sha512256)
if [ "$CMD" == "shasum -a 512256" ] ; then
	FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
fi
SHA512256=$(echo -n "LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz" | $CMD)
if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
	echo -e "$GREEN OK: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha512256"
	echo "$FT_SSL_SHA512256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "echo -n \"LJa0ugxQ/qEGzPeGEveyOmWDKi4Hyix1vunr2Lbz\" | ./ft_ssl sha512256"
fi
#############################----------5----------##############################
FT_SSL_SHA512256=$(./ft_ssl sha512256 -qs "")
if [ "$CMD" == "shasum -a 512256" ] ; then
	FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
fi
SHA512256=$(echo -n "" | $CMD)
if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
	echo -e "$GREEN OK: $RESET" "./ft_ssl sha512256 -qs \"\""
	echo "$FT_SSL_SHA512256"
	counter=$((counter+1))
else
	echo -e "$RED KO: $RESET" "./ft_ssl sha512256 -qs \"\""
fi



if [ "$counter" -eq 5 ]; then
	echo -e "$GREEN [ $counter / 5 ] $RESET"
else
	echo -e "$RED [ $counter / 5 ] $RESET"
fi

################################################################################
sha512256_total=$(($sha512256_total+$counter))
counter=0
echo -e "$WHITE SHA-512/256: Test random strings: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | base64 | head -c 40 > file1
	FT_SSL_SHA512256=$(./ft_ssl sha512256 -q file1)
	if [ "$CMD" == "shasum -a 512256" ] ; then
		FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
	fi
	SHA512256=$(cat file1 | $CMD)
	if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA512256\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## string: " ; cat file1 ; echo ""
		echo $FT_SSL_SHA512256
		echo $SHA512256
	fi
done


if [ "$counter" -eq 100 ]; then
	echo -e $CLEAR_LINE
	echo -e "$GREEN [ $counter / 100 ] $RESET"
else
	echo -e "$RED [ $counter / 100 ] $RESET"
fi

################################################################################
sha512256_total=$(($sha512256_total+$counter))
counter=0
echo -e "$WHITE SHA-512/256: Test random binary data: $RESET"
sleep 1
for i in {1..100}; do
	cat /dev/urandom | head -c 40 > file2
	FT_SSL_SHA512256=$(./ft_ssl sha512256 -q file2)
	if [ "$CMD" == "shasum -a 512256" ] ; then
		FT_SSL_SHA512256=$FT_SSL_SHA512256"  -"
	fi
	SHA512256=$(cat file2 | $CMD)
	if [ "$FT_SSL_SHA512256" == "$SHA512256" ] ; then
		if [ $(tput cols) -lt 128 ] ; then
			echo -e "$GREEN $counter OK $RESET\r\c"
		else
			echo -e "       " $CLEAR_LINE
			echo -n -e "$FT_SSL_SHA512256\r\c"
			echo -e "$GREEN $counter OK $RESET\r\c"
		fi
		counter=$((counter+1))
	else
		echo -e $CLEAR_LINE
		echo -e "$RED KO $RESET" ; echo "## data: " ; cat file2 ; echo ""
		echo $FT_SSL_SHA512256
		echo $SHA512256
fi
done
rm file1 file2
sha512256_total=$(($sha512256_total+$counter))


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
		echo -e -n "│ MD5 score: $GREEN         [ $md5_total / 214 ] $RESET"
		if [ $md5_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $md5_total -gt 9 && $md5_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $md5_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ MD5 score: $RED         [ $md5_total / 214 ] $RESET"
		if [ $md5_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $md5_total -gt 9 && $md5_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $md5_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi

if [ $sha224_set -eq 1 ] ; then
	if [ $sha224_total -eq 205 ] ; then
		echo -e -n "│ SHA-224 score: $GREEN     [ $sha224_total / 205 ] $RESET"
		if [ $sha224_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha224_total -gt 9 && $sha224_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha224_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ SHA-224 score: $RED     [ $sha224_total / 205 ] $RESET"
		if [ $sha224_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha224_total -gt 9 && $sha224_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha224_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi

if [ $sha256_set -eq 1 ] ; then
	if [ $sha256_total -eq 205 ] ; then
		echo -e -n "│ SHA-256 score: $GREEN     [ $sha256_total / 205 ] $RESET"
		if [ $sha256_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha256_total -gt 9 && $sha256_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha256_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ SHA-256 score: $RED     [ $sha256_total / 205 ] $RESET"
		if [ $sha256_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha256_total -gt 9 && $sha256_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha256_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi

if [ $sha384_set -eq 1 ] ; then
	if [ $sha384_total -eq 205 ] ; then
		echo -e -n "│ SHA-384 score: $GREEN     [ $sha384_total / 205 ] $RESET"
		if [ $sha384_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha384_total -gt 9 && $sha384_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha384_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ SHA-384 score: $RED     [ $sha384_total / 205 ] $RESET"
		if [ $sha384_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha384_total -gt 9 && $sha384_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha384_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi

if [ $sha512_set -eq 1 ] ; then
	if [ $sha512_total -eq 205 ] ; then
		echo -e -n "│ SHA-512 score: $GREEN     [ $sha512_total / 205 ] $RESET"
		if [ $sha512_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha512_total -gt 9 && $sha512_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha512_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ SHA-512 score: $RED     [ $sha512_total / 205 ] $RESET"
		if [ $sha512_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha512_total -gt 9 && $sha512_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha512_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi

if [ $sha512224_set -eq 1 ] ; then
	if [ $sha512224_total -eq 205 ] ; then
		echo -e -n "│ SHA-512/224 score: $GREEN [ $sha512224_total / 205 ] $RESET"
		if [ $sha512224_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha512224_total -gt 9 && $sha512224_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha512224_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ SHA-512/224 score: $RED [ $sha512224_total / 205 ] $RESET"
		if [ $sha512224_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha512224_total -gt 9 && $sha512224_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha512224_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi

if [ $sha512256_set -eq 1 ] ; then
	if [ $sha512256_total -eq 205 ] ; then
		echo -e -n "│ SHA-512/256 score: $GREEN [ $sha512256_total / 205 ] $RESET"
		if [ $sha512256_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha512256_total -gt 9 && $sha512256_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha512256_total -gt 99 ] ; then
			echo "                   │"
		fi
	else
		echo -e -n "│ SHA-512/256 score: $RED [ $sha512256_total / 205 ] $RESET"
		if [ $sha512256_total -lt 10 ] ; then
			echo "                     │"
		elif [[ $sha512256_total -gt 9 && $sha512256_total -lt 100 ]] ; then
			echo "                    │"
		elif [ $sha512256_total -gt 99 ] ; then
			echo "                   │"
		fi
	fi
fi




echo "└──────────────────────────────────────────────────────┘"
