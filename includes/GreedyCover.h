#ifndef GREEDYCOVER_H
#define GREEDYCOVER_H

#include <algorithm> // min_element, max_element
#include <cstddef> // size_t
#include <iostream> // ostream
#include <list>
#include <vector>

using std::list;
using std::size_t;
using std::vector;

#include "MultiSet.h" // MultiSet
#include "Utils.h" // Exception

class GreedyCoverInstance {
public:
    GreedyCoverInstance(size_t n_elements);
    const MultiSet& operator[](size_t index) const;
    const MultiSet& at(size_t index) const;

    vector<size_t> solution;
    vector<size_t> _coverage_until;
    vector<size_t> _n_elements_remaining;

    size_t size() const; // Number of sets
    size_t n_elements() const; // Number of elements across all sets

    // Getters
    vector<size_t> get_max_coverage() const;
    vector<size_t> get_leftovers() const;
    vector<size_t> get_multisets_incomplete_cover() const;

    void add_multiset(const vector<size_t>& elements);
    void add_multiset(const vector<size_t>& elements, const vector<size_t>& mult);
    void delete_multiset(size_t index);
    vector<size_t> cover(size_t coverage);
    vector<size_t> cover(size_t coverage, size_t max_iters);
    vector<size_t> cover(const vector<size_t>& coverage);
    vector<size_t> cover(const vector<size_t>& coverage, size_t max_iters);

protected:
    vector<MultiSet> _multisets;

    bool _exclusive;
    bool _covered = false;
    const size_t _n_elements; // Number of elements in all sets
    size_t _max_iters = 0; // Max number of sets to pick

    vector<size_t> _max_coverage;
    vector<size_t> _leftovers;
    list<size_t> _remaining_msets;
    vector<size_t> _multisets_incomplete_cover;

    size_t _coverage_all; // coverage factor if same for all elements
    vector<size_t> _coverage_idx; // coverage factors for each element individually

private:
    void __increase_max_coverage(const MultiSet& mset);
    void __decrease_max_coverage(size_t index);
    void __init_leftovers();
    void __update_leftovers(const MultiSet& mset);
    void __init_remaining_msets();
    void __reset_msets();
    bool __stop() const;
    void __check_elements(const vector<size_t>& elements) const;
    vector<size_t> __cover();
    size_t __compute_n_ele_rem() const;
    size_t __current_coverage() const;
};

#endif // GREEDYCOVER_H