#!/bin/bash  
DIR=$1  
if [ ! -d "$DIR" ]; then  
   echo "$DIR does not exist"  
      exit 0  
	  fi  
	  RESULT_FILE=./permis.sh  
	  echo "" > $RESULT_FILE  
	  tree -fiaR --noreport -o permis.log $DIR  
	  cat permis.log|cut -d" " -f1| while read line  
	  do  
	         echo chown `stat -c "%U:%G" $line` $line >> $RESULT_FILE  
			        echo chmod `stat -c "%a" $line` $line >> $RESULT_FILE  
					done  
