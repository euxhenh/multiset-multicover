import glob
import os

from setuptools import setup, Command, Extension

gci_ext = Extension('multiset_multicover._c_multiset_multicover',
                    sources=glob.glob(os.path.join(
                        'src', 'multiset_multicover', '*.cpp')),
                    include_dirs=['includes'],
                    extra_compile_args=['-std=c++17', '-O2'])

options = {
    'name': 'multiset_multicover',
    'description': 'MM is a package for running the greedy cover algorithm to perform multiset multicover.',
    'license': 'MIT',
    'author': 'Euxhen Hasanaj',
    'author_email': 'ehasanaj@cs.cmu.edu',
    'provides': 'multiset_multicover',
    'package_dir': {'multiset_multicover': os.path.join('src', 'multiset_multicover')},
    'packages': ['multiset_multicover'],
    'ext_modules': [gci_ext],
    'platforms': 'ALL'
}

setup(**options)
