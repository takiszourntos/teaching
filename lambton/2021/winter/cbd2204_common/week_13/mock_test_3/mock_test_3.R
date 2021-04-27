# investigation of trends in the esoph dataset
# to study risk associated with higher consumption
# of alcohol and tobacco products
#
# student: Takis Zourntos
# student ID: C012390481902348

# signature information
system("whoami")
Sys.time()

# working with esoph
library(datasets)
library(tidyverse)

# there are six age groups, from 25-75+ years
# let's only consider data where there are more than zero cases
#esoph_cases <- dplyr::filter(esoph, ncases > 0)
esoph_cases <- esoph

# add a probabilities column
esoph_cases$prob <- 100*esoph_cases$ncases/esoph_cases$ncontrols

### high versus low consumption, across all age groups
  # across all age groups, extract data for higher alcohol and tobacco consumption
  esoph_high <- dplyr::filter(esoph_cases, (alcgp=="120+" | alcgp=="80-119") & (tobgp=="30+" | tobgp=="20-29"))
  # extract data for low consumption
  esoph_low  <- dplyr::filter(esoph_cases, (alcgp=="0-39g/day" | alcgp=="40-79") & (tobgp=="0-9g/day" | tobgp=="10-19"))
  # generate a plot across lifespan of consumption versus probability
  Ylowlow <- dplyr::filter(esoph_low, alcgp=="0-39g/day" & tobgp=="0-9g/day")
  Ymodmod <- dplyr::filter(esoph_low, alcgp=="40-79" & tobgp=="10-19")
  Ymoremore <- dplyr::filter(esoph_high, alcgp=="80-119" & tobgp=="20-29")
  Ymaxmax <- dplyr::filter(esoph_high, alcgp=="120+" & tobgp=="30+")
  
  # plots
  ggplot(data = Ylowlow) + geom_point(mapping = aes(x = agegp, y= prob)) + ggtitle("Risk of Low Consumption") +
    xlab("age group") + ylab("probability")
  
  ggplot(data = Ymodmod) + geom_point(mapping = aes(x = agegp, y= prob)) + ggtitle("Risk of Moderate Consumption") +
    xlab("age group") + ylab("probability")
  
  ggplot(data = Ymoremore) + geom_point(mapping = aes(x = agegp, y= prob)) + ggtitle("Risk of Greater Consumption") +
    xlab("age group") + ylab("probability")
  
  ggplot(data = Ymaxmax) + geom_point(mapping = aes(x = agegp, y= prob)) + ggtitle("Risk of High Consumption") +
    xlab("age group") + ylab("probability")
  