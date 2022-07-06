from distutils import cmd
import glob
import os

from setuptools import setup, Command, Extension

gci_ext = Extension('multiset_multicover._c_multiset_multicover',
                    sources=glob.glob(os.path.join(
                        'src', 'multiset_multicover', '*.cpp')),
                    include_dirs=['includes'],
                    extra_compile_args=['-std=c++17', '-O2'])


class CleanCommand(Command):
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        os.system('rm -vrf ./build ./dist ./*.pyc ./*.tgz ./*.egg-info')


cmdclass = {'clean': CleanCommand}

options = {
    'name': 'multiset_multicover',
    'description': 'MM is a package for running the greedy cover algorithm to perform multiset multicover.',
    'long_description': (
        """This package implements the Greedy Cover algorithm for multisets
        in `C++` and exposes it to Python.
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
        has a log(n)-approximation guarantee where n is the size of the largest set.
        The same guarantee also applies to the multicover problem, as well as the
        multiset multicover problem (n here corresponds to the size of the largest
        set, counting multiplicities)."""
    ),
    'license': 'MIT',
    'version': '0.8',
    'author': 'Euxhen Hasanaj',
    'author_email': 'ehasanaj@cs.cmu.edu',
    'url': 'https://github.com/euxhenh/multiset_multicover',
    'provides': ['multiset_multicover'],
    'package_dir': {'multiset_multicover': os.path.join('src', 'multiset_multicover')},
    'packages': ['multiset_multicover'],
    'cmdclass': cmdclass,
    'ext_modules': [gci_ext],
    'platforms': 'ALL',
    'keywords': ['set', 'cover', 'multiset', 'multicover', 'greedy'],
    'install_requires': [],
    'python_requires': ">=3.7"
}

setup(**options)
