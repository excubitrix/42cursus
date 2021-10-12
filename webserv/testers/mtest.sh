#! /bin/bash

# INSTRUCTIONS --------------
# 1. cwd = testers
# 2. ./mtest.sh
# (the tests use the testing/ directory in www/)
# ---------------------------

# used curl flags:
#   -X <METHOD> : specifiy HTTP method
#   -I : only get header
#   -s : don't print stats in terminal

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BOLD="\033[1m"
RESET="\033[0m"

# --- START UP SERVER ---

# stop server if it's already running, as we need to make sure it's using mtest.conf
kill $(pgrep server) > /dev/null 2>&1
# move to parent dir, as binary needs to be executed from there
cd ..
# run make; if error: exit
make
if [[ $? != 0 ]]; then
    exit 1; fi
# run server in background
    # ./server mtest.conf & # server output -> screen
    ./server mtest.conf > testers/server_output.out 2>&1 & # server output -> file
    # ./server mtest.conf > /dev/null 2>&1 & # server output -> void
# store process PID of server to kill it later
SERVER_PID=$!
# move back to testers directory
cd testers

# truncate output file to 0
: > output_actual.out

# remove test-generated files and directories
# rm -rf ../www/testing/tmp
# rm -rf ../www/testing/subdir_PUT/some
# rm -rf ../www/testing/subdir_upload/upload*
# rm -rf ../www/testing/subdir_upload/newfile
# rm -rf ../www/testing/subdir_upload/some

# --- TESTING FUNCTION ---

f_tester()
{
    echo "curl $1" >> output_actual.out
    curl $1 >> output_actual.out
}

# --- TESTING INPUT ---

# allowed/implemented methods tests

f_tester "-s -X GET -I localhost:8080"
f_tester "-s -X POST -I localhost:8080"
f_tester "-s -X DELETE -I localhost:8080"
f_tester "-s -X HEAD -I localhost:8080"
f_tester "-s -X PUT -I localhost:8080"
f_tester "-s -X CONNECT -I localhost:8080"

f_tester "-s -X GET -I localhost:8080/subdir_NONE/"
f_tester "-s -X POST -I localhost:8080/subdir_NONE/"
f_tester "-s -X DELETE -I localhost:8080/subdir_NONE/"
f_tester "-s -X HEAD -I localhost:8080/subdir_NONE/"
f_tester "-s -X PUT -I localhost:8080/subdir_NONE/"
f_tester "-s -X CONNECT -I localhost:8080/subdir_NONE/"

f_tester "-s -X GET -I localhost:8080/subdir_GET/testfile"
f_tester "-s -X POST -I localhost:8080/subdir_POST/testfile"
f_tester "-s -X HEAD -I localhost:8080/subdir_HEAD/testfile"
# check server output to see if only head was sent

f_tester "-s -X GET localhost:8080/subdir_GET/testfile"
echo >> output_actual.out
# "-X HEAD" (without "-s") gives "Warning: Setting custom HTTP method to HEAD
# with -X/--request may not work the way you want. Consider using -I/--head
# instead." and then hangs
# -X HEAD without -I should return nothing
f_tester "-s -I localhost:8080/subdir_HEAD/testfile"
echo >> output_actual.out

# deletion tests

FILE="../www/testing/subdir_DELETE/file_to_delete.out"

touch $FILE
ls $FILE >> output_actual.out
f_tester "-s -X DELETE -I localhost:8080/subdir_DELETE/file_to_delete.out"
ls $FILE >> output_actual.out

touch $FILE
ls $FILE >> output_actual.out
f_tester "-s -X DELETE -I localhost:8080/subdir_DELETE/NOT_file_to_delete.out"
ls $FILE >> output_actual.out
rm $FILE

DIR="../www/testing/subdir_DELETE/dir_to_delete"
ls $DIR >> output_actual.out
f_tester "-s -X DELETE -I localhost:8080/subdir_DELETE/dir_to_delete"
ls $DIR >> output_actual.out

# URI_MAX_LENGTH tests
f_tester "-s -X GET -I localhost:8080/..............................................................................................100|................................................................................................200|.................................................................................................299|"
f_tester "-s -X GET -I localhost:8080/................................................................................................100|................................................................................................200|................................................................................................300|"

# upload tests

f_tester_upload()
{
    echo >> output_actual.out
    echo "curl $1 -d \"$2\"" >> output_actual.out
    curl $1 -d "$2" | grep "<title>" >> output_actual.out
}

# f_tester_upload2()
# {
#     echo >> output_actual.out
#     echo "curl $1" >> output_actual.out
# }

# POST - subdir_POST
f_tester_upload "-s -X POST localhost:8080/subdir_POST" "Hello There" # creates a file in tmp/uploads/
ls ../www/testing/tmp/uploads >> output_actual.out

f_tester_upload "-s -X POST localhost:8080/subdir_POST/" "Hello There" # creates a file in tmp/uploads/
ls ../www/testing/tmp/uploads >> output_actual.out

f_tester_upload "-s -X POST localhost:8080/subdir_POST/random/path" "Hello There" # creates a file in tmp/uploads/
ls ../www/testing/tmp/uploads >> output_actual.out

f_tester_upload "-s -X POST localhost:8080/subdir_POST/random/path/" "Hello There" # creates a file in tmp/uploads/
ls ../www/testing/tmp/uploads >> output_actual.out

# POST - subdir_upload
f_tester_upload "-s -X POST localhost:8080/subdir_upload" "Hello There" # creates a file in subdir_uploads/
ls ../www/testing/subdir_upload >> output_actual.out

f_tester_upload "-s -X POST localhost:8080/subdir_upload/" "Hello There" # creates a file in subdir_uploads/
ls ../www/testing/subdir_upload >> output_actual.out

# PUT - subdir_PUT
f_tester_upload "-s -X PUT localhost:8080/subdir_PUT" "Hello There" # 500
ls ../www/testing/subdir_PUT >> output_actual.out

f_tester_upload "-s -X PUT localhost:8080/subdir_PUT/" "Hello There" # 500
ls ../www/testing/subdir_PUT >> output_actual.out

# ls -R : list subdirectories recursively
f_tester_upload "-s -X PUT localhost:8080/subdir_PUT/some/path/" "Hello There"
ls -R ../www/testing/subdir_PUT >> output_actual.out

f_tester_upload "-s -X PUT localhost:8080/subdir_PUT/some/path" "Hello There"
ls -R ../www/testing/subdir_PUT >> output_actual.out

f_tester_upload "-s -X PUT localhost:8080/subdir_PUT/some/path/newfile" "Hello There"
ls -R ../www/testing/subdir_PUT >> output_actual.out

# PUT - subdir_upload
f_tester_upload "-s -X PUT localhost:8080/subdir_upload" "Hello There" # 500
ls ../www/testing/subdir_upload >> output_actual.out

f_tester_upload "-s -X PUT localhost:8080/subdir_upload/" "Hello There" # 500
ls ../www/testing/subdir_upload >> output_actual.out

f_tester_upload "-s -X PUT localhost:8080/subdir_upload/newfile" "Hello There" # creates a file "newfile" in subdir_uploads/
ls ../www/testing/subdir_upload >> output_actual.out

f_tester_upload "-s -X PUT localhost:8080/subdir_upload/some/path/newfile" "Hello There" # creates a file "newfile" in subdir_uploads/some/path/
ls -R ../www/testing/subdir_upload >> output_actual.out

# limit the client body (use curl -X POST -H "Content-Type: plain/text" --data "BODY IS HERE write something shorter or longer than body limit")
echo >> output_actual.out
echo 'curl -s -X POST localhost:8080/subdir_POST -H "Content-Type: plain/text" --data "................................................................................................100|"' >> output_actual.out
curl -s -X POST localhost:8080/subdir_POST -H "Content-Type: plain/text" --data "................................................................................................100|" | grep "<title>" >> output_actual.out
ls ../www/testing/tmp/uploads >> output_actual.out

echo >> output_actual.out
echo 'curl -s -X POST localhost:8080/subdir_POST -H "Content-Type: plain/text" --data ".................................................................................................101|"' >> output_actual.out
curl -s -X POST localhost:8080/subdir_POST -H "Content-Type: plain/text" --data ".................................................................................................101|" | grep "<title>" >> output_actual.out
ls ../www/testing/tmp/uploads >> output_actual.out

# # remove test-generated files and directories
rm -rf ../www/testing/tmp
rm -rf ../www/testing/subdir_PUT/some
rm -rf ../www/testing/subdir_upload/upload*
rm -rf ../www/testing/subdir_upload/newfile
rm -rf ../www/testing/subdir_upload/some

# 403
FILE="../www/testing/subdir_GET/forbidden.out"
touch $FILE
chmod 0 $FILE
f_tester "-s -X GET -I localhost:8080/subdir_GET/forbidden.out"

# setup multiple servers with different host name (use something like: curl --resolve example.com:80:127.0.0.1 http://example.com/)
# f_tester_upload '-s -X POST localhost:8080/subdir_POST -d "..............................................................................................100|"'
# f_tester_upload '-s -X POST localhost:8080/subdir_POST -d "...............................................................................................101|"'

# f_tester '-X POST -H "Content-Type: plain/text" --data "..............................................................................................99|"'

# setup a list of method accepted for a certain route (ex: setup only HEAD on a route and use curl with and without option -X HEAD)

# stop server
kill $SERVER_PID

# --- REPORT DIFFERENCES ---

diff --text output_actual.out output_desired > diff.out
if [[ $? = 0 ]]
then
    printf $GREEN"no differences found\n"$RESET
else
    printf $YELLOW"differences found:\n"$RESET
    printf $YELLOW"------------------\n"$RESET
    cat diff.out
    printf $YELLOW"------------------\n"$RESET
fi

exit 0