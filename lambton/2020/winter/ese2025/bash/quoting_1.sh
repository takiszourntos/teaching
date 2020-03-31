#!/bin/bash

clear # clear the screen

# Double quotes are sometimes known as partial quoting, because certain special characters
# retain their meaning within the quotes. This is true, for example, of $, which is used
# to express the string associated with a variable. Moreover, double quotes allow us to include
# whitespace (such as spaces or tabs) as part of a string

XNQ=this # without quotes, XNQ cannot contain whitespace
XWQ="can be so much more" # using quotes, XWQ can contain whitespace 

echo $XNQ
echo $XWQ


counter=0                    # Integer --- actually, the variables is BASH are untyped!
echo "---"
for x in $XWQ     # Splits the variable in parts at whitespace.
do
  echo "$x"
  let "counter += 1"     # count number of loop iterations
done
echo "The number of loop iterations was $counter"


counter=0                    # Integer, supposedly!
echo "---"
for x in "$XWQ"   # Preserves whitespace in a single variable.
do #     ^     ^
  echo "$x"
  let "counter += 1"     # count number of loop iterations
done
echo "The number of loop iterations was $counter"


# Single quotes (' ') operate similarly to double quotes, but do not permit referencing variables, 
# since the special meaning of $ is turned off. Within single quotes, every special character 
# except ' gets interpreted literally. Consider single quotes ("full quoting") to be a stricter 
# method of quoting than double quotes ("partial quoting").
 
exit 0
