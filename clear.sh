#!/bin/bash

find ~/Code_cpp -name "*.exe"
find ~/Code_cpp -name "a.out"
find ~/Code_cpp -name "*.o"

read -p "input y to delete: " op

if [ $op = 'y' ] || [ $op = 'Y' ]
then
	echo "deleting exe.."
	find ~/Code_cpp  -name "*.exe"|xargs -I {} rm {}
	echo "deleting a.out.."
	find ~/Code_cpp -name "a.out"|xargs -I {} rm {}
	echo "deleting o.."
	find ~/Code_cpp  -name "*.o"|xargs -I {} rm {}
else
	echo "Sorry, you did not identify yourself."
fi
