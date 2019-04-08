#!/bin/bash

## ENCODE ##

echo "ENCODING:"

BASE64=$(echo -n "a" | base64)
FT_SSL_BASE64=$(echo -n "a" | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo OK
else
	echo KO
fi

BASE64=$(echo -n "ab" | base64)
FT_SSL_BASE64=$(echo -n "ab" | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo OK
else
	echo KO
fi

BASE64=$(echo "abcdefg" | base64)
FT_SSL_BASE64=$(echo "abcdefg" | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo OK
else
	echo KO
fi

BASE64=$(cat /bin/ls | base64)
FT_SSL_BASE64=$(cat /bin/ls | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo OK
else
	echo KO
fi

cat /dev/urandom | head -c $RANDOM > file1

BASE64=$(cat file1 | base64)
FT_SSL_BASE64=$(cat file1 | ./ft_ssl base64)
if [ "$BASE64" == "$FT_SSL_BASE64" ] ; then
	echo OK
else
	echo KO
fi

rm file1

## DECODE ##

echo "DECODING:"

echo "1234" | ./ft_ssl base64 -d > file1
echo "1234" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
echo KO "echo \"1234\" | ./ft_ssl base64 -d > file1"

fi

echo "padding test=" | ./ft_ssl base64 -d > file1
echo "padding test=" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"padding test=\" | ./ft_ssl base64 -d"
fi

echo "aa==" | ./ft_ssl base64 -d > file1
echo "aa==" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"aa==\" | ./ft_ssl base64 -d"
fi

echo "" | ./ft_ssl base64 -d > file1
echo "" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"\" | ./ft_ssl base64 -d"
fi

echo "=aaaaaa=" | ./ft_ssl base64 -d > file1
echo "=aaaaaa=" | openssl enc -base64 -d > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"\" | ./ft_ssl base64 -d"
fi

echo "1234567" | ./ft_ssl base64 -d > file1 # should be padded
echo "1234567=" | base64 -D > file2 # base64 doesn't pad when decoding
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"1234567\" | ./ft_ssl base64 -d"
fi


echo "this is a a    TEST14" | ./ft_ssl base64 -d > file1 #should be padded by 2
echo "this is a a    TEST14==" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "\"this is a a    TEST14\" | ./ft_ssl base64 -d"
fi


echo "12345" | ./ft_ssl base64 -d > file1 # should be truncated
echo "12345" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"12345\" | ./ft_ssl base64 -d"
fi

echo "12345=" | ./ft_ssl base64 -d > file1 # should be truncated
echo "12345=" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"12345=\" | ./ft_ssl base64 -d"
fi

echo "123456=" | ./ft_ssl base64 -d > file1 # should be padded
echo "123456==" | base64 -D > file2 # base64 doesn't pad improperly padded input
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"123456=\" | ./ft_ssl base64 -d"
fi

echo "12345==" | ./ft_ssl base64 -d > file1 # should be truncated
echo "1234" | base64 -D > file2 # base64 would throw error
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"12345==\" | ./ft_ssl base64 -d"
fi

echo "a==" | ./ft_ssl base64 -d > file1
echo "a==" | base64 -D > file2
FILE1=$(./ft_ssl md5 -q file1)
FILE2=$(./ft_ssl md5 -q file2)
if [ "$FILE1" == "$FILE2" ] ; then
	echo OK
else
	echo KO "echo \"a==\" | ./ft_ssl base64 -d"
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
	echo OK
else
	echo KO
fi

echo $FILE1 $FILE2
cat file_encoded | tail -c 100
cat file_encoded | wc
rm -f file1 file2 ft_ssl_encoded new_ft_ssl file_encoded
