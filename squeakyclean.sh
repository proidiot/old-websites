#!/bin/sh
# In order to regenerate the necessary files that we delete in this script,
# you can run: autoreconf -i && ./configure

EXTRA_TOP_FILES="aclocal.m4 autom4te.cache autoscan.log config.guess config.h config.h.in config.log config.status config.sub configure configure.scan depcomp install-sh intl ltmain.sh missing stamp-h1"

EXTRA_RECURSIVE_FILES="*~ Makefile Makefile.in .deps"

M4_WHITELIST=""

PO_WHITELIST="*.po"


if [ -f Makefile ]
then
	make maintainer-clean
fi

for i in $EXTRA_TOP_FILES
do
	if [ -d $i ]
	then
		rm -r $i
	elif [ -f $i ]
	then
		rm $i
	fi
done

if [ -d m4 ]
then
	M4_LIST=`ls m4`
	M4_REMOVE=""
	for i in $M4_LIST
	do
		DROP=0
		for j in $M4_WHITELIST
		do
			if [ -z "`echo $i | egrep -v $j`" ]
			then
				DROP=1
			fi
		done
		if [ $DROP -ne 1 ]
		then
			M4_REMOVE="$M4_REMOVE $i"
		fi
	done
	
	for i in $M4_REMOVE
	do
		if [ -d m4/$i ]
		then
			rm -r m4/$i
		else
			rm m4/$i
		fi
	done
fi

if [ -d po ]
then
	PO_LIST=`ls po`
	PO_REMOVE=""
	for i in $PO_LIST
	do
		DROP=0
		for j in $PO_WHITELIST
		do
			if [ -z "`echo $i | egrep -v $j`" ]
			then
				DROP=1
			fi
		done
		if [ $DROP -ne 1 ]
		then
			PO_REMOVE="$PO_REMOVE $i"
		fi
	done
	
	for i in $PO_REMOVE
	do
		if [ -d po/$i ]
		then
			rm -r po/$i
		else
			rm po/$i
		fi
	done
fi

recursive_delete()
{
	for i in $EXTRA_RECURSIVE_FILES
	do
		if [ -d $1/$i ]
		then
			rm -r $1/$i
		elif [ -f $1/$i ]
		then
			rm $1/$i
		fi
	done

	for i in `ls $1`
	do
		if [ -d $1/$i ]
		then
			recursive_delete $1/$i
		fi
	done
}

recursive_delete .

