#! /bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"

# compile main with ft::vector
clang++ -Wall -Wextra -Werror -g main.cpp -D NAMESPACE=ft -D FT=1 -o main.ft.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error main.ft.out\n"$RESET
    exit 1
fi

# compile main with std::vector
clang++ -Wall -Wextra -Werror -g main.cpp -D NAMESPACE=std -D FT=0 -o main.std.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error main.std.out\n"$RESET
    exit 1
fi

# run main.ft.out and save output to main.ft.output
printf $YELLOW"running main.ft.out...\n"$RESET
if [[ $1 = "-v" ]]
then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.out ./main.ft.out
else
    START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    ./main.ft.out
    END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    echo "elapsed time ft: $(($END_TIME - $START_TIME)) ms"
fi

# run main.std.out and save output to main.std.output
printf $YELLOW"running main.std.out...\n"$RESET
START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
./main.std.out
END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
echo "elapsed time std: $(($END_TIME - $START_TIME)) ms"

# # compare ft::vector output to std::vector output
printf $YELLOW"comparing ft::vector to std::vector output...\n\n"$RESET
diff --text output.ft.out output.std.out > diff.out
if [[ $? = 0 ]]
then
    printf $GREEN"no differences found\n"$RESET
else
    printf $YELLOW"differences found:\n"$RESET
    printf $YELLOW"------------------\n"$RESET
    cat -e diff.out
fi