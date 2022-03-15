#ifndef MULTISET_H
#define MULTISET_H

#include <algorithm> // min_element
#include <cstddef> // size_t
#include <iostream> // ostream
#include <numeric> // accumulate
#include <utility> // pair
#include <vector>

using std::pair;
using std::size_t;
using std::vector;

#include "BaseSet.h" // BaseSet
#include "Utils.h" // Exception

class MultiSet : public BaseSet {
public:
    MultiSet(const vector<size_t>& elements);
    MultiSet(const vector<size_t>& elements, const vector<size_t>& multiplicity);
    const pair<size_t, size_t> operator[](size_t index) const;
    const pair<size_t, size_t> at(size_t index) const;

    vector<size_t> get_multiplicities() const;
    vector<size_t> get_leftovers() const;

    size_t value() const;
    size_t total_value() const;
    void consume(const vector<size_t>& upper_limits);
    void reset_leftovers();

    friend std::ostream& operator<<(std::ostream& os, const MultiSet& ms);

protected:
    size_t _value = 0;
    size_t _total_value = 0;
    vector<size_t> _leftovers;
    vector<size_t> _multiplicity;

private:
    size_t __maxel;
    void __init_leftovers();
    vector<size_t> __default_multiplicity();
};

#endif // MULTISET_H