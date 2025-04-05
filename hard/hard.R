library(Rcpp)
library(RcppArmadillo)


Rcpp::sourceCpp("hard/hard.cpp")

set.seed(123)

X = matrix(1:9, nrow = 3, ncol = 3)

Y <- matrix(rnorm(100 * 3), nrow=100, ncol=3)

cost_ptr <- create_cost(X)
cost_ptr2 <- create_cost(Y)

eval_cost(cost_ptr, 0, 3)
eval_cost(cost_ptr2, 0, 3)


