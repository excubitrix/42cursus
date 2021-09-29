# :large_orange_diamond: Libft &ensp; [![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/floogman/Libft)](https://github.com/JaeSeoKim/badge42)

This is the very first project of the 2019 42cursus. Its aim is to code a C library that contains an extract of useful standard library functions.

## :small_orange_diamond: Instructions

1. Run
```
make
```
for a library containing only the mandatory functions or
```
make bonus
```
for a library containing all functions.

2. Link the resulting library `libft.a` using the `-L`/`-l` flags.
```
gcc -Wall -Wextra -Werror -L. -lft main.c
```

## :small_orange_diamond: Resources
- [Linux Man Pages](https://linux.die.net/man/)
- [Create a Library w/ ar](https://www.ibm.com/docs/en/zos/2.4.0?topic=descriptions-ar-create-maintain-library-archives)
### GCC
- [-L / -l Option Flags](https://www.rapidtables.com/code/linux/gcc/gcc-l.html)
### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
### README.md
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
