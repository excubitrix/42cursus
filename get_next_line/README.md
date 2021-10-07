# :large_orange_diamond: get_next_line &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/get_next_line)

The aim of this project is to learn about static variables by coding a getline-esque function that returns a line ending with a newline, read from a file descriptor.

## :small_orange_diamond: Instructions

1. (optional) Change the size of the buffer in the Makefile.

2. Run `make` for a library containing the mandatory version or `make bonus` for a library containing the bonus version.

3. Link the resulting library `libgnl.a` using the `-L`/`-l` flags.

```
gcc -Wall -Wextra -Werror -L. -lgnl main.c
```

![make_gnl](https://user-images.githubusercontent.com/59726559/136330810-b0c6d175-89ec-462b-88df-b6268446874e.gif)

## :small_orange_diamond: Tester

To test the mandatory version, run the `tester.sh` located in `./tests` without arguments.

```
./tests/tester.sh
```

To test the bonus version, add the `-b` flag.

```
./tests/tester.sh -b
```

![gnl_tester](https://user-images.githubusercontent.com/59726559/136174280-9fb42087-0f56-4d66-8d58-fd42a4dabeea.gif)

## :small_orange_diamond: Resources
- [Static Variables In C](https://www.geeksforgeeks.org/static-variables-in-c/)
#### ar
- [Create or Maintain Library Archives](https://www.ibm.com/docs/en/zos/2.4.0?topic=descriptions-ar-create-maintain-library-archives)
#### GCC
- [-D Option Flag](https://www.rapidtables.com/code/linux/gcc/gcc-d.html)
- [-L / -l Option Flags](https://www.rapidtables.com/code/linux/gcc/gcc-l.html)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### Tester
- [Bash Scripting Cheatsheet](https://devhints.io/bash)
- [Check Emoji](https://emojipedia.org/check-mark-button/)
- [Cross Emoji](https://emojipedia.org/cross-mark/)
- [Ascii Art](https://www.asciiart.eu/animals/other-land)
#### README.md
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
