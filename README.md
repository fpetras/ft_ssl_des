# ft_ssl_md5

An introduction to cryptographic hashing algorithms

This project consists of recoded versions of the message-digest algorithm MD5 and the entire SHA-2 family of hash functions.

Built from the ground up using only these functions:

* open, close
* read, write
* malloc, free
* strerror, exit

## Installation:

`git clone https://github.com/fpetras/ft_ssl_md5.git && cd ft_ssl_md5 && make`

## Usage:

```
usage: ./ft_ssl <command> [options] [<arg>...]

COMMANDS:
     md5
     sha224 sha256 sha384 sha512 sha512224 sha512256

OPTIONS
     -p            echo stdin to stdout and append checksum to stdout
     -q            quiet mode
     -r            reverse the format of the output
     -s string     print the sum of the given string
```

## Examples:

Placeholder

### GIF:

Placeholder

### Test script:

Test the hash functions by running

`./test.sh <command>...`

or

`make test[_<command>]`

## FAQ:

**Q:** Why is the code structured so strangely?

**A:** It follows the set of rules described in this document: [Norm](https://github.com/fpetras/42-documents/blob/master/norm.en.pdf "norm.en.pdf")

**Q:** How do the hash algorithms work?

**A:** Refer to Wikipedia to get a quick overview:

https://en.wikipedia.org/wiki/MD5

https://en.wikipedia.org/wiki/SHA-2

On top of that, these documents provide an excellent in-depth description of the SHA-2 algorithms:

http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf

https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

## Code snippet:

Placeholder

## [Subject](https://github.com/fpetras/42-subjects/blob/master/ft_ssl_md5.en.pdf "ft_ssl_md5.en.pdf")
