#include "BaseSet.h"

BaseSet::BaseSet(const vector<size_t>& elements)
    : _n_elements(elements.size())
    , _elements(elements)
{
#ifdef DEBUG
    cout << "Constructing Base Set " << this << " with " << _n_elements << " elements." << endl;
#endif
    if (*std::min_element(elements.begin(), elements.end()) < 0)
        throw Exception("Cannot accept negative elements.");
}

BaseSet::BaseSet(const BaseSet& other)
    : _n_elements(other._n_elements)
{
    this->_elements.resize(other._n_elements);
    std::copy(other._elements.begin(), other._elements.end(), this->_elements.begin());
#ifdef DEBUG
    cout << "Copying " << &other << " to " << this << endl;
#endif
}

BaseSet& BaseSet::operator=(const BaseSet& other)
{
    if (this != &other) {
        this->_n_elements = other._n_elements;
        this->_elements.resize(other._n_elements);
        std::copy(other._elements.begin(), other._elements.end(), this->_elements.begin());
    }
    return *this;
#ifdef DEBUG
    cout << "Assigning " << &other << " to " << this << endl;
#endif
}

const size_t& BaseSet::operator[](size_t index) const
{
    return this->at(index);
}

const size_t& BaseSet::at(size_t index) const
{
    if (index >= this->_n_elements)
        throw Exception("Index out of bound.");
    return this->_elements[index];
}

size_t BaseSet::size() const
{
    return this->_n_elements;
}

size_t BaseSet::min() const
{
    return *std::min_element(this->_elements.begin(), this->_elements.end());
}

size_t BaseSet::max() const
{
    return *std::max_element(this->_elements.begin(), this->_elements.end());
}

vector<size_t> BaseSet::get_elements() const
{
    return this->_elements;
}

std::ostream& operator<<(std::ostream& os, const BaseSet& bs)
{
    os << "[" << bs[0];
    if (bs.size() <= 10) {
        for (size_t i = 1; i < bs.size(); ++i)
            os << ", " << bs[i];
    } else {
        for (size_t i = 1; i < 5; ++i)
            os << ", " << bs[i];
        os << ", ...";
        for (size_t i = bs.size() - 5; i < bs.size(); ++i)
            os << ", " << bs[i];
    }
    os << "]\n";
    return os;
}