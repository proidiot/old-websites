#!/bin/sh
# In order to regenerate the necessary files that we delete in this script,
# you can run: aclocal -i

EXTRA_FILES="aclocal.m4 autom4te.cache autoscan.log config.guess config.h.in config.h.in~ config.sub configure configure.scan depcomp install-sh intl ltmain.sh m4/* Makefile Makefile.in missing po/* *~ */Makefile */*~ */Makefile.in"

if [ -f Makefile ]
then
	make maintainer-clean
fi

for i in $EXTRA_FILES
do
	if [ -d $i ]
	then
		rm -r $i
	elif [ -f $i ]
	then
		rm $i
	fi
done

