#!/bin/bash
for x in cxxtest/*.t
do
	echo "RUNNING TEST $x"
	$x
done
