from . import _c_multiset_multicover as _c_mm


class GreedyCoverInstance:
    """
    Creates a greedy cover instance. It can accept multisets and run
    the greedy cover algorithm. The coverage factor can be a single integer
    or a specific integer for each element.

    Examples
    ________
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

    def __init__(self, n_elements):
        """
        The object can be initialized by specifying the number of elements.
        All elements are assumed to be in range [0, n_elements-1] and
        adding any elements that extend this range will raise an error.
        If your data is not in this range, or if it does not consist of numerical
        values, one can always encode it by using, for example,
        sklearn.preprocessing.LabelEncoder.

        Parameters
        __________
        n_elements: int
            Number of elements.
        """
        n_elements = int(n_elements)
        if n_elements < 1:
            raise ValueError("Cannot have less than 1 element.")

        self._n_elements = n_elements
        self._gci = _c_mm._new_GreedyCoverInstance(n_elements)

    def __getitem__(self, index):
        """
        Returns the multiset at `index`.
        """
        index = int(index)
        return _c_mm._GreedyCoverInstance_at(self._gci, index)

    def __repr__(self):
        return f"GreedyCoverInstance({self.n_elements})"

    def __str__(self):
        return f"GreedyCoverInstance({self.n_elements}) with {self.size} multisets"

    def effective_at(self, index):
        """
        Returns the multiset at `index` with a corrected multiplicity.
        """
        index = int(index)
        return _c_mm._GreedyCoverInstance_effective_at(self._gci, index)

    @property
    def size(self):
        """
        Number of multisets added to the object so far.
        """
        return _c_mm._GreedyCoverInstance_size(self._gci)

    @property
    def n_elements(self):
        """
        Number of elements that the object supports.
        """
        return _c_mm._GreedyCoverInstance_n_elements(self._gci)

    @property
    def max_coverage_(self):
        """
        The total multiplicity of each element across all multisets.
        """
        return _c_mm._GreedyCoverInstance_get_max_coverage(self._gci)

    @property
    def leftovers_(self):
        """
        Will only return a value if coverage has been run.
        """
        return _c_mm._GreedyCoverInstance_get_leftovers(self._gci)

    @property
    def multisets_incomplete_cover_(self):
        """
        List of multisets for which the desired coverage cannot be achieved.
        Will only return a value if coverage has been run.
        """
        return _c_mm._GreedyCoverInstance_get_multisets_incomplete_cover(self._gci)

    def add_multiset(self, elements, multiplicity=None):
        """
        Adds a multiset to the object. If multiplicity is not specified,
        each object is assumed to have a multiplicity of 1.

        Parameters
        __________
        elements: list
            List of elements.
        multiplicity: list or None
            If not None, must have the same length as elements.
            Specifies multiplicities for each element. Multiplicity must be
            an integer greater than 0.
        """
        if min(elements) < 0:
            raise ValueError("Cannot accept negative elements.")
        if max(elements) >= self._n_elements:
            raise ValueError("Found value greater than n_elements.")
        if multiplicity is not None and min(multiplicity) <= 0:
            raise ValueError("Can only accept positive multiplicities.")
        if multiplicity is not None and len(multiplicity) != len(elements):
            raise ValueError(
                "Multiplicities must have the same length as the number of elements.")
        _c_mm._GreedyCoverInstance_add_multiset(
            self._gci, elements, multiplicity)

    def delete_multiset(self, index):
        """
        Removes the multiset given by index.
        """
        index = int(index)
        if index >= self.size or index < 0:
            raise ValueError("Index out of bound.")
        _c_mm._GreedyCoverInstance_delete_multiset(self._gci, index)

    def cover(self, coverage, max_iters=0):
        """
        Runs the greedy cover algorithm. The specified coverage can be a single
        integer (in which case the same coverage factor is applied to all
        elements), or it can be element-specific. If the latter case,
        the length of coverage must equal n_elements. Optionally,
        if a maximum number of sets is desired, one can specify a positive
        value for max_iters. If max_iters is set to 0, the algorithm will
        run until the desired coverage is reached.

        If some elements cannot be covered to the desired coverage, the algorithm
        will not raise an error, but will try to each the maximum achievable
        coverage for those elements.

        Parameters
        __________
        coverage: int or list
            If int, must be greater than 0. If list, the length must equal n_elements.
        max_iters: int
            If 0, will not limit the number of iterations (multisets selected).
        """
        max_iters = int(max_iters)
        if isinstance(coverage, int):
            coverage = int(coverage)
        if max_iters < 0:
            raise ValueError("Cannot accept negative number of iterations.")
        return _c_mm._GreedyCoverInstance_cover(self._gci, coverage, max_iters)

    @property
    def solution(self):
        """
        Returns the solution indices.
        """
        return _c_mm._GreedyCoverInstance_solution(self._gci)

    @property
    def coverage_until_(self):
        """
        Returns the coverage factor for each selected element. Has the same
        length as solution.
        """
        return _c_mm._GreedyCoverInstance__coverage_until(self._gci)

    @property
    def n_elements_remaining_(self):
        """
        Returns the coverage factor for each selected element. Has the same
        length as solution.
        """
        return _c_mm._GreedyCoverInstance__n_elements_remaining(self._gci)
