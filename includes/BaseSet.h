#ifndef BASESET_H
#define BASESET_H

#include <algorithm> // min_element, max_element
#include <cstddef> // size_t
#include <iostream> // ostream
#include <vector>
using std::size_t;
using std::vector;

#include "Utils.h" // Exception

class BaseSet {
public:
    BaseSet(const vector<size_t>& elements);
    const size_t& operator[](size_t index) const;
    size_t size() const;
    size_t min() const;
    size_t max() const;

    friend std::ostream& operator<<(std::ostream& os, const BaseSet& bs);

protected:
    const size_t _n_elements;
    const vector<size_t> _elements;
};

#endif // BASESET_H