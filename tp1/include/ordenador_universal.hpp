// include/ordenador_universal.hpp
#ifndef ORDENADOR_UNIVERSAL_HPP
#define ORDENADOR_UNIVERSAL_HPP

#include <vector>
#include "sorting_algorithms.hpp"
#include "stats.hpp"

namespace ou {

// Count number of "breaks" (inversions between consecutive elements)
int countBreaks(const std::vector<int> &data);

// Determine optimal partition threshold via empirical cost scanning
int determinePartitionThreshold(const std::vector<int> &data,
                                double costThreshold,
                                double a,
                                double b,
                                double c);

// Determine optimal break threshold via empirical cost scanning
int determineBreaksThreshold(const std::vector<int> &data,
                             double costThreshold,
                             double a,
                             double b,
                             double c);

// Universal sorter: chooses insertion or quicksort based on thresholds
void universalSort(std::vector<int> &data,
                   int minPartitionSize,
                   int breakThreshold,
                   double a,
                   double b,
                   double c);

} // namespace ou

#endif // ORDENADOR_UNIVERSAL_HPP
