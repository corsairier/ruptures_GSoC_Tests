#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
double eval(arma::mat& X, int start, int end){
    arma::mat segment = X.rows(start, end - 1);

    arma::rowvec mean = arma::mean(segment, 0); // mean along rows

    // centered data
    arma::mat centered = segment.each_row() - mean;

    // squared euclidean norm of each row
    arma::vec squared_norms = arma::sum(arma::square(centered), 1);

    // Total cost
    return arma::sum(squared_norms);
}

