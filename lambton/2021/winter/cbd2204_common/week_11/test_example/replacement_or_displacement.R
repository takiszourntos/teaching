# Name: Takis Zourntos
# Student ID: C01872364293108471829437
# preferred salad: arugula pear with walnuts
#
# signature
system("whoami")
Sys.time()

# load the mpg library and other useful functions
library(tidyverse)

# definitions
  # efficiency: cty or hwy
  # sports cars: 2 seaters with rwd

# visualizations
  # show cty versus displacement by class
  ggplot(data = mpg) + geom_point(mapping = aes(x = displ, y=cty, color=class))
  
  # show hwy versus displacement by class
  ggplot(data = mpg) + geom_point(mapping = aes(x = displ, y=hwy, color=class))
  
  # extraction : from visualizations, we can look at
    # vehicles with less than 30 mpg (hwy) OR less than 20 mpg (cty)

    # get just the sports cars from mpg
    mpg_sport <- dplyr::filter(mpg, class=="2seater" & ((hwy < 30) | (cty < 20)))
    ggplot(data = mpg_sport) + geom_histogram(mapping = aes(hwy))
    summary(mpg_sport$cty)
    summary(mpg_sport$hwy)
  
    # get just the suvs from from mpg
    mpg_suv <- dplyr::filter(mpg, class=="suv" & ((hwy < 30) | (cty < 20)))
    ggplot(data = mpg_suv) + geom_histogram(mapping = aes(hwy))
    
    # get just the minivans from mpg
    mpg_minivan <- dplyr::filter(mpg, class=="minivan" & ((hwy < 30) | (cty < 20)))
    ggplot(data = mpg_minivan) + geom_histogram(mapping = aes(hwy))
    
    # get just the pickups from mpg
    mpg_pickup <- dplyr::filter(mpg, class=="pickup" & ((hwy < 30) | (cty < 20)))
    ggplot(data = mpg_pickup) + geom_histogram(mapping = aes(hwy))
    summary(mpg_pickup$cty)
    summary(mpg_pickup$hwy)
    
    # as a comparison, midsize 
    mpg_midsize <- dplyr::filter(mpg, class=="midsize" & ((hwy < 30) | (cty < 20)))
    ggplot(data = mpg_midsize) + geom_histogram(mapping = aes(hwy))
    
  