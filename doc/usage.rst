Usage
_____

The Python GreedyCoverInstance class is just an interface for a C++
object which is doing the real work. We can construct an instance of
this class:

>>> import multiset_multicover as mm
>>> gci = mm.GreedyCoverInstance(5)

The number of elements is the only argument the class takes. Here
we are using 5 elements. This number can be obtained at any time:

>>> gci.n_elements
5

Calling

>>> gci.size
0

will display the number of multisets added so far. Right now we have 0.
Multisets can be added by calling the `add_multiset` method. This method
takes one argument (elements) and an optional argument (multiplicity).
If multiplicity has been omitted, then the multiplicity for every element
will default to 1.

>>> gci.add_multiset([1, 2, 3])  # Adds elements 1, 2, 3 with multiplicity 1
>>> gci.add_multiset([2, 4], [6, 7])  # Adds elements 2, 3, 4 with mult. 6, 5, 7, respectively
>>> gci.add_multiset([3], [5])
>>> gci.add_multiset([0, 1, 4], [1, 2, 1])

The current maximum coverage for each element can be obtained via:

>>> gci.max_coverage_
[1, 3, 7, 6, 8]

To run a multicover, one can needs to specify the coverage factor. This
can be a single integer x, in which case, the algorithm will attempt to cover
each element x times, or it can be a list of length `gci.n_elements` where
for each element we require a specific coverage factor.

>>> solution = gci.cover(1)
>>> solution
[0, 3]

When a `coverage` has been specified, each multiset's "value" is updated
by clipping the multiplicity of every element to `coverage`. Therefore,
in our example above, the value of the first multiset is going to be 3,
since each element has multiplicity 1. However, the value of the second
multiset is going to be 2, since each of the multiplicities got clipped to 1.
The value of the third will be 1, and so on.

When two multisets have the same value, the one that has the highest total
value will get picked. Therefore, set 0 gets picked first.
This covers elements 1, 2, 3, to the desired coverage leaving elements 0 and 4.
Both of these elements can be covered by including set 3.

One can obtain the coverage factor up until the i-th set in
the solution has been selected:

>>> gci.coverage_until_
[0, 1]

I.e., 0 coverage after the first set was picked, followed by 1 coverage
after the second set was picked.

Similarly, one can get the number of elements left to cover:

>>> gci.n_elements_remaining_
[2, 0]

I.e., 2 elements remain after first set was picked (elements 0 and 4).

When the coverage factor is higher than the possible coverage for some
element, then the algorithm will attempt to cover that element entirely.
For example,

>>> solution = gci.cover(2)
[1, 3, 2]

Note that in this example it is impossible to cover element 0 twice.
The list of elements that cannot be covered to the desired coverage can be
obtained by:

>>> gci.multisets_incomplete_cover_
[0]

We could also require a specific coverage for each element by passing
a list to the `cover` method instead:

>>> solution = gci.cover([1, 2, 3, 2, 2])
>>> solution
[1, 3, 2]
