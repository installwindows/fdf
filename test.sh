#!/bin/sh

FILES=./maps/*.fdf

for f in $FILES
do
	./fdf $f
done
