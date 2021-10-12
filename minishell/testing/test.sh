#! /bin/bash

# NOTES:
	# When running the test with -v, the number of segfaults and sigaborts is unreliable, because when a program is run under valgrind it's environment is altered.

RED="\033[0;31m"
GREEN="\033[0;32m"
HONEY="\e[38;5;214m"
GREY="\e[38;5;245m"
BOLD="\033[1m"
REVERSED="\033[7m"
RESET="\033[0m"

# verify that test is being run from testing directory
CWD=${PWD##*/}
if [[ $CWD != testing ]]
then
	echo "test needs to be run from testing directory"
	exit
fi

printf "\n"
printf $HONEY"╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦    ╔╦╗╔═╗╔═╗╔╦╗╔═╗╦═╗\n"$RESET
printf $HONEY"║║║║║║║║╚═╗╠═╣║╣ ║  ║     ║ ║╣ ╚═╗ ║ ║╣ ╠╦╝\n"$RESET
printf $HONEY"╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝   ╩ ╚═╝╚═╝ ╩ ╚═╝╩╚═\n\n"$RESET

make -C ../ > /dev/null 2>&1

PASSES_OUTPUT=0
FAILS_OUTPUT=0
PASSES_EXIT_STATUS=0
FAILS_EXIT_STATUS=0
PASSES_VALGRIND=0
FAILS_VALGRIND=0
SEGFAULT=0
SIGABRT=0

# flags
ERRORS_ONLY=0
SOLAL=0
MAZOISE=0
T0MM4RX=0
ALL=0
ASCII=0
TEST_EXIT_STATUS=0

FAILS_OUTPUT_REPORT="fails_output.txt"
FAILS_EXIT_STATUS_REPORT="fails_exit_status.txt"
FAILS_VALGRIND_REPORT="fails_valgrind.txt"

rm $FAILS_OUTPUT_REPORT > /dev/null 2>&1
rm $FAILS_EXIT_STATUS_REPORT > /dev/null 2>&1
rm $FAILS_VALGRIND_REPORT > /dev/null 2>&1

# "set traps" so that when the script exits or ctrl+C is pressed, f_exit() is executed first
trap f_exit EXIT
trap f_exit INT

# function that runs the tests
f_tester () {
	
	# ERRORS ONLY OUTPUT MODE
	
	if [[ $ERRORS_ONLY -eq 1 ]]
	then
		# get output and exit status from bash
	    BASH_OUTPUT=$(echo $1"; exit" | bash 2> /dev/null)
	    BASH_EXIT_STATUS=$?
		# get output and exit status from minishell
	    MINISHELL_OUTPUT=$(echo $1"; exit" | $VALGRIND ../minishell 2> /dev/null)
	    MINISHELL_EXIT_STATUS=$?  

		if [[ $MINISHELL_OUTPUT = $BASH_OUTPUT ]]
		then
			OUTPUT_CMP_RES=1
		else
			OUTPUT_CMP_RES=0
		fi

		if [[ $TEST_EXIT_STATUS = 1 ]]
		then
			if [[ $MINISHELL_EXIT_STATUS = $BASH_EXIT_STATUS ]]
			then
				EXIT_STATUS_CMP_RES=1
			else
				EXIT_STATUS_CMP_RES=0
			fi
		fi

		if [[ $VALGRIND ]]
		then
			if [[ $(grep "definitely lost: 0" valgrind-out.txt) \
			&& $(grep "indirectly lost: 0" valgrind-out.txt) \
			&& $(grep "possibly lost: 72" valgrind-out.txt) \
			&& $(grep "still reachable: 200" valgrind-out.txt) \
			|| $(grep "definitely lost: 0" valgrind-out.txt) \
			&& $(grep "indirectly lost: 2,064" valgrind-out.txt) \
			&& $(grep "possibly lost: 0" valgrind-out.txt) \
			&& $(grep "still reachable: 200" valgrind-out.txt) ]]
			then
				VALGRIND_RES=1
			else
				VALGRIND_RES=0
			fi
		fi

		if [[ $OUTPUT_CMP_RES = 0 || $EXIT_STATUS_CMP_RES = 0 || $VALGRIND_RES = 0 ]]
		then
			printf $BOLD; echo $1; printf $RESET
		fi
		# compare outputs
		if [[ $OUTPUT_CMP_RES = 1 ]]
		then
			((PASSES_OUTPUT=PASSES_OUTPUT+1))
		else
			printf $GREY"desired output:\t|"$RESET"$BASH_OUTPUT"$GREY"|\n"$RESET
			printf $GREY"actual output:\t|"$RESET"$MINISHELL_OUTPUT"$GREY"|\n"$RESET
			printf $RED$BOLD"X output $RESET "
			((FAILS_OUTPUT=FAILS_OUTPUT+1))
			echo $1 >> $FAILS_OUTPUT_REPORT
			printf "desired output:\t|$BASH_OUTPUT|\n" >> $FAILS_OUTPUT_REPORT
			printf "actual output:\t|$MINISHELL_OUTPUT|\n\n" >> $FAILS_OUTPUT_REPORT
		fi

		if [[ $TEST_EXIT_STATUS = 1 ]]
		then
			if [[ $EXIT_STATUS_CMP_RES = 1 ]]
			then
				((PASSES_EXIT_STATUS=PASSES_EXIT_STATUS+1))
			else
				printf $RED$BOLD"X exit status (b:$BASH_EXIT_STATUS|m:$MINISHELL_EXIT_STATUS) $RESET "
				((FAILS_EXIT_STATUS=FAILS_EXIT_STATUS+1))
				echo $1 >> $FAILS_EXIT_STATUS_REPORT
				printf "bash's exit status:\t\t\t$BASH_EXIT_STATUS\n" >> $FAILS_EXIT_STATUS_REPORT
				printf "minishell's exit status:\t$MINISHELL_EXIT_STATUS\n\n" >> $FAILS_EXIT_STATUS_REPORT
			fi
		fi

		# check valgrind report if -v flag was given
		if [[ $VALGRIND ]]
		then
			if [[ $VALGRIND_RES = 1 ]]
			then
				((PASSES_VALGRIND=PASSES_VALGRIND+1))
			else
				printf $RED$BOLD"X valgrind $RESET "
				((FAILS_VALGRIND=FAILS_VALGRIND+1))
				echo "$1\n" >> $FAILS_VALGRIND_REPORT
			fi
		fi

		# check if a segfault or abort occured
		if [[ $MINISHELL_EXIT_STATUS = 139 ]]
		then
			printf $RED$BOLD"☠️ SEGFAULT!"$RESET
			((SEGFAULT=SEGFAULT+1))
		fi
		if [[ $MINISHELL_EXIT_STATUS = 134 ]]
		then
			printf $RED$BOLD"☠️ SIGABRT!"$RESET
			((SIGABRT=SIGABRT+1))
		fi
		if [[ $OUTPUT_CMP_RES = 0 || $EXIT_STATUS_CMP_RES = 0 || $VALGRIND_RES = 0 ]]
		then
			printf "\n\n"
		fi
	
	else

		# FULL OUTPUT MODE

		# print test being run
		printf $BOLD; echo $1; printf $RESET
		
		# get output and exit status from bash
		printf $RED
		BASH_OUTPUT=$(echo $1"; exit" | bash)
		BASH_EXIT_STATUS=$?
		printf $RESET
		printf $GREY"desired output:\t|"$RESET"$BASH_OUTPUT"$GREY"|\n"$RESET
		
		# get output and exit status from minishell
		printf $RED
		MINISHELL_OUTPUT=$(echo $1"; exit" | $VALGRIND ../minishell)
		MINISHELL_EXIT_STATUS=$?
		printf $RESET
		printf $GREY"actual output:\t|"$RESET"$MINISHELL_OUTPUT"$GREY"|\n"$RESET

		# compare outputs
		if [[ $MINISHELL_OUTPUT = $BASH_OUTPUT ]]
		then
			# printf $GREY"both outputs:\t|"$RESET"$BASH_OUTPUT"$GREY"|\n"$RESET
			printf $GREEN$BOLD"√ output $RESET"
			((PASSES_OUTPUT=PASSES_OUTPUT+1))
		else
			printf $RED$BOLD"X output $RESET"
			((FAILS_OUTPUT=FAILS_OUTPUT+1))
			echo "$1" >> $FAILS_OUTPUT_REPORT
			printf "desired output:\t|$BASH_OUTPUT|\n" >> $FAILS_OUTPUT_REPORT
			printf "actual output:\t|$MINISHELL_OUTPUT|\n\n" >> $FAILS_OUTPUT_REPORT
		fi

		if [[ $TEST_EXIT_STATUS = 1 ]]
		then
			# compare exit statuses
			if [[ $MINISHELL_EXIT_STATUS = $BASH_EXIT_STATUS ]]
			then
				printf $GREEN$BOLD" √ exit status $RESET"
				((PASSES_EXIT_STATUS=PASSES_EXIT_STATUS+1))
			else
				printf $RED$BOLD" X exit status (b:$BASH_EXIT_STATUS|m:$MINISHELL_EXIT_STATUS)$RESET "
				((FAILS_EXIT_STATUS=FAILS_EXIT_STATUS+1))
				echo "$1" >> $FAILS_EXIT_STATUS_REPORT
				printf "bash's exit status:\t\t\t$BASH_EXIT_STATUS\n" >> $FAILS_EXIT_STATUS_REPORT
				printf "minishell's exit status:\t$MINISHELL_EXIT_STATUS\n\n" >> $FAILS_EXIT_STATUS_REPORT
			fi
		fi

		# check valgrind report if -v flag was given
		if [[ $VALGRIND ]]
		then
			if [[ $(grep "definitely lost: 0" valgrind-out.txt) \
			&& $(grep "indirectly lost: 0" valgrind-out.txt) \
			&& $(grep "possibly lost: 72" valgrind-out.txt) \
			&& $(grep "still reachable: 200" valgrind-out.txt) \
			|| $(grep "definitely lost: 0" valgrind-out.txt) \
			&& $(grep "indirectly lost: 2,064" valgrind-out.txt) \
			&& $(grep "possibly lost: 0" valgrind-out.txt) \
			&& $(grep "still reachable: 200" valgrind-out.txt) ]]
			then
				printf $GREEN$BOLD" √ valgrind "$RESET
				((PASSES_VALGRIND=PASSES_VALGRIND+1))
			else
				printf $RED$BOLD" X valgrind "$RESET
				((FAILS_VALGRIND=FAILS_VALGRIND+1))
				echo "$1\n" >> $FAILS_VALGRIND_REPORT
			fi
		fi
		
		# check if a segfault or abort occured
		if [[ $MINISHELL_EXIT_STATUS = 139 ]]
		then
			printf $RED$BOLD" ☠️ SEGFAULT!"$RESET
			((SEGFAULT=SEGFAULT+1))
		fi
		if [[ $MINISHELL_EXIT_STATUS = 134 ]]
		then
			printf $RED$BOLD" ☠️ SIGABRT!"$RESET
			((SIGABRT=SIGABRT+1))
		fi
		printf "\n\n"

	fi
}

# function that is called before exiting
f_exit() {
	# report test results
	HEADER="RESULTS"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	printf $BOLD"\toutput\t exit status\t valgrind\n"$RESET
	printf $GREEN$BOLD"passes\t$PASSES_OUTPUT\t $PASSES_EXIT_STATUS\t\t $PASSES_VALGRIND\n"$RESET
	printf $RED$BOLD"fails\t$FAILS_OUTPUT\t $FAILS_EXIT_STATUS\t\t $FAILS_VALGRIND\n\n"$RESET
	printf $RED$BOLD"segfaults (exit status 139): $SEGFAULT\n"$RESET
	printf $RED$BOLD"sigaborts (exit status 134): $SIGABRT\n\n"$RESET
	
	# get list of files to delete
	# find files in this directory, ignoring ones that start with "fails" and end with .txt or end with .sh, and remove them
	LIST=$(find . -type f \( ! -iname "fails*.txt" ! -iname "*.sh" \) -exec basename {} \;)
	
	# check if there're any files to delete
	if [[ $(echo $LIST | wc -w) -gt 0 ]]
	then
		# ask if user want to delete the files
		printf "delete the following files?\n$LIST\n"$BOLD$HONEY"(y/n)\n"$RESET

		# get input
		read USER_INPUT

		# check and process input
		if [[ $USER_INPUT = y ]]
		then
			find . -type f \( ! -iname "fails*.txt" ! -iname "*.sh" \) -exec basename {} \; -exec rm -f {} \; > /dev/null 2>&1
		fi
	fi
	
	kill $OBSERVER_PID
	# remove exit trap, so we can call exit without it triggering again
	trap - EXIT
	exit 0
}

f_help() {
	echo "available flags"
	echo "-a: test all characters on the ascii table"
	echo "-v: run tests with valgrind (can take a while)"
	echo "-e: only show the tests that fail"
	echo "-E: also test exit status"
	echo "-s: run only the tests from solaldunckel's minishell-tester"
	echo "-m: run only part of the tests from Mazoise's 42TESTERS-MINISHELL"
	echo "-t: run only the tests from t0mm4rx's minishell_tests"
	echo "-A: run all tests (exluding ascii)"
	trap - EXIT
	exit 0
}

# check and process flags
while getopts haveEsmtA flag
do
	case "${flag}" in
		h)
			f_help
			;;
		a)
			ASCII=1
			;;
		v)
			VALGRIND="valgrind --log-file=valgrind-out.txt"
			;;
		e)
			ERRORS_ONLY=1
			;;
		E)
			TEST_EXIT_STATUS=1
			;;
		s)
			SOLAL=1
			;;
		m)
			MAZOISE=1
			;;
		t)
			T0MM4RX=1
			;;
		A)
			ALL=1
			;;
	esac
done

# function that runs a process that will kill minishell in case it hangs on a test
f_minishell_observer() {
	while :
	do
		# get pid of minishell
		PID1=$(pgrep minishell)
		# wait a moment
		sleep 2
		# get pid of minishell again
		PID2=$(pgrep minishell)
		# if both pids aren't 0 and the pids match, the tester stopped running (usually because the exit command wasn't executed for some reason) so we kill the current running process of minishell so the testing can continue
		if [[ $PID1 && $PID2 && $PID1 = $PID2 ]]
		then
			printf $RED$BOLD"minishell stranded(?); attempting to kill: "$RESET
			if kill $PID1 > /dev/null 2>&1
			then
				printf $RED$BOLD"successful\n"$RESET
			else
				printf $RED$BOLD"failed (likely false alarm)\n"$RESET
			fi
		fi
		sleep 2
	done
}
# start f_minishell_observer in the background
f_minishell_observer &
# store the pid of the process so we can kill it later
OBSERVER_PID=$!

# TESTS ---------------------------------------------------

# test all ASCII characters
if [[ $ASCII = 1 ]]
then
	i=0
	while [[ i -le 127 ]]
	do
		CHAR=$(printf "\x$(printf %x $i)\n")
		f_tester "$CHAR"
		((i=i+1))
	done
	exit 0
fi

if [[ $SOLAL = 0 && $MAZOISE = 0 && $T0MM4RX = 0 ]] || [[ $ALL = 1 ]]
then
	HEADER="ECHO + \$?"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester 'echo test ; echo $?'
	f_tester 'testing ; echo $?'
	f_tester '><> ; echo $?'

	
	HEADER="&& AND ||"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester 'false & echo howdy1!'
	f_tester 'true & echo howdy1!'
	f_tester 'true | echo howdy1!'
	f_tester 'false | echo howdy1!'
	f_tester 'false &| echo howdy1!'
	f_tester 'true &| echo howdy1!'
	f_tester 'true |& echo howdy1!'
	f_tester 'false |& echo howdy1!'
	f_tester 'false & & echo howdy1!'
	f_tester 'true & & echo howdy1!'
	f_tester 'true | | echo howdy1!'
	f_tester 'false | | echo howdy1!'
	f_tester '&& echo howdy1!'
	f_tester '&& echo howdy1!'
	f_tester '|| echo howdy1!'
	f_tester '|| echo howdy1!'
	f_tester '& echo howdy1!'
	f_tester '& echo howdy1!'
	f_tester '| echo howdy1!'
	f_tester '| echo howdy1!'
	f_tester 'false &&'
	f_tester 'true &&'
	f_tester 'true ||'
	f_tester 'false ||'
	f_tester '&&'
	f_tester '&&'
	f_tester '||'
	f_tester '||'
	f_tester 'false &&& echo howdy1!'
	f_tester 'true &&& echo howdy1!'
	f_tester 'true ||| echo howdy1!'
	f_tester 'false ||| echo howdy1!'
	f_tester 'false \&& echo howdy1!'
	f_tester 'true \&& echo howdy1!'
	f_tester 'true \|| echo howdy1!'
	f_tester 'false \|| echo howdy1!'
	f_tester '1 && echo howdy1!'
	f_tester '0 && echo howdy1!'
	f_tester '0 || echo howdy1!'
	f_tester '1 || echo howdy1!'

	f_tester 'false && echo howdy1!'
	f_tester 'true && echo howdy1!'
	f_tester 'true || echo howdy1!'
	f_tester 'false || echo howdy1!'
	f_tester 'false && false && echo howdy1!'
	f_tester 'true && true && echo howdy1!'
	f_tester 'true || true || echo howdy1!'
	f_tester 'false || false || echo howdy1!'
	f_tester 'false && echo howdy1! || false && echo howdy2!'
	f_tester 'true && echo howdy1! || true && echo howdy2!'
	f_tester 'true || echo howdy1! || true || echo howdy2!'
	f_tester 'false || echo howdy1! || false || echo howdy2!'
	f_tester 'false && echo howdy1! && false && echo howdy2!'
	f_tester 'true && echo howdy1! && true && echo howdy2!'
	f_tester 'true || echo howdy1! && true || echo howdy2!'
	f_tester 'false || echo howdy1! && false || echo howdy2!'
	f_tester 'false && echo howdy1! && false && echo howdy2! && false && echo howdy3!'
	f_tester 'true && echo howdy1! && true && echo howdy2! && true && echo howdy3!'
	f_tester 'true || echo howdy1! && true || echo howdy2! && true || echo howdy3!'
	f_tester 'false || echo howdy1! && false || echo howdy2! && false || echo howdy3!'
	f_tester 'false && echo howdy1! || false && echo howdy2! || false && echo howdy3!'
	f_tester 'true && echo howdy1! || true && echo howdy2! || true && echo howdy3!'
	f_tester 'true || echo howdy1! || true || echo howdy2! || true || echo howdy3!'
	f_tester 'false || echo howdy1! || false || echo howdy! || false || echo howdy3!'


	HEADER="ECHO + -n"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester "echo"
	f_tester "echo -n"
	f_tester "echo -n -n"
	f_tester "echo -n -n -n"
	f_tester "echo -n    -n"
	f_tester "echo -n -n test"
	f_tester "echo -test -n"
	f_tester "echo -test -n -n"
	f_tester "echo -n -test"
	f_tester "echo -n -n -test"
	f_tester "echo - n test"
	f_tester "echo --n test"
	f_tester "echo -ntest"
	f_tester "echo-n test"


	HEADER="ECHO + LINE PARSING"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester "echo 'test\"test\"test'"
	f_tester "echo \"test'test'test\""
	f_tester "echo test\"test\"test"
	f_tester "echo test'test'test"
	f_tester 'echo test1"test1"'
	f_tester 'echo"test2 "test2'
	f_tester 'echo "test|test"'
	f_tester 'echo "test | test"'
	f_tester 'echo "test;test"'
	f_tester 'echo "test ; test"'
	f_tester 'echo "test>test"'
	f_tester 'echo "test > test"'
	f_tester 'echo "test3; echo test4"test'
	f_tester "echo 'test5;echo test6'"
	f_tester "echo \"test'7;echo' test8\""
	f_tester "echo t ' e ' s ' t \"9 '"
	f_tester '"echo test 10"'
	f_tester 'echo "test1"test2'
	f_tester 'echo " test3 " test4'
	f_tester 'echo \"test'


	HEADER="ENVIRONMENT VARIABLES"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester 'export a=b ; echo $a'
	f_tester 'echo $ b, $b, "$b"'
	f_tester "echo $ b, \$b, '\$b'"
	f_tester 'export b=a ; echo $ b, $b, "$b"'
	f_tester "export b=a ; echo $ b, \$b, '\$b'"

	printf $HONEY$BOLD"\t❖ env vars + spaces + quotes\n\n"$RESET
	f_tester 'echo test"$a"test'
	f_tester 'export a=b ; echo test"$a"test'
	f_tester "export a=b ; echo test'\$a'test"
	f_tester 'echo test  "$c"test'
	f_tester 'export c=d ; echo test  "$c"test'
	f_tester "echo test  '\$c'test"
	f_tester "export c=d ; echo test  '\$c'test"
	f_tester 'echo test  "  $c  "  test'
	f_tester 'export c=d ; echo test  "  $c  "  test'
	f_tester "echo test  '  \$c  '  test"
	f_tester "export c=d ; echo test  '  \$c  '  test"

	printf $HONEY$BOLD"\t❖ multiple exports in one command\n\n"$RESET
	f_tester 'export a=b b=c ; echo $a $b'
	f_tester 'export a=b b=c c=d ; echo $a $b $c'

	printf $HONEY$BOLD"\t❖ unset\n\n"$RESET
	f_tester 'export a=b ; unset a ;  echo $a'
	f_tester 'export a=b ; unset b ;  echo $a'
	f_tester 'export a=b c=d ; unset a ;  echo $a $c'
	f_tester 'export a=b c=d ; unset a c ;  echo $a $c'


	HEADER="REDIRECTIONS"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester 'echo test > file ; cat file ; rm file'
	f_tester 'echo test> file ; cat file ; rm file'
	f_tester 'echo test >file ; cat file ; rm file'
	f_tester 'echo test>file ; cat file ; rm file'
	f_tester 'echo test>file;cat file ; rm file'
	f_tester 'echo test1 > file ; echo test2 >> file ; cat file ; rm file'
	f_tester 'echo test1 > file ; echo test2 >> file ; echo test3 > file ; cat file ; rm file'
	f_tester 'echo test1 > file ; echo test2 >> file ; cat file ; rm file'
	f_tester 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'

	printf $HONEY$BOLD"\t❖ redirection symbol at beginning\n\n"$RESET
	f_tester '> file echo test ; cat file ; rm file'
	f_tester '>file echo test ; cat file ; rm file'
	f_tester '>file echo test ; >>file echo test ; cat file ; rm file'
	f_tester '>file echo test;cat file ; rm file'
	f_tester ' > file echo test1 ; >> file echo test2 ; cat file ; rm file'
	f_tester '> file echo test1 ; >> file echo test2 ;> file  echo test3 ; cat file ; rm file'
	f_tester '>file echo test ; >> file echo test1 ; >> file echo test2 ;> file  echo test3 ; cat file ; rm file'

	printf $HONEY$BOLD"\t❖ file with function name\n\n"$RESET
	f_tester '> cat echo test ; cat cat ; rm cat'
	f_tester '>cat echo test ; cat cat ; rm cat'
	f_tester '>cat echo test;cat cat ; rm cat'
	f_tester ' > cat echo test1 ; >> cat echo test2 ; cat cat ; rm cat'
	f_tester '> cat echo test1 ; >> cat echo test2 ;> cat  echo test3 ; cat cat ; rm cat'

	printf $HONEY$BOLD"\t❖ redirection with fd to redirect from\n\n"$RESET
	f_tester '1> file echo test ; rm file'
	f_tester '1> file echo test ; cat file ; rm file'
	f_tester '2> file echo test ; rm file'
	f_tester '2> file echo test ; cat file ; rm file'
	f_tester '3> file echo test ; rm file'
	f_tester '3> file echo test ; cat file ; rm file'
	f_tester '99> file echo test ; rm file'
	f_tester '99> file echo test ; cat file ; rm file'
	f_tester '2147483647> file echo test ; rm file'
	f_tester '2147483647> file echo test ; cat file ; rm file'
	f_tester '-1> file echo test ; rm file'
	f_tester '-1> file echo test ; cat file ; rm file'

	printf $HONEY$BOLD"\t❖ redirection fuckery (mandatory?)\n\n"$RESET
	f_tester 'echo test > ls ; cat ls'
	f_tester 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
	f_tester '> lol echo test lol; cat lol'
	f_tester '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
	f_tester 'cat < ls'
	f_tester 'cat < ls > ls'
	rm ls lol test > /dev/null 2>&1
	# ADD TESTS THAT SWITCH BETWEEN FDS

	# printf $HONEY$BOLD"\t❖ fd aggregation (not mandatory) + fuckery\n\n"$RESET
	# f_tester '2>&1 file echo test'
	# f_tester '>&1 file echo test'
	# f_tester '2>& file echo test'
	# f_tester '2>&99 file echo test'
	# f_tester '99>&1 file echo test'
	# f_tester '-1>&1 file echo test'
	# f_tester '2>&-1 file echo test'
	# f_tester '2 >&1 file echo test'
	# f_tester '2> &1 file echo test'
	# f_tester '2>& 1 file echo test'
	# f_tester '2>&1file echo test'
	# f_tester '2 >&1file echo test'
	# f_tester '2> &1file echo test'
	# f_tester '2>& 1file echo test'
	# rm file > /dev/null 2>&1

	printf $HONEY$BOLD"\t❖ redirection + \\ \n\n"$RESET
	f_tester 'echo test \> file'
	f_tester 'echo test >\ file ; cat " file" ; rm " file"'
	f_tester 'echo test > \file ; cat file ; rm file'
	f_tester 'echo test \1> file ; cat file ; rm file'
	f_tester 'echo test 1\> file'
	f_tester 'echo test 1> \file ; cat file ; rm file'


	HEADER="FUNCTIONS"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester 'touch file file2 file3'
	f_tester 'chmod 000 file2'
	f_tester 'echo test > file2'
	f_tester 'chmod 777 file2'
	f_tester 'ls -al > file2'
	f_tester 'cat file2'
	f_tester 'cat file2 | head -3'
	f_tester 'cat file2 | tail -3'
	f_tester 'grep "file" file2'
	f_tester 'grep -w "file" file2'
	rm file file2 file3 > /dev/null 2>&1
	f_tester 'ls .. > file ; cat file | head -6 > file2 ; cat file2 | tail -3 > file3 ; cat file3 | wc -c > file4 ; cat file4 ; rm file file2 file3 file4'
	# rm file*

	printf $HONEY$BOLD"\t❖ more cd testing\n\n"$RESET
	f_tester 'cd .. ; pwd'
	f_tester 'cd /Users ; pwd'
	f_tester 'cd ; pwd'
	f_tester 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'


	# HEADER="FILE EXECUTION w abs. & rel. paths"
	# PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	# printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	# f_tester 'touch file.sh ; echo echo Hello from within file.sh! > file.sh ; chmod 777 file.sh ; ./file.sh'
	# f_tester '$PWD/file.sh'
	# f_tester 'mkdir testing_sub ; cd testing_sub ; ../file.sh'
	# f_tester 'mkdir -p testing_sub/testing_sub_2 ; cd testing_sub/testing_sub_2 ; ../../file.sh'
	# f_tester 'mv file.sh testing_sub ; ./testing_sub/file.sh'
	# f_tester 'mv testing_sub/file.sh testing_sub/testing_sub_2 ; ./testing_sub/testing_sub_2/file.sh'
	# rm -rf testing_sub > /dev/null 2>&1


	HEADER="SYNTAX ERRORS"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET
	f_tester '<'
	f_tester '<<'
	f_tester '<<<'
	f_tester '< < <'
	f_tester '>'
	f_tester '>>'
	f_tester '>>>'
	f_tester '> > >'
	f_tester '><'
	f_tester '> <'
	f_tester '<>'
	f_tester '< >'
	f_tester 'echo <'
	f_tester 'echo > >'
	f_tester 'echo <<'
	f_tester 'echo ><'
	f_tester 'echo > <'
	f_tester 'echo <>'
	f_tester 'echo < >'
	f_tester 'echo |>'
	f_tester ';; test'
	f_tester '| test'
	f_tester 'echo | |'

	f_tester '2>1 file echo test'
	rm file > /dev/null 2>&1

	f_tester '><> file echo test'
	rm file 1 > /dev/null 2>&1
fi

if [[ $SOLAL = 1 || $ALL = 1 ]]
then
	HEADER="SOLALDUNCKEL'S MINISHELL-TESTER TESTS"
	PADDING=$(echo $(((42 - ${#HEADER}) / 2)))
	printf $HONEY$BOLD$REVERSED"\n%-"$PADDING"s $HEADER %"$PADDING"s\n\n"$RESET

	printf $HONEY$BOLD"\t❖ echo tests\n\n"$RESET
	f_tester 'echo test tout'
	f_tester 'echo test      tout'
	f_tester 'echo -n test tout'
	f_tester 'echo -n -n -n test tout'

	printf $HONEY$BOLD"\t❖ cd tests\n\n"$RESET
	f_tester 'cd .. ; pwd'
	f_tester 'cd /Users ; pwd'
	f_tester 'cd ; pwd'
	f_tester 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'

	printf $HONEY$BOLD"\t❖ pipe tests\n\n"$RESET
	f_tester 'cat tests/lorem.txt | grep arcu | cat -e'

	if [[ $VALGRIND = 0 ]]
	then
		f_tester 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
		f_tester 'cat /dev/random | head -c 100 | wc -c'
		f_tester 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
		f_tester 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
	fi
	
	printf $HONEY$BOLD"\t❖ env expansions + escape\n\n"$RESET
	f_tester 'echo test     \    test'
	f_tester 'echo \"test'
	f_tester 'echo $TEST'
	f_tester 'echo "$TEST"'
	f_tester "echo '$TEST'"
	f_tester 'echo "$TEST$TEST$TEST"'
	f_tester 'echo "$TEST$TEST=lol$TEST"'
	f_tester 'echo "   $TEST lol $TEST"'
	f_tester 'echo $TEST$TEST$TEST'
	f_tester 'echo $TEST$TEST=lol$TEST""lol'
	f_tester 'echo    $TEST lol $TEST'
	f_tester 'echo test "" test "" test'
	f_tester 'echo "\$TEST"'
	f_tester 'echo "$=TEST"'
	f_tester 'echo "$"'
	f_tester 'echo "$?TEST"'
	f_tester 'echo $TEST $TEST'
	f_tester 'echo "$1TEST"'
	f_tester 'echo "$T1TEST"'

	printf $HONEY$BOLD"\t❖ env expansions\n\n"$RESET
	ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
	EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
	f_tester 'export ='
	f_tester 'export 1TEST= ;' $ENV_SHOW
	f_tester 'export TEST ;' $EXPORT_SHOW
	f_tester 'export ""="" ; ' $ENV_SHOW
	f_tester 'export TES=T="" ;' $ENV_SHOW
	f_tester 'export TE+S=T="" ;' $ENV_SHOW
	f_tester 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
	f_tester 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
	f_tester 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
	# f_tester $ENV_SHOW
	# f_tester $EXPORT_SHOW
	f_tester 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

	printf $HONEY$BOLD"\t❖ redirections\n\n"$RESET
	f_tester 'echo test > ls ; cat ls'
	f_tester 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
	f_tester '> lol echo test lol; cat lol'
	f_tester '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
	f_tester 'cat < ls'
	f_tester 'cat < ls > ls'

	printf $HONEY$BOLD"\t❖ multi tests\n\n"$RESET
	f_tester 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'

	printf $HONEY$BOLD"\t❖ syntax error\n\n"$RESET
	f_tester ';; test'
	f_tester '| test'
	f_tester 'echo > <'
	f_tester 'echo | |'
	f_tester '<'

	printf $HONEY$BOLD"\t❖ exit\n\n"$RESET
	f_tester "exit 42"
	f_tester "exit 42 53 68"
	f_tester "exit 259"
	f_tester "exit 9223372036854775807"
	f_tester "exit -9223372036854775808"
	f_tester "exit 9223372036854775808"
	f_tester "exit -9223372036854775810"
	f_tester "exit -4"
	f_tester "exit wrong"
	f_tester "exit wrong_command"
	f_tester "gdagadgag"
	f_tester "ls -Z"
	f_tester "cd gdhahahad"
	f_tester "ls -la | wtf"

	rm lol ls test
fi

if [[ $MAZOISE = 1 || $ALL = 1 ]]
then
	printf $HONEY$BOLD"\t❖ Mazoise's 42TESTERS-MINISHELL tests\n\n"$RESET
	f_tester "echo hello"
	f_tester "echo -n hello"
	f_tester "echo -n hello      world"
	f_tester "echo \"coucou\"lala"
	f_tester "echo \"coucou\"\'lala\'"
	f_tester "echo -n \"hello      world\""
	f_tester "echo \"-n \"hello      world\"\""
	f_tester "echo \"-n hello      world\""
	f_tester "echo -n hello; echo \"world\""
	f_tester "echo hello; echo   -n     world; echo !"
	# f_tester "echo \"\\\\\""
	# f_tester "echo \"\\n \\n \\n\""
	# f_tester "echo \"\\n \\\\n \\\\\n\""
	f_tester "echo hello\";\"world"
	f_tester "echo hello \";  \"  world"
	f_tester "echo hello -n \\n world -n;"
	f_tester "echo hello > yours/tmp1.txt"
	f_tester "echo bijour > yours/tmp1.txt"
	f_tester "echo yo >> yours/tmp1.txt"
	f_tester "echo coucou >> yours/tmp2.txt"
	f_tester "echo $PWD"
	f_tester "echo \"$PWD\""
	f_tester "echo \'$PWD\'"
	f_tester "echo $\"PWD\""
	f_tester "echo $\'PWD\'"
	f_tester "echo coucou; echo $?"
	f_tester 'echo bonjour; echo -n je suis; echo gentil; echo $?'
	f_tester "echo -n -n One\"argument\"'lo'l; echo \"n\"''ee\"d\"more'?'''\"'\";"
	f_tester "pwd"

	# echo "env" | ./minishell | grep -v ^_= | LC_ALL=C sort
	# echo "export" | ./minishell | grep -v ^"declare -x _=" | LC_ALL=C sort
	f_tester "export PWD=coucou; echo $PWD"
	# echo "export COUCOU=lala LALA=coucou coucou=lulu le12la=truc _12=truc a_a=bada ____=lolo _1_1=ololo bada= relele ; echo $?; env" | ./minishell  | grep -v ^_= | LC_ALL=C sort
	# echo "export COUCOU=lala LALA=coucou; unset COUCOU LALA truc; echo $?; env" | ./minishell  | grep -v ^_= | LC_ALL=C sort
	f_tester "cd ..; echo $PWD; pwd"
	f_tester "/bin/ls"
	f_tester "ls"
	# ./minishell < srcs/cmds.txt
	f_tester "bash < srcs/cmds.txt >> yours/tmp3.txt"
	f_tester "bash srcs/cmds.txt >> yours/tmp3.txt"
	f_tester "echo \"echo coucou\" | bash"
	f_tester "echo \"echo coucou\" | ./minishell"
	f_tester "env | grep PWD"
	f_tester "cd $HOME; ls"
	f_tester 'cat tester.sh | grep echo | wc; exit | echo RECKT | cat; cat tester.sh | sort'
	f_tester 'cat tester.sh | grep echo; echo $?; cat tester.sh | grep RECKT | wc; echo $?'
	f_tester 'cat tester.sh | cat | cat | cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat'
	# echo "echo export | bash" | ./minishell | LC_ALL=C sort
	# echo "bash ; export" | ./minishell | LC_ALL=C sort
	# echo "./minishell ; export" | ./minishell | LC_ALL=C sort
	f_tester "export PATH=$PWD/srcs/test1:$PWD/srcs/test2:$PATH ; testexecpath"
	f_tester "export PATH=$PWD/srcs/test2:$PWD/srcs/test1:$PATH ; testexecpath"
	f_tester "export PATH=.:$PWD/srcs/test1:$PWD/srcs/test2:$PATH ; cd srcs/test3; testexecpath"
	f_tester "cat < srcs/cmds.txt"
	# cat srcs/cmds.txt | ./minishell

	printf $HONEY$BOLD"\t❖ error tests\n\n"$RESET
	f_tester "echolala lol"
	f_tester "; ;"
	f_tester "| |"
	f_tester "echo coucou ; ;"
	f_tester "echo coucou | |"
	f_tester "echo coucou ; echo lala ; ;"
	f_tester "echo coucou | echo lala | |"
fi

if [[ $T0MM4RX = 1 || $ALL = 1 ]]
then
	printf $HONEY$BOLD"\t❖ t0mm4rx's minishell_tests\n\n"$RESET
	f_tester 'echo bonjour ; |'
	f_tester 'echo bonjour | |'
	f_tester '|'
	f_tester 'echo bonjour |;'
	f_tester 'echo bonjour ; ls'
	f_tester 'echo bonjour > test\ 1'
	f_tester 'cd $HOME/Documents'
	# f_tester 'echo "\s" & echo "\s"'
	f_tester 'echo >'
	f_tester 'echo -n -n -nnnn -nnnnm'
	# f_tester 'cat /dev/random | head -n 1 | cat -e'
	f_tester 'unset var1 # with undefined var1'
	f_tester 'export "" et unset ""'
	f_tester 'echo test > file test1'
	f_tester '$'
	f_tester 'not_cmd bonjour > salut'
	f_tester 'env puis export puis env' # vars aren't sorted
	# f_tester 'cat Makefile | grep pr | head -n 5 | cd test (mybin)' # check status code
	# f_tester 'cat Makefile | grep pr | head -n 5 | cat test (bin)' # check status code
	# f_tester 'cat Makefile | grep pr | head -n 5 | hello (NA)' # check status code
	f_tester 'echo bonjour >>> test'
	f_tester 'echo bonjour > > out'
	f_tester 'echo 2 >> out1 > out2'
	f_tester 'echo 2 > out1 >> out2'
	f_tester 'cat < test' # with non-existent test
	f_tester 'export var; export var=test'
	f_tester 'echo bonjour > $test' # with test not defined
	f_tester 'file_name_in_current_dir'
	f_tester 'cd ../../../../../.. ; pwd'
	# f_tester 'ctrl-C . 130 sur bin(ex : sleep 10)&line vide'
	# f_tester 'ctrl-\ .131 sur bin'
	f_tester 'echo "bip | bip ; coyotte > < " "'
	f_tester 'cat | cat | cat | ls' # check outputs order
	f_tester '$bla' # with bla not defined
	f_tester 'export var ="cat Makefile | grep >"'
	f_tester 'export "test=ici"=coucou'
	f_tester 'c$var Makefile' # with var=at
	f_tester '$LESS$VAR'
	f_tester '/bin/echo bonjour'
	f_tester 'not_cmd'
	# f_tester 'sleep 5 | exit'
	f_tester 'echo bonjour > $test w/ t'
	f_tester '"exit retour a la ligne"'
	f_tester 'minishell' # binary not in path without "./" before
	f_tester 'cat diufosgid' # check exit code
	f_tester 'exit' # should return the last exit code value
	f_tester 'exit -10'
	f_tester 'exit +10'
	f_tester ';'
	f_tester 'echo coucou | ;'
	f_tester 'echo "$HOME"'
	f_tester "echo '$HOME'"
	# f_tester 'export ; env' # display is different for both commands
	f_tester 'echo $HOME'
	f_tester '> log echo coucou'
	f_tester 'echo hudifg d | | hugdfihd'
	f_tester 'echo'
	f_tester 'echo simple'
	f_tester 'echo -n simple'
	f_tester 'echo '''
	f_tester 'echo ""'
	f_tester 'echo "\"'
	# f_tester 'echo "\n \n \n"'
	# f_tester 'echo "\n \n \\n"'
	f_tester 'echo ;;'
	f_tester 'echo hi";" hihi'
	f_tester 'echo hi " ; " hihi'
	f_tester 'cd'
	f_tester 'cd .'
	f_tester 'cd ~'
	f_tester 'cd /'
	f_tester 'cd no_file'
	f_tester 'cd a b c d'
	f_tester 'pwd a'
	f_tester 'pwd a b c d'
	f_tester 'export LOL=lala ROR=rara'
	f_tester 'unset LOL ROR'
	f_tester 'export "HI= hi"'
	f_tester 'export "HI =hi"'
	f_tester '/bin/ls'
	# f_tester '# write something the press ctrl+c'
	# f_tester '# write something then press ctrl+d'
	# f_tester '# write something then press ctrl+\'
	f_tester 'echo $?'
	f_tester 'l^Ds'
	f_tester 'echo |'
	f_tester '| echo'
	f_tester 'sort | ls' # check output order
	f_tester 'cat < >'
	f_tester 'cat < <'
	f_tester 'cat > >'
	f_tester '> a ls > b < Makefile'
	f_tester 'echo > a Hello World!'
	f_tester '> a echo Hello World!'
	f_tester 'cat < Makefile | grep gcc > output'
	f_tester 'exit 0 | exit 1'
	f_tester 'exit 1 | exit 0'
fi