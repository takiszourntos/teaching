#!/bin/bash
for x in S*.png
do
    y=$(echo $x | tr " " "_")
    mv "$x" "$y" # rename file
done

exit 0
