#!/bin/bash

find ~/Code -name "*.exe"
find ~/Code -name "a.out"
find ~/Code -name "*.o"

read -p "input y to delete: " op

if [ $op = 'y' ] || [ $op = 'Y' ]
then
	echo "deleting exe.."
	find ~/Code  -name "*.exe"|xargs -I {} rm {}
	echo "deleting a.out.."
	find ~/Code -name "a.out"|xargs -I {} rm {}
	echo "deleting o.."
	find ~/Code  -name "*.o"|xargs -I {} rm {}
else
	echo "Sorry, you did not identify yourself."
fi
