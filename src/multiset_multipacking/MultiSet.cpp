#include "MultiSet.h"

MultiSet::MultiSet(const vector<size_t>& elements)
    : BaseSet(elements)
    , _multiplicity(__default_multiplicity())
{
#ifdef DEBUG
    cout << "Constructing Multi Set " << this << endl;
#endif
    this->__init_leftovers();
}

MultiSet::MultiSet(const vector<size_t>& elements, const vector<size_t>& multiplicity)
    : BaseSet(elements)
    , _multiplicity(multiplicity)
{
#ifdef DEBUG
    cout << "Constructing Multi Set " << this << endl;
#endif
    if (*std::min_element(multiplicity.begin(), multiplicity.end()) <= 0)
        throw Exception("Cannot only accept positive multiplicities.");
    this->__init_leftovers();
}

void MultiSet::reset()
{
    this->__init_leftovers();
}

void MultiSet::__init_leftovers()
{
    this->_leftovers = this->_multiplicity;
    this->_value = std::accumulate(this->_multiplicity.begin(), this->_multiplicity.end(), 0);
#ifdef DEBUG
    cout << "Initializing leftovers\n";
    for (auto c : this->_leftovers)
        cout << c << " ";
    cout << endl;
#endif
}

vector<size_t> MultiSet::__default_multiplicity()
{
    return vector<size_t>(this->_n_elements, 1);
}

size_t MultiSet::value() const
{
    return this->_value;
}

void MultiSet::consume(const vector<size_t>& upper_limits)
{
    this->_value = 0;
    for (size_t i = 0; i < this->_n_elements; ++i) {
        this->_leftovers[i] = std::min(this->_leftovers[i], upper_limits[this->_elements[i]]);
        this->_value += this->_leftovers[i];
    }
}

std::ostream& operator<<(std::ostream& os, const MultiSet& ms)
{
    os << "[(" << ms[0] << ", " << ms._multiplicity[0] << ")";
    if (ms.size() <= 10) {
        for (size_t i = 1; i < ms.size(); ++i)
            os << ", (" << ms[i] << ", " << ms._multiplicity[i] << ")";
    } else {
        for (size_t i = 1; i < 5; ++i)
            os << ", " << ms[i];
        os << ", ...";
        for (size_t i = ms.size() - 5; i < ms.size(); ++i)
            os << ", (" << ms[i] << ", " << ms._multiplicity[i] << ")";
    }
    os << "]\n";
    return os;
}