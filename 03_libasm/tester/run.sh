#! /bin/bash

CC="gcc"
CFLAGS="-Wall -Wextra -Werror"
LINKS="-I${0%/*} -L${0%/*}/.. -lasm"

YELLOW="\033[0;33m"
CYAN="\033[0;36m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"

print_header () {
	printf $HONEY"┌─┐┬┌┬┐┌─┐┬  ┌─┐\n"
	printf $HONEY"└─┐││││├─┘│  ├┤ \n"
	printf $HONEY"└─┘┴┴ ┴┴  ┴─┘└─┘\n"
	printf $HONEY"╔╗   ╔╗╔════╗  ╔═╗ ╔═══╗╔═╗  ╔═╗\n"
	printf $HONEY"║║   ║║║ ╔═╗╚╗╔╝ ╚╗║╔═╗║║ ╚╗╔╝ ║\n"
	printf $HONEY"║║   ║║║ ╚═╝╔╝║╔═╗║║║ ╚╝║╔╗╚╝╔╗║\n"
	printf $HONEY"║║   ║║║ ╔═╗╚╗║╚═╝║╚╩═╦╗║║╚══╝║║\n"
	printf $HONEY"║║ ╔╗║║║ ║ ║ ║║╔═╗║╔╗ ║║║║    ║║\n"
	printf $HONEY"║╚═╝║║║║ ╚═╝╔╝║║ ║║║╚═╝║║║    ║║\n"
	printf $HONEY"╚═══╝╚╝╚════╝ ╚╝ ╚╝╚═══╝╚╝    ╚╝\n"
	printf $HONEY"┌┬┐┌─┐┌─┐┌┬┐┌─┐┬─┐\n"
	printf $HONEY" │ ├┤ └─┐ │ ├┤ ├┬┘\n"
	printf $HONEY" ┴ └─┘└─┘ ┴ └─┘┴└─\n\n"$RESET
}

mkdir "${0%/*}/logs" > /dev/null 2>&1

if [[ $# -eq 0 ]]; then
	print_header
	printf $CYAN$BOLD"++++ MANDATORY ++++\n"$RESET
	echo
	make -C "${0%/*}/.."
	# make -f "${0%/*}/../Makefile"
	$CC $CFLAGS $LINKS ${0%/*}/main.c ${0%/*}/tests.c ${0%/*}/utils.c
	./a.out | tee "${0%/*}/logs/results"
elif [[ $# -eq 1 && $1 = "-b" ]]; then
	print_header
	printf $CYAN$BOLD"++++++ BONUS ++++++\n"$RESET
	echo
	make -C "${0%/*}/.." bonus
	# make -f "${0%/*}/../Makefile" bonus
	$CC $CFLAGS $LINKS ${0%/*}/main_bonus.c ${0%/*}/tests_bonus.c ${0%/*}/ft_atoi_base_c.c ${0%/*}/utils.c
	./a.out | tee "${0%/*}/logs/results_bonus"
fi

rm -f a.out
