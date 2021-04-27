# produce "distributions" for various religious affiliations with the highest
# earners; the idea is to show the proportion within the group who possess
# higher incomes

# signature information
system("whoami")
Sys.time()

# load library to get relig_income and ggplot()
library(tidyverse)

#########################################
# Mainline Protestant religion
#########################################
relig_MainlineProt <- dplyr::filter(relig_income, religion == "Mainline Prot")
data_MainlineProt <- base::data.frame() # initialize a dataframe/tibble
  # create the new data frame, transposed
  data_MainlineProt [1, 1] = 1
  data_MainlineProt[1, 2] = relig_MainlineProt[1, 2]
  for (bracket in 3:10) {
    data_MainlineProt[bracket-1, 1] <- bracket - 1
    data_MainlineProt[bracket-1, 2] <- relig_MainlineProt[1,bracket]
  }
  colnames(data_MainlineProt) <- c("bracket", "count")
# generate plot
ggplot(data = data_MainlineProt) + geom_step(mapping = aes(x = bracket, y= count)) + ggtitle("Mainline Protestant Religion") +
    xlab("income bracket (< $10k to > $150k )") + ylab("number surveyed")

#########################################
# Orthodox religion
#########################################
relig_Orthodox <- dplyr::filter(relig_income, religion == "Orthodox")
data_Orthodox <- base::data.frame() # initialize a dataframe/tibble
  # create the new data frame, transposed
  data_Orthodox[1, 1] = 1
  data_Orthodox[1, 2] = relig_Orthodox[1, 2]
  for (bracket in 3:10) {
    data_Orthodox[bracket-1, 1] <- bracket - 1
    data_Orthodox[bracket-1, 2] <- relig_Orthodox[1,bracket]
  }
  colnames(data_Orthodox) <- c("bracket", "count")
# generate plot
ggplot(data = data_Orthodox) + geom_step(mapping = aes(x = bracket, y= count)) + ggtitle("Orthodox Religion") +
  xlab("income bracket (< $10k to > $150k )") + ylab("number surveyed")

#########################################
# Jewish religion
#########################################
relig_Jewish <- dplyr::filter(relig_income, religion == "Jewish")
data_Jewish <- base::data.frame() # initialize a dataframe/tibble
  # create the new data frame, transposed
  data_Jewish[1, 1] = 1
  data_Jewish[1, 2] = relig_Jewish[1, 2]
  for (bracket in 3:10) {
    data_Jewish[bracket-1, 1] <- bracket - 1
    data_Jewish[bracket-1, 2] <- relig_Jewish[1,bracket]
  }
  colnames(data_Jewish) <- c("bracket", "count")
# generate plot
ggplot(data = data_Jewish) + geom_step(mapping = aes(x = bracket, y= count)) + ggtitle("Jewish Religion") +
  xlab("income bracket (< $10k to > $150k )") + ylab("number surveyed")

#########################################
# Hindu religion
#########################################
relig_Hindu <- dplyr::filter(relig_income, religion == "Hindu")
data_Hindu <- base::data.frame() # initialize a dataframe/tibble
  # create the new data frame, transposed
  data_Hindu[1, 1] = 1
  data_Hindu[1, 2] = relig_Hindu[1, 2]
  for (bracket in 3:10) {
    data_Hindu[bracket-1, 1] <- bracket - 1
    data_Hindu[bracket-1, 2] <- relig_Hindu[1,bracket]
  }
  colnames(data_Hindu) <- c("bracket", "count")
# generate plot
ggplot(data = data_Hindu) + geom_step(mapping = aes(x = bracket, y= count)) + ggtitle("Hindu Religion") +
  xlab("income bracket (< $10k to > $150k )") + ylab("number surveyed")