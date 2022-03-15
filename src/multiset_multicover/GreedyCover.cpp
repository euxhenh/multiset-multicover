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
    return this->at(index);
}

const MultiSet& GreedyCoverInstance::at(size_t index) const
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

void GreedyCoverInstance::__check_elements(const vector<size_t>& elements) const
{
    if (*std::min_element(elements.begin(), elements.end()) < 0)
        throw Exception("Cannot accept negative elements.");
    if (*std::max_element(elements.begin(), elements.end()) >= this->_n_elements)
        throw Exception("Found element greater than number of elements.");
}

void GreedyCoverInstance::add_multiset(const vector<size_t>& elements)
{
    this->__check_elements(elements);
    this->_multisets.emplace_back(elements); // Implicit conversion taking place
    this->__increase_max_coverage(this->_multisets[this->size() - 1]); // Use last multiset to update coverage
}

void GreedyCoverInstance::add_multiset(const vector<size_t>& elements, const vector<size_t>& mult)
{
    this->__check_elements(elements);
    this->_multisets.emplace_back(elements, mult); // Implicit conversion taking place
    this->__increase_max_coverage(this->_multisets[this->size() - 1]);
}

void GreedyCoverInstance::delete_multiset(size_t index)
{
    this->__decrease_max_coverage(index);
    this->_multisets.erase(this->_multisets.begin() + index);
}

vector<size_t> GreedyCoverInstance::__cover()
{
    // _exclusive = false <=> use same coverage for all
    // _exclusive = true <=> use individual coverages
    this->__init_leftovers();
    this->__init_remaining_msets();
    this->__reset_msets();
    this->_coverage_until.clear();
    this->_n_elements_remaining.clear();
    this->solution.clear();

    while (!this->__stop()) {
        size_t value, total_value;
        size_t best_val = 0, best_total_val = 0;
        list<size_t>::iterator ut;
        for (auto it = this->_remaining_msets.begin(); it != this->_remaining_msets.end(); ++it) {
            // First consume
            // This takes care of the starting point where multiplicities
            // are not clipped to the requested coverage
            this->_multisets[*it].consume(this->_leftovers);
            value = this->_multisets[*it].value();
            if (value > best_val) {
                best_val = value;
                best_total_val = this->_multisets[*it].total_value();
                ut = it;
            } else if (value == best_val) { // Update if better total value
                total_value = this->_multisets[*it].total_value();
                if (total_value > best_total_val) {
                    best_total_val = total_value;
                    ut = it;
                }
            }
        }
        this->solution.push_back(*ut);
        this->__update_leftovers(this->_multisets[*ut]);
        this->_coverage_until.push_back(this->__current_coverage());
        this->_n_elements_remaining.push_back(this->__compute_n_ele_rem());
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
    if (coverage.size() != this->_n_elements)
        throw Exception("Coverage size differs from the number of elements.");
    this->_coverage_idx = coverage;
    this->_exclusive = true;
    return this->__cover();
}

vector<size_t> GreedyCoverInstance::cover(const vector<size_t>& coverage, size_t max_iters)
{
    if (coverage.size() != this->_n_elements)
        throw Exception("Coverage size differs from the number of elements.");
    this->_coverage_idx = coverage;
    this->_max_iters = max_iters;
    this->_exclusive = true;
    return this->__cover();
}

void GreedyCoverInstance::__increase_max_coverage(const MultiSet& mset)
{
    for (size_t i = 0; i < mset.size(); ++i)
        this->_max_coverage[mset[i].first] += mset[i].second;
}

void GreedyCoverInstance::__decrease_max_coverage(size_t index)
{
    if (index >= this->size())
        throw Exception("Index out of bound.");
    for (size_t i = 0; i < this->_multisets[index].size(); ++i)
        this->_max_coverage[this->_multisets[index][i].first] -= this->_multisets[index][i].second;
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
        if (this->_leftovers[mset[i].first] <= mset[i].second)
            this->_leftovers[mset[i].first] = 0;
        else
            this->_leftovers[mset[i].first] = this->_leftovers[mset[i].first] - mset[i].second;
}

void GreedyCoverInstance::__init_remaining_msets()
{
    this->_remaining_msets.clear();
    for (size_t i = 0; i < this->size(); ++i)
        this->_remaining_msets.push_back(i);
}

size_t GreedyCoverInstance::__compute_n_ele_rem() const
{
    size_t n_ele_rem = 0;
    for (size_t i = 0; i < this->_n_elements; ++i)
        n_ele_rem += (this->_leftovers[i] > 0);
    return n_ele_rem;
}

void GreedyCoverInstance::__reset_msets()
{
    for (size_t i = 0; i < this->size(); ++i)
        this->_multisets[i].reset_leftovers();
}

bool GreedyCoverInstance::__stop() const
{
    if (this->_remaining_msets.empty()) {
#ifdef DEBUG
        cout << "Stopping as no sets left.\n";
#endif
        return true;
    }

    if (this->_max_iters > 0 && this->solution.size() >= this->_max_iters) {
#ifdef DEBUG
        cout << "Reached max number of iterations.\n";
#endif
        return true;
    }

    size_t maxel = *std::max_element(this->_leftovers.begin(), this->_leftovers.end());
    if (maxel <= 0) {
#ifdef DEBUG
        cout << "Reached desired coverage.\n";
#endif
        return true;
    }
    return false;
}

size_t GreedyCoverInstance::__current_coverage() const
{
    size_t cc = SIZE_MAX;
    // Note, if max coverage for some element is smaller than
    // the desired coverage, then the desired coverage will be considered

    if (!this->_exclusive)
        for (size_t i = 0; i < this->_n_elements; ++i)
            // No issue with minus since leftovers are always <=
            cc = std::min(this->_coverage_all - this->_leftovers[i], cc);
    else
        for (size_t i = 0; i < this->_n_elements; ++i)
            cc = std::min(this->_coverage_idx[i] - this->_leftovers[i], cc);
    return cc;
}