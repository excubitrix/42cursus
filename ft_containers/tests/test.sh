#! /bin/bash

# compile main with ft::map
clang++ -Wall -Werror -Wextra -std=c++98 -D FT=1 main.cpp -o main.ft.out
# compile main with std::map
clang++ -Wall -Werror -Wextra -std=c++98 -D FT=0 main.cpp -o main.std.out

# run main.ft.out and save output to main.ft.output
START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
./main.ft.out 123
END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
echo "elapsed time ft: $(($END_TIME - $START_TIME))"

# run main.std.out and save output to main.std.output
START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
./main.std.out 123
END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
echo "elapsed time std: $(($END_TIME - $START_TIME))"
