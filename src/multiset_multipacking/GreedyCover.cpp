#include "GreedyCover.h"

GreedyCoverInstance::GreedyCoverInstance(size_t n_elements)
    : _n_elements(n_elements)
{
    if (n_elements <= 0)
        throw Exception("Number of elements must be positive.");
}

const MultiSet& GreedyCoverInstance::operator[](size_t index) const
{
    if (index >= this->size())
        throw Exception("Index out of bound.");
    return this->_multisets[index];
}

size_t GreedyCoverInstance::size() const
{
    return this->_multisets.size();
}

size_t GreedyCoverInstance::n_elements() const
{
    return this->_n_elements;
}

void GreedyCoverInstance::add_multiset(const vector<size_t>& mset)
{
    if (*std::min_element(mset.begin(), mset.end()) <= 0)
        throw Exception("Cannot accept negative elements.");
    if (*std::max_element(mset.begin(), mset.end()) >= this->_n_elements)
        throw Exception("Found element greater than n_elements.");

    this->_multisets.emplace_back(mset); // Implicit conversion taking place
}

void GreedyCoverInstance::add_multiset(const vector<size_t>& mset, const vector<size_t>& mult)
{
    if (*std::min_element(mset.begin(), mset.end()) <= 0)
        throw Exception("Cannot accept negative elements.");
    if (*std::max_element(mset.begin(), mset.end()) >= this->_n_elements)
        throw Exception("Found element greater than n_elements.");

    this->_multisets.emplace_back(mset, mult); // Implicit conversion taking place
}