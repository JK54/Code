#!/bin/bash

find . -name "*.exe"
find . -name "a.out"
find . -name "*.o"

read -p "input y to delete: " op

if [ $op = 'y' ] || [ $op = 'Y' ]
then
	echo "deleting exe.."
	find . -name "*.exe"|xargs -I {} rm {}
	echo "deleting a.out.."
	find . -name "a.out"|xargs -I {} rm {}
	echo "deleting o.."
	find . -name "*.o"|xargs -I {} rm {}
else
	echo "Sorry, you did not identify yourself."
fi
