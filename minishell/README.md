# :large_orange_diamond: minishell &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/minishell)

Minishell is a group project for a team of two students. Its objective is to create a simple shell.

|  | Team Member
|:-|:-----------:
![minishell](https://user-images.githubusercontent.com/59726559/136932417-21c8fe83-0e32-4a90-a64d-b26129187add.gif) | <a href="https://github.com/magalifabri"><sub><img src="https://avatars.githubusercontent.com/u/65071369?v=4" alt="mfabri" width="250"/><br/></sub><sub><b>mfabri</b></sub></a>

## :small_orange_diamond: Instructions

Run `make` or `make bonus` to compile and `./minishell` to launch the shell.<br>

## :small_orange_diamond: Features
- The prompt shown when waiting for a new command, is the name of the current directory.
- Commands are searched and launched as they are in bash (based on the PATH variable or by using a relative or an absolute path).
- The following commands are build-in:
 - `echo` with option `-n`
 - `cd` with no argument or a relative or an absolte path
 - `pwd` without any options
 - `export` without any options
 - `unset` without any options
 - `env` without any options or arguments
 - `exit` without any options
- Commands can be separated by `;`, `&`, `&&` or `||`. However, `&` will have the same effect as `;`.
- Quotes `'` and `"` as they work in bash.
- Redirections `<`, `>` and `>>` as they work in bash with the exception of file descriptor aggregation.
- Pipes `|` as they work in bash with the exception of multiline commands.
- Environment variables as they work in in bash.
- `$?` as it works in bash.
- ctrl-C, ctrl-D and ctrl-\ have the same result as they do in bash.
- The up and down arrow keys allow for the user to navigate through the histroy, which can then be edited.
- Custom key sequences that act like [home] and [end].
- Copy and paste up to fifty characters at a time.
- Write and edit multiline commands.
- Wildcard `*` as it works in bash.

## :small_orange_diamond: RESOURCES:

## :small_orange_diamond: Resources
- [Guide to Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Understandin Shell Syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Example Shell](https://github.com/Swoorup/mysh)
- [Creating a Pipe](https://www.gnu.org/software/libc/manual/html_node/Creating-a-Pipe.html)
- [$_](https://unix.stackexchange.com/questions/280453/understand-the-meaning-of)
#### Bonus
- [Wildcard Expansion](https://man7.org/linux/man-pages/man3/glob.3.html)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
