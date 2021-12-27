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
    'license': 'MIT',
    'version': '0.5',
    'author': 'Euxhen Hasanaj',
    'author_email': 'ehasanaj@cs.cmu.edu',
    'url': 'https://github.com/ferrocactus/multiset_multicover',
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
