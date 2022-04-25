# :large_orange_diamond: push_swap &ensp; ![42Project Score](https://badge42.vercel.app/api/v2/cl2etis99004009mnrj7l8h9o/project/2126465)

The objective of this project is to sort data on a stack, using the lowest possible number of actions.

## :small_orange_diamond: Description

This project consists of two programs: `checker` and `push_swap`.

The `checker` program takes as an argument stack A formatted as a list of intergers and will then wait and read instructions from stdin. Once all instructions have been read, checker will display 'OK' or 'KO' depending on whether or not the list of instructions was successful in sorting stack A.

The `push_swap` program takes as an argument also stack A formatted as a list of intergers and will then display the smallest list of instructions it can muster to sort stack A (with the smallest number being at the top).

## :small_orange_diamond: Instructions

1. Run `make` or `make bonus` to compile both programs.
```
make
```

2. Execute the progams separately
    - `./<program> "<list of intergers>"`
    ```
    ./push_swap "4 9 2"
    ```

    or together
    - `ARG="<list of intergers>"; ./push_swap $ARG | ./checker $ARG`
    ```
    ARG="4 9 2"; ./push_swap $ARG | ./checker $ARG
    ```

The number of instructions outputted by *push_swap* can be counted using wc like this:<br>
`ARG="<list of intergers>"; ./push_swap $ARG | wc -l`
```
ARG="4 9 2"; ./push_swap $ARG | wc -l
```

## :small_orange_diamond: Sneak Peek

Mandatory | Bonus Flags -scp | Bonus Flags -sc(p)g
:--------:|:----------------:|:-----------------:
![push_swap](https://user-images.githubusercontent.com/59726559/136754541-5d42ff30-3b35-4f64-9237-5ee721f8dbc2.gif) | ![push_swap_bonus_p](https://user-images.githubusercontent.com/59726559/136754751-4481b204-f041-47dd-80ec-46fceb8f8317.gif) | ![push_swap_bonus_g](https://user-images.githubusercontent.com/59726559/136755420-277733fc-3a60-4d7c-9f99-28384b6d13ed.gif)

## :small_orange_diamond: Bonus Flags

Flags should be used as follows:<br>
`ARG="<list of intergers>"; ./<program> [flags] $ARG`<br>
```
ARG="4 9 2"; ./push_swap -sc $ARG
```
or `ARG="<list of intergers>"; ./push_swap $ARG | ./checker [flags] $ARG`
```
ARG="4 9 2"; ./push_swap $ARG | ./checker -scpvg $ARG
```

Flag | Description | push_swap | checker
:---:|:-----------:|:---------:|:-------:
`-s` | print the total number of steps (i.e. instructions) taken | ✅ | ✅
`-c` | make the output more colorful | ✅ | ✅
`-p` | display the stacks after each instruction, each time overwriting the previous output | ❌ | ✅
`-v` | display the stacks after each instruction without overwriting the previous output | ❌ | ✅
`-g` | display the stacks after each instruction but as a graph | ❌ | ✅

## :small_orange_diamond: Resources
- [Divide and Conquer Algorithm](https://www.geeksforgeeks.org/divide-and-conquer-algorithm-introduction/)
- [Example Strategy](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
#### Bonus
- [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)
#### Tools
- [Number Generator](https://numbergenerator.org/randomnumbergenerator#!numbers=60&low=-50&high=50&unique=true&csv=&oddeven=&oddqty=0&sorted=false&addfilters=)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
- [Check Emoji](https://emojipedia.org/check-mark-button/)
- [Cross Emoji](https://emojipedia.org/cross-mark/)
#### Attributions
- Dynamically generated score badge by [badge42](https://github.com/JaeSeoKim/badge42)
