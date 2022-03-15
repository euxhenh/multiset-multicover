#include "MultiSet.h"

MultiSet::MultiSet(const vector<size_t>& elements)
    : BaseSet(elements)
    , _multiplicity(__default_multiplicity())
    , __maxel(*std::max_element(this->_elements.begin(), this->_elements.end()))
{
#ifdef DEBUG
    cout << "Constructing Multi Set " << this << endl;
#endif
    this->__init_leftovers();
}

MultiSet::MultiSet(const vector<size_t>& elements, const vector<size_t>& multiplicity)
    : BaseSet(elements)
    , _multiplicity(multiplicity)
    , __maxel(*std::max_element(this->_elements.begin(), this->_elements.end()))
{
#ifdef DEBUG
    cout << "Constructing Multi Set " << this << endl;
#endif
    if (elements.size() != multiplicity.size())
        throw Exception("Found elements and multiplicities of differing sizes.");
    if (*std::min_element(multiplicity.begin(), multiplicity.end()) <= 0)
        throw Exception("Can only accept positive multiplicities.");
    this->__init_leftovers();
}

const pair<size_t, size_t> MultiSet::operator[](size_t index) const
{
    return this->at(index);
}

const pair<size_t, size_t> MultiSet::at(size_t index) const
{
    if (index >= this->_n_elements)
        throw Exception("Index out of bound.");
    return { this->_elements[index], this->_multiplicity[index] };
}

vector<size_t> MultiSet::get_multiplicities() const
{
    return this->_multiplicity;
}

vector<size_t> MultiSet::get_leftovers() const
{
    return this->_leftovers;
}

void MultiSet::reset_leftovers()
{
    this->__init_leftovers();
}

void MultiSet::__init_leftovers()
{
    this->_leftovers = this->_multiplicity;
    this->_value = std::accumulate(this->_multiplicity.begin(), this->_multiplicity.end(), 0);
    this->_total_value = this->_value;
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

size_t MultiSet::total_value() const
{
    return this->_total_value;
}

void MultiSet::consume(const vector<size_t>& upper_limits)
{
    if (upper_limits.size() <= this->__maxel)
        throw Exception("Upper limits size smaller than the number of elements.");

    this->_value = 0;
    for (size_t i = 0; i < this->_n_elements; ++i) {
        this->_leftovers[i] = std::min(this->_leftovers[i], upper_limits[this->_elements[i]]);
        this->_value += this->_leftovers[i];
    }
}

std::ostream& operator<<(std::ostream& os, const MultiSet& ms)
{
    os << "[(" << ms[0].first << ", " << ms[0].second << ")";
    if (ms.size() <= 10) {
        for (size_t i = 1; i < ms.size(); ++i)
            os << ", (" << ms[i].first << ", " << ms[i].second << ")";
    } else {
        for (size_t i = 1; i < 5; ++i)
            os << ", " << ms[i].first;
        os << ", ...";
        for (size_t i = ms.size() - 5; i < ms.size(); ++i)
            os << ", (" << ms[i].first << ", " << ms[i].second << ")";
    }
    os << "]\n";
    return os;
}