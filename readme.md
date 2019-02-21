Trial.Online
============

Trial.Online is a header-only C++11 library that contains online algorithms for statistical analysis.

The online algorithms process data piecemeal and work in constant space and constant time (per data point), making them suitable for edge analysis on embedded devices.

The supported algorithms are:

* Moments: Mean, variance, skewness, kurtosis.
* Correlation: Covariance, Pearson's correlation coefficient.
* Linear regression.
* Quantiles: Estimator of median and other quantiles.
* Sampling: Reservoir data sampling.

Many of the algorithms (e.g. moments, covariance, and linear regression) exists in several variants:
* Cumulative: Accumulated moments.
* Decay: Exponentially smoothing moments.
* Window: Moments within a sliding-window.
* Interim: Approximate moments within sliding-window. Memory consumption independent on window size.
