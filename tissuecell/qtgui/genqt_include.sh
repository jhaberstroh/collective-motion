#!/bin/bash
shift 1
for FILE in $@
do
	echo $FILE
	FPATH=$(dirname $FILE)
	PRI_FILE=$(echo $FILE | sed "s/.mk/.pri/")
	echo "PWD = $(pwd)" > $PRI_FILE
	echo "" >> $PRI_FILE
	echo "INDLUDEPATH += \$\$PWD/$FPATH" >> $PRI_FILE
	cat $FILE | grep SRC | sed "s:SRC.*=[ \t]*:SOURCES \+= \$\$PWD/:" >> $PRI_FILE
	cat $FILE | grep HEADERS | sed "s:HEADERS.*=[ \t]*:HEADERS \+= \$\$PWD/:" >> $PRI_FILE
	#cat $FILE | sed "s:SRC[ \t]+\+=[ \t]+:SOURCES \+= \$\$PWD/:" >> $PRI_FILE
done


