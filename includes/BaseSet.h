#ifndef BASESET_H
#define BASESET_H

#include <algorithm> // min_element, max_element, copy
#include <cstddef> // size_t
#include <iostream> // ostream
#include <vector>
using std::size_t;
using std::vector;

#include "Utils.h" // Exception

class BaseSet {
public:
    BaseSet(const vector<size_t>& elements);
    BaseSet(const BaseSet& other);
    BaseSet& operator=(const BaseSet& other);
    const size_t& operator[](size_t index) const;
    const size_t& at(size_t index) const;
    size_t size() const;
    size_t min() const;
    size_t max() const;

    vector<size_t> get_elements() const;

    friend std::ostream& operator<<(std::ostream& os, const BaseSet& bs);

protected:
    size_t _n_elements;
    vector<size_t> _elements;
};

#endif // BASESET_H