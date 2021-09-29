#! /bin/bash

CC="gcc"
CFLAGS="-Wall -Wextra -Werror"

YELLOW="\033[0;33m"
CYAN="\033[0;36m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"

print_header () {
	printf $HONEY"┌─┐┬┌┬┐┌─┐┬  ┌─┐\n"
	printf $HONEY"└─┐││││├─┘│  ├┤ \n"
	printf $HONEY"└─┘┴┴ ┴┴  ┴─┘└─┘\n"
	printf $HONEY"╔═══╗╔═╗ ╔╗╔╗   \n"
	printf $HONEY"║╔═╗║║ ╚╗║║║║   \n"
	printf $HONEY"║║ ╚╝║╔╗╚╝║║║   \n"
	printf $HONEY"║║╠╦╗║║╚╗ ║║║ ╔╗\n"
	printf $HONEY"║╚═╝║║║ ║ ║║╚═╝║\n"
	printf $HONEY"╚═══╝╚╝ ╚═╝╚═══╝\n"
	printf $HONEY"┌┬┐┌─┐┌─┐┌┬┐┌─┐┬─┐\n"
	printf $HONEY" │ ├┤ └─┐ │ ├┤ ├┬┘\n"
	printf $HONEY" ┴ └─┘└─┘ ┴ └─┘┴└─\n\n"$RESET
}

run_test () {
	# 1 = test file   2 = output file   3 = buffer size   4 = source directory   5 = main
	printf $YELLOW"testing with a BUFFER_SIZE of "$3"\n"$RESET
	$CC $CFLAGS -I"$4" -D BUFFER_SIZE=$3 $5 $4/*.c
	./a.out $1 > "${0%/*}/logs/$2"
	printf "\n"
}

run_tests () {
	# 1 = source directory   2 = main
	run_test "${0%/*}/test.txt" "buffer_size_-1.txt" "-1" "${0%/*}/$1" "$2"
	run_test "${0%/*}/test.txt" "buffer_size_0.txt" "0" "${0%/*}/$1" "$2"
	run_test "${0%/*}/test.txt" "buffer_size_1.txt" "1" "${0%/*}/$1" "$2"
	run_test "${0%/*}/test.txt" "buffer_size_8.txt" "8" "${0%/*}/$1" "$2"
	run_test "${0%/*}/test.txt" "buffer_size_32.txt" "32" "${0%/*}/$1" "$2"
	run_test "${0%/*}/test.txt" "buffer_size_9999.txt" "9999" "${0%/*}/$1" "$2"
	run_test "${0%/*}/test.txt" "buffer_size_1000000.txt" "1000000" "${0%/*}/$1" "$2"
}

mkdir "${0%/*}/logs" > /dev/null 2>&1

if [[ $# -eq 0 ]]; then
	print_header
	printf $CYAN$BOLD"++++ MANDATORY ++++\n"$RESET
	echo
	run_tests ".." "${0%/*}/main.c"
elif [[ $# -eq 1 && $1 = "-b" ]]; then
	print_header
	printf $CYAN$BOLD"++++++ BONUS ++++++\n"$RESET
	echo
	run_tests "../bonus" "${0%/*}/main_bonus.c"
fi

rm -f a.out
