# Working with Big (and Real) Data

This directory contains data obtained from a government web site, known as Homogenized Temperatures for Canada.

Please see the included ATemperature_Documentation.doc file for more information. Essentially, each file (of the form mm*.txt) in this directory
represents one of 338 locations across Canada where climate temperatures were made. Within each file, temperature data (in Celsius) is recorded several times over a period often spanning more than 100 years!

I have written a script, query.sh, which you can study. It incorporates a couple of new BASH features such as command-line arguments and makes substantial use of pipes and variables.

For example, you can use query.sh as follows at the Linux prompt, which returns the first temperature reading recorded in 1948 for site 318 (of 338 possible sites)

$ ./query.sh 1948 318

mm8300447.txt

1948

-9.5

The first string returned is the name of the file corresponding to site 318. The second quantity (which can be stored as an integer in C) is the year in which the measurement was taken. The final quantity (which could be stored using a float in C) is a measured mean temperature.

There is a lot of data to sift through, so the script can take some time to execute!

## Exercise
Compose a BASH script to correlate the location number to the actual location name. If you look at the file BTemperature_Stations.txt, each station, numbered 1 to 338, has a proper name. For example, station number 28 is KELOWNA, and station 241 is TORONTO. If you consider the line of the file corresponding to TORONTO, it looks like:

241 6158355 TORONTO           ON  1840  3  2012 12      43.67    -79.40     113       Y

where the location/station number is first (241), followed by the station ID code (6158355), followed by the station name (TORONTO), followed by province (ON), year the measurements begin (1840), month in 1840 (3 - March), final year of measurements in the dataset (2012), final year month (12 - December), and additional information, including the latitude and longitude of the site location.

Your BASH script, findtemp.sh, should filter the output of query.sh to produce an output with the proper name of the site, rather than a file name. Your script should be used as follows:

$ ./findtemp.sh 1948 318

MONTICELLO

1948

-9.5

## Exercise
Now, compose a BASH script to create a file, testdata.dat, which contains climate data for a specific site over a number of years. Your script, called testgen.sh, should be used as follows:

$ ./testgen.sh 218 1948 1997 

where 218 represents the site location, 1948 the start year, and 1997 the final year. The generated file, testdata.dat, should look something like:

$ cat testdata.dat

KAPUSKASING

1948

-3.6


KAPUSKASING

1949

-5.2


.
.
.


KAPUSKASING

1997

2.6


-9999

-9999

-9999


where the three rows of -9999 are included to indicate the end of the valid data. These will be useful for our C-code.







