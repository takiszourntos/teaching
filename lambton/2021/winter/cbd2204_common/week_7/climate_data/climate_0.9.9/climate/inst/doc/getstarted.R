## ----setup, include = FALSE---------------------------------------------------
knitr::opts_chunk$set(
  collapse = TRUE,
  comment = "#>"
)
options(scipen=999)

## ----stations , eval=T, fig.width=7,fig.height=7, fig.fullwidth=TRUE----------
library(climate)
ns = nearest_stations_ogimet(country ="United+Kingdom",
                             point = c(-4, 56),
                             no_of_stations = 50, 
                             add_map = TRUE)
head(ns)
#>    wmo_id       station_names       lon       lat alt  distance [km]
#> 29  03144         Strathallan  -3.733348 56.31667  35      46.44794
#> 32  03155           Drumalbin  -3.733348 55.61668 245      52.38975
#> 30  03148           Glen Ogle  -4.316673 56.41667 564      58.71862
#> 27  03134   Glasgow Bishopton  -4.533344 55.90002  59      60.88179
#> 35  03166 Edinburgh Gogarbank  -3.350007 55.93335  57      73.30942
#> 28  03136      Prestwick RNAS  -4.583345 55.51668  26      84.99537

## ----stations, eval=T, fig.width=7, fig.height=7, fig.fullwidth=T-------------
library(climate)
PL = stations_ogimet(country ="Poland", add_map = TRUE)
head(PL)

## ----windrose,eval=T----------------------------------------------------------
# downloading data with NOAA service:
df = meteo_noaa_hourly(station = "010080-99999", 
                       year = sample(2000:2020, 1))

# downloading the same data with Ogimet.com (example for 2019):
# df <- meteo_ogimet(interval = "hourly", date = c("2019-01-01", "2019-12-31"),
#                   station = c("01008"))

## ----windrose2, echo=FALSE----------------------------------------------------
library(knitr)
kable(head(df[,c(-2:-5)],10), caption = "Examplary data frame of meteorological data.")

## ----sonda,eval=T, fig.width=7, fig.height=7, fig.fullwidth=TRUE--------------
library(climate)
data("profile_demo")
# same as:
# profile_demo <- sounding_wyoming(wmo_id = 12120,
#                                  yy = 2000,
#                                  mm = 3,
#                                  dd = 23,
#                                  hh = 0)
df2 <- profile_demo[[1]] 
colnames(df2)[c(1, 3:4)] = c("PRESS", "TEMP", "DEWPT") # changing column names

## ----sonda2, echo=FALSE-------------------------------------------------------
library(knitr)
kable(head(df2,10), caption = "Examplary data frame of sounding preprocessing")

## ----imgw_meteo, fig.width=7, fig.height=7, fig.fullwidth=TRUE----------------
library(climate)
library(dplyr)

df = meteo_imgw(interval = 'monthly', rank='synop', year = 1991:2019, station = "ŁEBA") 
# please note that sometimes 2 names are used for the same station in different years

df2 = select(df, station:t2m_mean_mon, rr_monthly)

monthly_summary = df2 %>% 
  group_by(mm) %>% 
  summarise(tmax = mean(tmax_abs, na.rm = TRUE), 
            tmin = mean(tmin_abs, na.rm = TRUE),
            tavg = mean(t2m_mean_mon, na.rm = TRUE), 
            precip = sum(rr_monthly) / n_distinct(yy))            

monthly_summary = as.data.frame(t(monthly_summary[, c(5,2,3,4)])) 
monthly_summary = round(monthly_summary, 1)
colnames(monthly_summary) = month.abb


## ----imgw_meto2, echo=FALSE---------------------------------------------------
library(knitr)
kable(head(monthly_summary), caption = "Examplary data frame of meteorological preprocessing.")

## ----data---------------------------------------------------------------------
library(climate)
library(dplyr)
library(tidyr)
h = hydro_imgw(interval = "monthly", year = 2001:2005, coords = TRUE)
head(h)

## ----filtering, eval=TRUE, include=TRUE---------------------------------------
h2 = h %>%
  filter(idex == 3) %>%
  select(id, station, X, Y, hyy, Q) %>%
  group_by(hyy, id, station, X, Y) %>%
  summarise(annual_mean_Q = round(mean(Q, na.rm = TRUE), 1)) %>% 
  pivot_wider(names_from = hyy, values_from = annual_mean_Q)

## ----filtering2, echo=FALSE---------------------------------------------------
library(knitr)
kable(head(h2), caption = "Examplary data frame of hydrological preprocesssing.")

