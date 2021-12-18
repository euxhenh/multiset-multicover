#ifndef GREEDYCOVER_H
#define GREEDYCOVER_H

#include <algorithm> // min_element, max_element
#include <cstddef> // size_t
#include <iostream> // ostream
#include <vector>

using std::size_t;
using std::vector;

#include "MultiSet.h" // MultiSet
#include "Utils.h" // Exception

class GreedyCoverInstance {
public:
    GreedyCoverInstance(size_t n_elements);
    const MultiSet& operator[](size_t index) const;

    vector<size_t> selected;
    vector<size_t> _coverage_until;

    size_t size() const;
    size_t n_elements() const;

    void add_multiset(const vector<size_t>& mset);
    void add_multiset(const vector<size_t>& mset, const vector<size_t>& mult);
    vector<size_t> cover(size_t coverage);
    vector<size_t> cover(size_t coverage, size_t max_iters);
    vector<size_t> cover(const vector<size_t>& coverage);
    vector<size_t> cover(const vector<size_t>& coverage, size_t max_iters);

protected:
    const size_t _n_elements;
    vector<size_t> _upper_limits;
    vector<MultiSet> _multisets;
    size_t __coverage_all;
    const vector<size_t> __coverage_idx;
};

#endif // GREEDYCOVER_H