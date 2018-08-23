#!/bin/bash

function disp()
{
	find ~/Code -name "*.exe"
	find ~/Code -name "a.out"
	find ~/Code -name "*.o"
}

function xclear()
{
	echo "deleting exe.."
	find ~/Code  -name "*.exe"|xargs -I {} rm {}
	echo "deleting a.out.."
	find ~/Code -name "a.out"|xargs -I {} rm {}
	echo "deleting o.."
	find ~/Code  -name "*.o"|xargs -I {} rm {}
	echo "deleting tmp.."
	find ~/Code/Data_Struct/Test/Tmp/ "*.*"|xargs rm 
}

disp
if [ $# = 1 ] && [ $1 = "-y" ]
then
	xclear
else
	read -p "input y to delete: " op
	if [ $op = 'y' ] || [ $op = 'Y' ]
	then
		xclear
	else
		echo "dididi"
	fi
fi
