import unittest
import multiset_multicover as mm


class test_interface(unittest.TestCase):
    def test1(self):
        gci = mm.GreedyCoverInstance(4)
        gci.add_multiset([0, 1], [2, 1])
        gci.add_multiset([0, 1, 2, 3], [1, 3, 1, 1])
        gci.add_multiset([2, 1, 0], [3, 1, 5])
        gci.add_multiset([0, 1, 2], [6, 3, 1])
        gci.add_multiset([2, 3], [2, 1])

        assert gci.size == 5
        assert gci.n_elements == 4
        self.assertListEqual(gci.max_coverage_, [14, 8, 7, 2])
        solution = gci.cover(2)
        self.assertListEqual(solution, [3, 1, 4])
        n_elements_rem = gci.n_elements_remaining_
        self.assertListEqual(n_elements_rem, [2, 1, 0])
        coverage_until = gci.coverage_until_
        self.assertListEqual(coverage_until, [0, 1, 2])

        solution = gci.cover(3)
        self.assertListEqual(solution, [3, 4, 1])
        multisets_incomplete_cover = gci.multisets_incomplete_cover_
        self.assertListEqual(multisets_incomplete_cover, [3])
        coverage_until = gci.coverage_until_
        self.assertListEqual(coverage_until, [1, 2, 3])

    def test2(self):
        gci = mm.GreedyCoverInstance(4)
        gci.add_multiset([0, 1], [2, 1])
        gci.add_multiset([0, 1, 2, 3], [1, 3, 1, 1])
        gci.add_multiset([2, 1, 0], [3, 1, 5])
        gci.add_multiset([2, 3], [2, 1])
        gci.add_multiset([0, 1, 2], [6, 3, 2])

        solution = gci.cover(2, max_iters=1)
        self.assertListEqual(solution, [4])
        leftovers = gci.leftovers_
        self.assertListEqual(leftovers, [0, 0, 0, 2])

        self.assertTupleEqual(gci[1], ([0, 1, 2, 3], [1, 3, 1, 1]))

        try:
            gci[0] = 1
            assert False
        except:
            pass

        gci.delete_multiset(1)
        solution = gci.cover(2, max_iters=1)
        self.assertListEqual(solution, [3])
        leftovers = gci.leftovers_
        self.assertListEqual(leftovers, [0, 0, 0, 1])

        try:
            gci.cover(23151324513512345134513254135134531)
            assert False
        except:
            pass

        try:
            gci.cover("foo")
            assert False
        except:
            pass

        try:
            gci.cover(234.1345)
            assert False
        except:
            pass

        try:
            gci.cover([234.123, 2])
            assert False
        except:
            pass


if __name__ == "__main__":
    unittest.main()
