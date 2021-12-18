#ifndef MULTISET_H
#define MULTISET_H

#include <algorithm> // min_element
#include <cstddef> // size_t
#include <iostream> // ostream
#include <numeric> // accumulate
#include <vector>

using std::size_t;
using std::vector;

#include "BaseSet.h" // BaseSet
#include "Utils.h" // Exception

class MultiSet : public BaseSet {
public:
    MultiSet(const vector<size_t>& elements);
    MultiSet(const vector<size_t>& elements, const vector<size_t>& multiplicity);

    size_t value() const;
    void consume(const vector<size_t>& upper_limits);
    void reset();

    friend std::ostream& operator<<(std::ostream& os, const MultiSet& ms);

protected:
    size_t _value = 0;
    vector<size_t> _leftovers;
    const vector<size_t> _multiplicity;

private:
    void __init_leftovers();
    vector<size_t> __default_multiplicity();
};

#endif // MULTISET_H