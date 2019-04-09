#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
WHITE="\033[1;37m"
RESET="\033[0;0m"

base64_set=0
base64url_set=0

function ctrl_c {
	rm -f file1 file2 ft_ssl_encoded new_ft_ssl file_encoded url_test decoded
	exit $?
}

function print_usage {
	echo "usage: $0 <test>..."
	echo ""
	echo "available tests: base64"
	echo "                 base64url"
	echo "                 all"
}

if [ $# -eq 0 ] ; then
	print_usage
	exit 1
fi

for arg in "$@" ; do
	case $arg in
		base64)
			base64_set=1
			;;
		base64url)
			base64url_set=1
			;;
		all)
			base64_set=1
			base64url_set=1
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

## BASE64 ENCODE ##
if [ $base64_set -eq 1 ] ; then

echo -e "$WHITE BASE64 ENCODING: $RESET"

BASE64=$(echo -n "a" | base64)
FT_SSL_BASE64=$(echo -n "a" | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

BASE64=$(echo -n "ab" | base64)
FT_SSL_BASE64=$(echo -n "ab" | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

BASE64=$(echo "abcdefg" | base64)
FT_SSL_BASE64=$(echo "abcdefg" | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

BASE64=$(cat /bin/ls | base64)
FT_SSL_BASE64=$(cat /bin/ls | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

cat /dev/urandom | head -c $RANDOM > file1

BASE64=$(cat file1 | base64)
FT_SSL_BASE64=$(cat file1 | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

rm file1


## BASE64 DECODE ##

echo -e "$WHITE BASE64 DECODING: $RESET"

echo "1234" | ./ft_ssl base64 -d > file1
echo "1234" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"1234\" | ./ft_ssl base64 -d > file1"

fi

echo "padding test=" | ./ft_ssl base64 -d > file1
echo "padding test=" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"padding test=\" | ./ft_ssl base64 -d"
fi

echo "aa==" | ./ft_ssl base64 -d > file1
echo "aa==" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"aa==\" | ./ft_ssl base64 -d"
fi

echo "" | ./ft_ssl base64 -d > file1
echo "" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"\" | ./ft_ssl base64 -d"
fi

echo "=aaaaaa=" | ./ft_ssl base64 -d > file1 # should be error
echo "=aaaaaa=" | openssl enc -base64 -d > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"=aaaaaa=\" | ./ft_ssl base64 -d"
fi

echo "1234567" | ./ft_ssl base64 -d > file1 # should be padded
echo "1234567=" | base64 -D > file2 # base64 doesn't pad when decoding
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"1234567\" | ./ft_ssl base64 -d"
fi


echo "this is a a    TEST14" | ./ft_ssl base64 -d > file1 #should be padded by 2
echo "this is a a    TEST14==" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "\"this is a a    TEST14\" | ./ft_ssl base64 -d"
fi


echo "12345" | ./ft_ssl base64 -d > file1 # should be truncated
echo "12345" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"12345\" | ./ft_ssl base64 -d"
fi

echo "12345=" | ./ft_ssl base64 -d > file1 # should be truncated
echo "12345=" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"12345=\" | ./ft_ssl base64 -d"
fi

echo "123456=" | ./ft_ssl base64 -d > file1 # should be padded
echo "123456==" | base64 -D > file2 # base64 doesn't pad improperly padded input
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"123456=\" | ./ft_ssl base64 -d"
fi

echo "12345==" | ./ft_ssl base64 -d > file1 # should be truncated
echo "1234" | base64 -D > file2 # base64 would throw error
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"12345==\" | ./ft_ssl base64 -d"
fi

echo "a==" | ./ft_ssl base64 -d > file1
echo "a==" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET" "echo \"a==\" | ./ft_ssl base64 -d"
fi


rm file1 file2

cat ft_ssl | ./ft_ssl base64 > ft_ssl_encoded
cat ft_ssl_encoded | ./ft_ssl base64 -d > new_ft_ssl
chmod 744 new_ft_ssl
cat /dev/urandom | head -c $RANDOM > file1
./new_ft_ssl base64 file1 | ./ft_ssl base64 -d > file2
./new_ft_ssl base64 file1 > file_encoded
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)

if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

echo $FILE1 $FILE2
cat file_encoded | tail -c 100
cat file_encoded | wc
rm -f file1 file2 ft_ssl_encoded new_ft_ssl file_encoded

fi



## BASE64 URL ENCODE ##
if [ $base64url_set -eq 1 ] ; then

echo -e "$WHITE BASE64 URL ENCODING: $RESET"

echo "��m��My���׆�Ӈ�y�<�]Z��m��My���׆�Ӈ�y�<�]Z�ƱqSi�C��u�Ɔ�Z�y���8u�n��\u�m]�XF:j��[v����M��	��#=��CE�D �VI�I" > url_test
./ft_ssl base64url -i url_test -o file1
echo "77-977-9be-_ve-_vU1577-977-977-914bvv73Th--_vXnvv70877-9XVrvv73vv71t77-977-9TXnvv73vv73vv73Xhu-_vdOH77-9ee-_vTzvv71dWu-_vcaxcVNp77-9Q--_ve-_vXXvv73Ghu-_vVrvv71577-977-977-9OHXvv71u77-977-9XHXvv71tXe-_vVhGOmrvv73vv71bdu-_ve-_ve-_ve-_vU3vv73vv70J77-977-9Iz3vv73vv71DRe-_vUQg77-9Vknvv71JCg" > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi

## BASE64 URL DECODE ##

echo -e "$WHITE BASE64 URL DECODING: $RESET"

./ft_ssl base64url -d -i file2 -o decoded
FILE1=$(./ft_ssl md5 -q decoded)
FILE2=$(./ft_ssl md5 -q url_test)
if [ "$FILE1" == "$FILE2" ] ; then
	echo -e "$GREEN OK $RESET"
else
	echo -e "$RED KO $RESET"
fi
rm -f file1 file2 url_test decoded

fi
