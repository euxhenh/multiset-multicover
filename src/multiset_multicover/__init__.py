# -*- coding: utf-8 -*-
r"""
This package implements the Greedy Cover algorithm for multisets
in ``C++`` and exposes it to Python.
Given a universe of elements U, and a family of subsets F = {S1, ..., Sn}
of U, the set cover problem asks to find the smallest number of sets in F
such that every element of U appears in at least one such set.
This can be extended to a multicover problem, where we ask that
every element be included at least k sets. This in turn, can be extended
to accomodate multisets, where each element in Si also has a given
multiplicity.

The set cover problem is NP hard. The best known algorithm
is a greedy approach that iteratively selects the set with the largest
number of elements that have not been covered yet. This algorithm
has a log(n)-approximation guarantee where n is the number of elements in U.
The same guarantee also applies to the multicover problem, as well as the
multiset multicover problem (n here corresponds to all the elements including
multiplicities, hence, the guarantees are worse).

Examples
________

To run the greedy cover algorithm, one needs to create a GreedyCoverInstance
object and add multisets to it. The coverage factor can be a single integer
or a specific integer for each element in U.
The solution is a list of integers corresponding to the index of the sets
included (in order of selection).

  >>> import multiset_multicover as mm

  >>> gci = mm.GreedyCoverInstance(4)
  >>> gci.add_multiset([1, 2, 3])  # if no multiplicity provided, it defaults to 1
  >>> gci.add_multiset([0, 1, 2], multiplicity=[2, 3, 1])
  >>> gci.add_multiset([0, 1, 2, 3])

  >>> gci.cover(1)
  Output: [2]
  >>> gci.cover([2, 1, 1, 1])
  Output: [1, 0]
"""

from .python_source import GreedyCoverInstance
