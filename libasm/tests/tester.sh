#! /bin/bash

CC="/usr/local/bin/nasm"
CFLAGS="-f macho64"

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

run_edge_test () {
	# # 1 = test file   2 = output file   3 = buffer size   4 = source directory   5 = main
	# printf $YELLOW"Testing with a BUFFER_SIZE of "$3" "$RESET
	# $CC $CFLAGS -I"$4" -D BUFFER_SIZE=$3 $5 $4/*.c
	# ./a.out $1 > "${0%/*}/logs/$2"
	# DIFF=$(diff ${0%/*}/logs/$2 ${0%/*}/logs/expected/$2)
	# if [[ $DIFF ]]; then
	# 	printf "\t❌"
	# 	ret=0
	# else
	# 	printf "\t✅"
	# fi
	# printf "\n"
}

run_test () {
	# # 1 = test file   2 = output file   3 = buffer size   4 = source directory   5 = main
	# printf $YELLOW"Testing with a BUFFER_SIZE of "$3" "$RESET
	# $CC $CFLAGS -I"$4" -D BUFFER_SIZE=$3 $5 $4/*.c
	# ./a.out $1 > "${0%/*}/logs/$2"
	# DIFF=$(diff ${0%/*}/logs/$2 ${0%/*}/logs/expected/buffer_size_.out)
	# if [[ $DIFF ]]; then
	# 	printf "\t❌"
	# 	ret=0
	# else
	# 	printf "\t✅"
	# fi
	# printf "\n"
}

test_stdin () {
	# # 1 = source directory   2 = main
	# printf $YELLOW"Testing stdin (pass 'exit' to exit):\n"$RESET
	# $CC $CFLAGS -I"$1" -D BUFFER_SIZE=1 $2 $1/*.c
	# ./a.out
}

run_tests () {
	# # 1 = source directory   2 = main   3 = test file(s)
	# local ret=1
	# run_edge_test "$3" "buffer_size_-1.out" "-1" "${0%/*}/$1" "$2"
	# run_edge_test "$3" "buffer_size_0.out" "0" "${0%/*}/$1" "$2"
	# run_test "$3" "buffer_size_1.out" "1" "${0%/*}/$1" "$2"
	# run_test "$3" "buffer_size_8.out" "8" "${0%/*}/$1" "$2"
	# run_test "$3" "buffer_size_32.out" "32" "${0%/*}/$1" "$2"
	# run_test "$3" "buffer_size_9999.out" "9999" "${0%/*}/$1" "$2"
	# run_test "$3" "buffer_size_1000000.out" "1000000" "${0%/*}/$1" "$2"
	# if [[ $ret -ne 0 ]]; then
	# 	cat "${0%/*}/files/pass"
	# 	printf "\n"$CYAN$BOLD"\t\t\t\tWell done!\n"$RESET
	# else
	# 	cat "${0%/*}/files/fail"
	# 	printf "\n"$CYAN$BOLD"\t\t\t\tTry again!\n"$RESET
	# fi
	# printf $HONEY"Test stdin? [Y/n]: "$RESET
	# read -n 1 ans
	# printf "\n"
	# if [[ $ans != "n" ]]; then
	# 	test_stdin "${0%/*}/$1" "$2"
	# fi
}

mkdir "${0%/*}/logs" > /dev/null 2>&1

if [[ $# -eq 0 ]]; then
	print_header
	# printf $CYAN$BOLD"++++ MANDATORY ++++\n"$RESET
	# echo
	# run_tests ".." "${0%/*}/main.c" "${0%/*}/files/pass"
elif [[ $# -eq 1 && $1 = "-b" ]]; then
	print_header
	# printf $CYAN$BOLD"++++++ BONUS ++++++\n"$RESET
	# echo
	# run_tests "../bonus" "${0%/*}/main_bonus.c" "${0%/*}/files/file1 ${0%/*}/files/file2"		
fi

rm -f a.out
