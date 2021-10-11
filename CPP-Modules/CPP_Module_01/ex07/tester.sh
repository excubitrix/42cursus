#!/bin/bash

PWD="$(pwd)"

mkdir -p $PWD/files

WORKDIR=$PWD/files

cat <<EOF > $WORKDIR/test1
Hello world!
Hello world!
Hello world!
How are you?
Hello world!
Hello world!
Hello world!
EOF

cat <<EOF > $WORKDIR/test1.expected
Hello there!
Hello there!
Hello there!
How are you?
Hello there!
Hello there!
Hello there!
EOF

cat $WORKDIR/test1.expected > $WORKDIR/test2

cat <<EOF > $WORKDIR/test2.expected
Hi!
Hi!
Hi!
How are you?
Hi!
Hi!
Hi!
EOF

cat $WORKDIR/test2.expected > $WORKDIR/test3

cat $WORKDIR/test1 > $WORKDIR/test3.expected

make

echo './replace test1 world there'
./replace $WORKDIR/test1 world there
diff $WORKDIR/test1.replace $WORKDIR/test1.expected > $WORKDIR/test1.diff
ret=$?
if [ $ret -eq 0 ]; then
	echo "OK!"
elif [ $ret -eq 1 ]; then
	cat -e $WORKDIR/test1.diff
	echo "KO!"
else
	echo "The diff command failed."
fi

echo './replace test2 "Hello there" Hi'
./replace $WORKDIR/test2 "Hello there" Hi
diff $WORKDIR/test2.replace $WORKDIR/test2.expected > $WORKDIR/test2.diff
ret=$?
if [ $ret -eq 0 ]; then
	echo "OK!"
elif [ $ret -eq 1 ]; then
	cat -e $WORKDIR/test2.diff
	echo "KO!"
else
	echo "The diff command failed."
fi

echo './replace test3 Hi "Hello world"'
./replace $WORKDIR/test3 Hi "Hello world"
diff $WORKDIR/test3.replace $WORKDIR/test3.expected > $WORKDIR/test3.diff
ret=$?
if [ $ret -eq 0 ]; then
	echo "OK!"
elif [ $ret -eq 1 ]; then
	cat -e $WORKDIR/test3.diff
	echo "KO!"
else
	echo "The diff command failed."
fi
