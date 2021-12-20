#include "GreedyCover.h"

GreedyCoverInstance::GreedyCoverInstance(size_t n_elements)
    : _n_elements(n_elements)
{
    if (n_elements <= 0)
        throw Exception("Number of elements must be positive.");

    this->_max_coverage.resize(this->_n_elements); // init'ed with 0's
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

vector<size_t> GreedyCoverInstance::get_max_coverage() const
{
    return this->_max_coverage;
}

vector<size_t> GreedyCoverInstance::get_leftovers() const
{
    if (!this->_covered)
        throw Exception("No coverage has been specified.");
    return this->_leftovers;
}

vector<size_t> GreedyCoverInstance::get_multisets_incomplete_cover() const
{
    if (!this->_covered)
        throw Exception("No coverage has been specified.");
    return this->_multisets_incomplete_cover;
}

void GreedyCoverInstance::add_multiset(const vector<size_t>& mset)
{
    if (*std::min_element(mset.begin(), mset.end()) < 0)
        throw Exception("Cannot accept negative elements.");
    if (*std::max_element(mset.begin(), mset.end()) >= this->_n_elements)
        throw Exception("Found element greater than number of elements.");

    this->_multisets.emplace_back(mset); // Implicit conversion taking place
    this->__update_max_coverage(this->_multisets[this->size() - 1]); // Use last multiset to update coverage
}

void GreedyCoverInstance::add_multiset(const vector<size_t>& mset, const vector<size_t>& mult)
{
    if (*std::min_element(mset.begin(), mset.end()) < 0)
        throw Exception("Cannot accept negative elements.");
    if (*std::max_element(mset.begin(), mset.end()) >= this->_n_elements)
        throw Exception("Found element greater than number of elements.");

    this->_multisets.emplace_back(mset, mult); // Implicit conversion taking place
    this->__update_max_coverage(this->_multisets[this->size() - 1]);
}

vector<size_t> GreedyCoverInstance::__cover()
{
    // _exclusive = false <=> use same coverage for all
    // _exclusive = true <=> use individual coverages
    this->__init_leftovers();
    this->__init_remaining_msets();

    while (!this->__stop()) {
        size_t value;
        size_t best_val = SIZE_MAX;
        list<size_t>::iterator ut;
        for (auto it = this->_remaining_msets.begin(); it != this->_remaining_msets.end(); ++it) {
            this->_multisets[*it].consume(this->_leftovers);
            value = this->_multisets[*it].value();
            if (value > best_val) {
                best_val = value;
                ut = it;
            }
        }
        this->__update_leftovers(this->_multisets[*ut]);
        this->_remaining_msets.erase(ut);
    }

    this->_covered = true;
    return solution;
}

vector<size_t> GreedyCoverInstance::cover(size_t coverage)
{
    this->_coverage_all = coverage;
    this->_exclusive = false;
    return this->__cover();
}

vector<size_t> GreedyCoverInstance::cover(size_t coverage, size_t max_iters)
{
    this->_coverage_all = coverage;
    this->_max_iters = max_iters;
    this->_exclusive = false;
    return this->__cover();
}

vector<size_t> GreedyCoverInstance::cover(const vector<size_t>& coverage)
{
    this->_coverage_idx = coverage;
    this->_exclusive = true;
    return this->__cover();
}

vector<size_t> GreedyCoverInstance::cover(const vector<size_t>& coverage, size_t max_iters)
{
    this->_coverage_idx = coverage;
    this->_max_iters = max_iters;
    this->_exclusive = true;
    return this->__cover();
}

void GreedyCoverInstance::__update_max_coverage(const MultiSet& mset)
{
    for (size_t i = 0; i < mset.size(); ++i)
        this->_max_coverage[mset[i].first] += mset[i].second;
}

void GreedyCoverInstance::__init_leftovers()
{
    this->_leftovers.resize(this->_n_elements);
    std::fill(this->_leftovers.begin(), this->_leftovers.end(), 0);
    this->_multisets_incomplete_cover.clear();

    if (!this->_exclusive) {
        for (size_t i = 0; i < this->_n_elements; ++i) {
            if (this->_max_coverage[i] < this->_coverage_all)
                this->_multisets_incomplete_cover.push_back(i);
            this->_leftovers[i] = std::min(this->_coverage_all, this->_max_coverage[i]);
        }
    } else {
        for (size_t i = 0; i < this->_n_elements; ++i) {
            if (this->_max_coverage[i] < this->_coverage_idx[i])
                this->_multisets_incomplete_cover.push_back(i);
            this->_leftovers[i] = std::min(this->_coverage_idx[i], this->_max_coverage[i]);
        }
    }
#ifdef DEBUG
    if (!this->_multisets_incomplete_cover.empty()) {
        cout << "Cannot cover elements " << this->_multisets_incomplete_cover[0];
        for (size_t i = 1; i < this->_multisets_incomplete_cover.size(); ++i)
            cout << ", " << this->_multisets_incomplete_cover[i];
        cout << ".\n";
    }
#endif
}

void GreedyCoverInstance::__update_leftovers(const MultiSet& mset)
{
    for (size_t i = 0; i < mset.size(); ++i)
        this->_leftovers[mset[i].first] = std::max(this->_leftovers[mset[i].first] - mset[i].second, size_t(0));
}

void GreedyCoverInstance::__init_remaining_msets()
{
    this->_remaining_msets.clear();
    for (size_t i = 0; i < this->size(); ++i)
        this->_remaining_msets.push_back(i);
}

bool GreedyCoverInstance::__stop() const
{
    if (this->_remaining_msets.empty()) {
#ifdef DEBUG
        cout << "Stopping as no sets left.\n";
#endif
        return true;
    }

    size_t iter = this->solution.size();
    if (this->_max_iters != 0 && iter >= this->_max_iters - 1) {
#ifdef DEBUG
        cout << "Reached max number of iterations.\n";
#endif
        return true;
    }

    size_t sum = std::accumulate(this->_leftovers.begin(), this->_leftovers.end(), 0);
    if (sum <= 0) {
#ifdef DEBUG
        cout << "Reached desired coverage.\n";
#endif
        return true;
    }
    return false;
}