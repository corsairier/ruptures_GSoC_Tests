#include "include/cumsum.h"
// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat getCumsum(const arma::mat& X) {
    int T = X.n_rows;
    int D = X.n_cols;
    
    // Create output matrix of size T x D+1
    arma::mat Y(T+1, D, arma::fill::zeros);
    
    for (int j = 1; j <= T; j++) {
        Y.row(j) = arma::cumsum(X.row(j-1));
    }
    
    return Y;
}
