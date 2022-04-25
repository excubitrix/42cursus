# :large_orange_diamond: libasm &ensp; ![42Project Score](https://badge42.vercel.app/api/v2/cl2etis99004009mnrj7l8h9o/project/2079040)

The objective of this project is to get familiar with assembly language.

## :small_orange_diamond: Instructions

1. Make sure [nasm](https://www.nasm.us/) is installed.
	- You can check this by running the following command in your terminal:
	```
	which nasm
	```
	- If it's missing, nasm can be installed via homebrew:
	```
	brew install nasm
	```

2. Run `make` for a library including only the mandatory functions and `make bonus` for a library including all functions.
```
make
```

## :small_orange_diamond: Testing

To test the mandatory functions, execute the `run.sh` script located in the `./tester` directory without arguments.
```
./tester/run.sh
```

To test the bonus functions, add the `-b` flag.
```
./tester/run.sh -b
```

## :small_orange_diamond: Resources
#### NASM
- [Install nasm (Netwide Assembler) on Mac with Brew](https://brewinstall.org/install-nasm-on-mac-with-brew/)
- [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
#### x86-64 Assembly
- [Assembly Programming Tutorial](https://www.tutorialspoint.com/assembly_programming/index.htm)
- [Intel vs. AT&T syntax](http://staffwww.fullcoll.edu/aclifton/courses/cs241/syntax.html)
- [Registers in x86 Assembly](https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html)
- [x86 and amd64 Instruction Reference](https://www.felixcloutier.com/x86/index.html)
- [macOS 64-bit System Call Table](https://fossies.org/linux/radare/libr/syscall/d/darwin-x86-64.sdb.txt)
- [When should I use the RSP register to add space to the stack?](https://stackoverflow.com/questions/55422522/when-should-i-use-the-rsp-register-to-add-space-to-the-stack)
- [What is the best way to set a register to zero in x86 assembly: xor, mov or and?](https://stackoverflow.com/questions/33666617/what-is-the-best-way-to-set-a-register-to-zero-in-x86-assembly-xor-mov-or-and)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### Attributions
- Dynamically generated score badge by [badge42](https://github.com/JaeSeoKim/badge42)
