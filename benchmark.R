library(bench)
library(Rcpp)
library(RcppArmadillo)
library(ggplot2)

Rcpp::sourceCpp("medium/medium.cpp")
Rcpp::sourceCpp("hard/hard.cpp")

set.seed(123)

X <- matrix(rnorm(1000 * 3), nrow=1000, ncol=3)
cost_ptr = create_cost(X)

Y <- matrix(rnorm(10000 * 3), nrow=10000, ncol=3)
cost_ptr2 = create_cost(Y)

Z <- matrix(rnorm(100000 * 3), nrow=100000, ncol=3)
cost_ptr3 = create_cost(Z)

bnch1 <- bench::mark(
    naive = eval(X, 0, 1000),
    precomputed = eval_cost(cost_ptr, 0, 1000),
    iterations = 1000
)

bnch2 <- bench::mark(
    naive = eval(Y, 0, 10000),
    precomputed = eval_cost(cost_ptr2, 0, 10000),
    iterations = 1000
)

bnch3 <- bench::mark(
    naive = eval(Z, 0, 100000),
    precomputed = eval_cost(cost_ptr3, 0, 100000),
    iterations = 1000
)

summary(bnch1)
summary(bnch2)
summary(bnch3)
