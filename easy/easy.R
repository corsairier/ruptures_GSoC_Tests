library(Rcpp)
library(RcppArmadillo)


Rcpp::sourceCpp("easy/easy.cpp")


X <- matrix(1:12, nrow = 4, ncol = 3)

Y <- getCumsum(X)
print(Y)
