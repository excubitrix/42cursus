# :large_orange_diamond: get_next_line &ensp; [![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/floogman/get_next_line)](https://github.com/JaeSeoKim/badge42)

The aim of this project is to code a function that returns a line ending with a newline, read from a file descriptor.

## :small_orange_diamond: Instructions

1. Run
```
make
```
for a library containing the mandatory version or
```
make bonus
```
for a library containing the bonus version.

2. Link the resulting library `libgnl.a` using the `-L`/`-l` flags.
```
gcc -Wall -Wextra -Werror -L. -lgnl main.c
```

## :small_orange_diamond: Tester

To test the mandatory version, run the `tester.sh` located in `./tests` without arguments.
```
./tests/tester.sh
```
To test the bonus version, add the `-b` flag.
```
./tests/tester.sh -b
```

## :small_orange_diamond: Resources
### GCC
- [-D Option Flag](https://www.rapidtables.com/code/linux/gcc/gcc-d.html)
- [-L / -l Option Flags](https://www.rapidtables.com/code/linux/gcc/gcc-l.html)
### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
### Bash Scripting
- [Cheatsheet](https://devhints.io/bash)
### README.md
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
