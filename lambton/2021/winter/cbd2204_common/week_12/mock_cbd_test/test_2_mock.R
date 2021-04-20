# Name: Takis Zourntos
# Student ID: C01872364293108471829437
# preferred salad: arugula pear with walnuts
#
# signature
system("whoami")
Sys.time()

# load the mpg library and other useful functions
library(tidyverse)

# template: graph
# ggplot(data = mpg) + geom_point(mapping = aes(x = displ, y=cty, color=class))
# template: histogram
# ggplot(data = rich_1) + geom_histogram(mapping = aes(religion, fill=religion),  binwidth=1)
# template: filter
# mpg_sport <- dplyr::filter(mpg, class=="2seater" & ((hwy < 30) | (cty < 20)))

# filter out the data to form high income columns, normalized by total count
  rich_1 <- dplyr::select(relig_income, religion, '$75-100k', '$100-150k', '>150k')
  # total up each religion (create a vector)
  total_count <- rich_1$`$75-100k`+rich_1$`$100-150k`+rich_1$`>150k`
  # normalize rich_1, scale up to "percent" units for normalized counts
  for (relig in 1:18) { 
    rich_1[relig,2] <- round(100*rich_1[relig,2]/total_count[relig]) # $75-100k
    rich_1[relig,3] <- round(100*rich_1[relig,3]/total_count[relig]) # $100-150k
    rich_1[relig,4] <- round(100*rich_1[relig,4]/total_count[relig]) # > $150k
  }
  
# plot higher incomes 
  # in the bracket $75-100k
  ggplot(data = rich_1) + geom_point(mapping = aes(x = religion, y=`$75-100k`, color=religion)) + 
    geom_text(aes(x = religion, y = `$75-100k`, label=religion), hjust=0, vjust=+1)
  # in the bracket $100-150k
  ggplot(data = rich_1) + geom_point(mapping = aes(x = religion, y=`$100-150k`, color=religion)) + 
    geom_text(aes(x = religion, y = `$100-150k`, label=religion), hjust=0, vjust=+1)
  # in the bracket > $150k
  ggplot(data = rich_1) + geom_point(mapping = aes(x = religion, y=`>150k`, color=religion)) + 
    geom_text(aes(x = religion, y = `>150k`, label=religion), hjust=0, vjust=+1)
  
  
  
  
