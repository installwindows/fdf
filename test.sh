#!/bin/sh

FILES=./maps/*.fdf

for f in $FILES
do
	echo $f
	./a $f
	./fdf $f
done
