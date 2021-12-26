#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "BaseSet.h"
#include "GreedyCover.h"
#include "MultiSet.h"

using std::cerr;
using std::cout;
using std::endl;
using std::vector;

void test1()
{
    vector<size_t> v = { 0, 6, 2, 3 };

    BaseSet bs(v);
    assert(bs[1] == 6);

    MultiSet bb(v);
    assert(bb.size() == 4);
    assert(bb.at(1).first == 6);
    assert(bb[2].first == 2);
    assert(bb.min() == 0);
    assert(bb.max() == 6);

    try {
        cout << bb[-1].first;
    } catch (Exception e) {
        cout << "Error caught\n";
    }

    vector<size_t> ulimit = { 1, 0, 0, 3, 0, 2, 3 };
    cout << bb << endl;

    vector<size_t> mult = { 1, 2, 1, 5 };
    MultiSet ms(v, mult);
    cout << ms << endl;

    vector<size_t> eat = { 1, 1, 1, 1, 1, 1, 2 };
    cout << ms.value() << endl;
    ms.consume(eat);
    cout << ms.value() << endl;

    GreedyCoverInstance gci(4);
    vector<size_t> g = { 2, 1 };
    gci.add_multiset(g);
    assert(gci.size() == 1);
    assert(gci.n_elements() == 4);
    g[0] = 0;
    assert(gci[0][0].first == 2);

    vector<size_t> gg = { 1, 3 };
    vector<size_t> gg_m = { 3, 2 };
    gci.add_multiset(gg, gg_m);

    vector<size_t> maxc = gci.get_max_coverage();
    assert(maxc[0] == 0);
    assert(maxc[1] == 4);
    assert(maxc[2] == 1);
    assert(maxc[3] == 2);
    maxc[2] = 2;
    vector<size_t> maxc2 = gci.get_max_coverage();
    assert(maxc[2] = 1);

    try {
        vector<size_t> leftovers = gci.get_leftovers();
    } catch (Exception e) {
        cout << "Caught leftovers not init'ed\n";
    }

    gci.cover(3);

    vector<size_t> mmnc = gci.get_multisets_incomplete_cover();
    assert(mmnc.size() == 3);
    assert(mmnc[1] = 2);

    cout << "Test 1 passed.\n";
}

void test2()
{
    GreedyCoverInstance gci(4);
    vector<size_t> x1 = { 0, 1 };
    vector<size_t> m1 = { 2, 1 };
    gci.add_multiset(x1, m1);
    vector<size_t> x2 = { 0, 1, 2, 3 };
    vector<size_t> m2 = { 1, 3, 1, 1 };
    gci.add_multiset(x2, m2);
    vector<size_t> x3 = { 0, 1, 2 };
    vector<size_t> m3 = { 5, 1, 3 };
    gci.add_multiset(x3, m3);
    vector<size_t> x4 = { 0, 1, 2 };
    vector<size_t> m4 = { 6, 3, 1 };
    gci.add_multiset(x4, m4);
    vector<size_t> x5 = { 2, 3 };
    vector<size_t> m5 = { 2, 1 };
    gci.add_multiset(x5, m5);

    auto solution = gci.cover(1);
    assert(solution.size() == 1);
    assert(solution[0] == 1);

    solution = gci.cover(2);
    assert(solution.size() == 3);
    assert(solution[0] == 1);
    assert(solution[1] == 2);
    assert(solution[2] == 4);

    solution = gci.cover(3);
    auto n_ele_rem = gci._n_elements_remaining;
    assert(solution.size() == 3);
    assert(solution[0] == 2);
    assert(solution[1] == 1);
    assert(solution[2] == 4);

    assert(n_ele_rem.size() == 3);
    assert(n_ele_rem[0] == 2);
    assert(n_ele_rem[1] == 1);
    assert(n_ele_rem[2] == 0);

    cout << "Test 2 passed.\n";
}

void test3()
{
    GreedyCoverInstance gci(3);
    vector<size_t> x1 = { 0 };
    vector<size_t> m1 = { 3 };
    gci.add_multiset(x1, m1);
    vector<size_t> x2 = { 1 };
    vector<size_t> m2 = { 3 };
    gci.add_multiset(x2, m2);
    vector<size_t> x3 = { 2 };
    vector<size_t> m3 = { 3 };
    gci.add_multiset(x3, m3);

    auto solution = gci.cover(1);
    auto n_ele_rem = gci._n_elements_remaining;
    assert(solution.size() == 3);
    assert(solution[0] == 0);
    assert(solution[1] == 1);
    assert(solution[2] == 2);

    assert(n_ele_rem.size() == 3);
    assert(n_ele_rem[0] == 2);
    assert(n_ele_rem[1] == 1);
    assert(n_ele_rem[2] == 0);

    cout << "Test 3 passed.\n";
}

void test4()
{
    GreedyCoverInstance gci(3);
    vector<size_t> x1 = { 0 };
    vector<size_t> m1 = { 3 };
    gci.add_multiset(x1, m1);
    vector<size_t> x2 = { 1 };
    vector<size_t> m2 = { 3 };
    gci.add_multiset(x2, m2);
    vector<size_t> x3 = { 2 };
    vector<size_t> m3 = { 3 };
    gci.add_multiset(x3, m3);
    vector<size_t> x4 = { 0, 1, 2 };
    vector<size_t> m4 = { 1, 1, 1 };
    gci.add_multiset(x4, m4);

    auto solution = gci.cover(1);
    assert(solution.size() == 1);
    assert(solution[0] == 3);

    cout << "Test 4 passed.\n";
}

void test5()
{
    GreedyCoverInstance gci(5);
    vector<size_t> x1 = { 0, 2, 4 };
    gci.add_multiset(x1);
    vector<size_t> x2 = { 1, 2, 4 };
    gci.add_multiset(x2);
    vector<size_t> x3 = { 1, 3 };
    gci.add_multiset(x3);
    vector<size_t> x4 = { 0, 2, 3, 4 };
    gci.add_multiset(x4);

    auto solution = gci.cover(1);
    assert(solution.size() == 2);

    solution = gci.cover(2);
    assert(solution.size() == 4);

    cout << "Test 5 passed.\n";
}

void test6()
{
    GreedyCoverInstance gci(5);
    vector<size_t> x1 = { 0, 2, 4 };
    gci.add_multiset(x1);
    vector<size_t> x2 = { 1, 2, 4 };
    gci.add_multiset(x2);
    vector<size_t> x3 = { 1, 3 };
    vector<size_t> m3 = { 2, 1 };
    gci.add_multiset(x3, m3);
    vector<size_t> x4 = { 0, 2, 3, 4 };
    gci.add_multiset(x4);

    auto solution = gci.cover(1);
    assert(solution.size() == 2);

    solution = gci.cover(2);
    assert(solution.size() == 3);

    cout << "Test 6 passed.\n";
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}