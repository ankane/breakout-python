/*
  Penalizes based on percent change in the statistic value.
  Linear penalty means that each new breakout must result in an at least X% increase
  Quadratic penalty means that each new breakout must result in at least an (X*k)% increase for k breakouts
*/

#include <algorithm>
#include <cmath>
#include <functional>
#include <set>
#include <vector>
#include "helper.h"

std::vector<int> EDM_percent(const std::vector<double>& Z, int min_size = 24, double percent = 0, int degree = 0) {
  // Z: time series
  // min_size: minimum segment size
  // beta: penalization term for the addition of a change point

  // identify which type of penalization to use
  double (*G)(double);
  switch (degree) {
  case 1:
    G = Linear;
    break;
  case 2:
    G = Quadratic;
    break;
  default:
    G = Const;
    break;
  }

  int n = Z.size();

  std::vector<int> prev(n + 1, 0);   // store optimal location of previous change point
  std::vector<int> number(n + 1, 0); // store the number of change points in optimal segmentation
  std::vector<double> F(n + 1, 0);   // store optimal statistic value
  // F[s] is calculated using observations { Z[0], Z[1], ..., Z[s-1] }

  // trees used to store the "upper half" of the considered observations
  std::multiset<double> right_min, left_min;
  // trees used to store the "lower half" of the considered observations
  std::multiset<double, std::greater<double>> right_max, left_max;

  // Iterate over possible locations for the last change
  for (int s = 2 * min_size; s < n + 1; ++s) {
    right_max.clear();
    right_min.clear(); // clear right trees
    left_max.clear();
    left_min.clear(); // clear left trees

    // initialize left and right trees to account for minimum segment size
    for (int i = prev[min_size - 1]; i < min_size - 1; ++i)
      insert_element(left_min, left_max, Z[i]);
    for (int i = min_size - 1; i < s; ++i)
      insert_element(right_min, right_max, Z[i]);

    // Iterate over possible locations for the penultimate change
    for (int t = min_size; t < s - min_size + 1; ++t) { // modify limits to deal with min_size
      insert_element(left_min, left_max, Z[t - 1]);     // insert element into left tree
      remove_element(right_min, right_max, Z[t - 1]);   // remove element from right tree
      // left tree now has { Z[prev[t-1]], ..., Z[t-1] }
      // right tree now has { Z[t], ..., Z[s-1] }

      // check to see if optimal position of previous change point has changed
      // if so update the left tree
      if (prev[t] > prev[t - 1]) {
        for (int i = prev[t - 1]; i < prev[t]; ++i)
          remove_element(left_min, left_max, Z[i]);
      } else if (prev[t] < prev[t - 1]) {
        for (int i = prev[t]; i < prev[t - 1]; ++i)
          insert_element(left_min, left_max, Z[i]);
      }

      // calculate statistic value
      double left_median = get_median(left_min, left_max), right_median = get_median(right_min, right_max);
      double normalize = ((t - prev[t]) * (s - t)) / (std::pow(static_cast<double>(s - prev[t]), 2));
      double tmp = F[t] + normalize * std::pow(static_cast<double>(left_median - right_median), 2);
      // Find best location for change point. check % condition later
      if (tmp > F[s]) {
        number[s] = number[t] + 1;
        F[s] = tmp;
        prev[s] = t;
      }
    }
    // check to make sure we meet the percent change requirement
    if (prev[s]) {
      if (F[s] - F[prev[s]] < percent * G(number[prev[s]]) * F[prev[s]]) {
        number[s] = number[prev[s]];
        F[s] = F[prev[s]];
        prev[s] = prev[prev[s]];
      }
    }
  }

  // obtain list of optimal change point estimates
  std::vector<int> ret;
  int at = n;
  while (at) {
    if (prev[at]) // don't insert 0 as a change point estimate
      ret.push_back(prev[at]);
    at = prev[at];
  }
  sort(ret.begin(), ret.end());
  return ret;
}
