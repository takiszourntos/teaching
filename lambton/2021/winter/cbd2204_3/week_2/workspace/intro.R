# show the current working directory
getwd()

# change the following line for your setup
setwd("Identities/takiszourntos/teaching/lambton/2021/winter/cbd2204_3/week_2/workspace/")

# import a CSV file of the total annual sales for each customer
#sales <- read.csv("Identities/takiszourntos/teaching/lambton/2021/winter/cbd2204_3/week_2/workspace/yearly_sales.csv", sep="");
sales <- read.csv("yearly_sales.csv", sep="");


# examine the imported dataset
head(sales)
summary(sales)

# plot num_of_orders vs. sales
plot(sales$num_of_orders, sales$sales_total, main="Number of Orders vs. Sales")

# perform a statistical analysis (fit a linear regression model)
results <- lm(sales$sales_total ~ sales$num_of_orders)
summary(results)

# perform some diagnostics on the fitted model
# plot histogram of the residuals
hist(results$residuals, breaks = 800)
