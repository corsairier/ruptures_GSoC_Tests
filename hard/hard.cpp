#include "../include/cumsum.h"
#include <iostream>
using namespace std;

// [[Rcpp::depends(RcppArmadillo)]]

class Cost {
private:
    arma::mat X;
    arma::mat cumsum_X;
    arma::vec cumsum_sq_norms;
    
public:
    // Constructor
    Cost(const arma::mat& input_X) {
        X = input_X;
        int T = X.n_rows;
        
        // Compute cumulative sum of X
        cumsum_X = arma::join_cols(arma::zeros<arma::rowvec>(X.n_cols), arma::cumsum(X, 0));
        cout << cumsum_X << endl;

        arma::mat cum2 = getCumsum(X);
        cout << cum2 << endl;

        // Compute cumulative sum of squared norms
        cumsum_sq_norms = arma::join_cols(arma::zeros<arma::vec>(1), arma::cumsum(arma::sum(arma::square(X), 1)));
    }

    // function to evaluate cost
    double efficient_eval(int start, int end) {
        if (start >= end) return 0.0;
        
        // compute cumsums for the given segment
        arma::rowvec sum_X = cumsum_X.row(end) - cumsum_X.row(start);
        double sum_sq_norms = cumsum_sq_norms[end] - cumsum_sq_norms[start];

        // Compute mean over the segment
        int segment_length = end - start;
        double cost = sum_sq_norms - arma::dot(sum_X, sum_X) / segment_length;

        return cost;
    }
};

// [[Rcpp::export]]
Rcpp::XPtr<Cost> create_cost(arma::mat X) {
    return Rcpp::XPtr<Cost>(new Cost(X));
}

// [[Rcpp::export]]
double eval_cost(Rcpp::XPtr<Cost> cost_ptr, int start, int end) {
    return cost_ptr->efficient_eval(start, end);
}
