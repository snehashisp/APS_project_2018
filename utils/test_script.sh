#!/bin/bash

if [ -f ./$3/$4 ]
then 
	rm ./$3/$4
fi

filelist=($(ls $3))


for file in ${filelist[@]}
do
	$1 $2 $5 < ./$3/$file >> ./$3/$4
done


