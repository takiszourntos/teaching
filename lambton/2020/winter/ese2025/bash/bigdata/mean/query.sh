#
# BASH Script extracts real climate data from government website
# 
#	usage: ./query.sh 1985 16
#
#	first argument (access in BASH as $1) is the year of the measurements
#  	second argument (access in BASH as $2) is the location (1 to 338)
#
# author: Takis Zourntos
#

#!/bin/bash
NUMCONTEXTLINES=1 # works up to 17
let NCLPLUSONE=NUMCONTEXTLINES+1

# temporary file definitions
alldatafile="BIGDATA8zx2756.txt"
smalldatafile="distilled_datazx47432_$1.dat"
locationsfile="locationszx646332.txt"

# scan all data files
for x in mm*.txt # $x is a data file name, corresponding to a geographical location
do
	echo "$x" >> $locationsfile	# write the data file name first
	y=$(cat $x | tr "," "\n")	# remove commas, replace with newlines
	for z in $y			# go through each token in the file $x
	do
		echo $z >> $alldatafile 
	done 
done

# scan for a particular year; there should be as many of a given year
# as there are geographical locations
yearsearch=$1 # year provided as argument
cat  $alldatafile | grep -A 17 $yearsearch >> $smalldatafile

# extract year's info for location specified in $2
head -n $2 $locationsfile | tail -n 1 # send the location identifier string to STDOUT
cat $smalldatafile | grep -A $NUMCONTEXTLINES -m $2 $yearsearch | tail -n $NCLPLUSONE	# send the target year's temp data to STDOUT 

# wrap up, delete all temporary files
rm $alldatafile; rm $smalldatafile; rm $locationsfile

exit 0
