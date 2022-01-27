#ifndef PYTHON_INTERFACE_H
#define PYTHON_INTERFACE_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cstddef> // size_t
#include <vector>
#include <exception>
#include <string>

using std::size_t;
using std::vector;
using std::string;

#include "GreedyCover.h"

GreedyCoverInstance* create_greedy_cover_instance(size_t n_elements);

PyObject* capsule_GreedyCoverInstance(GreedyCoverInstance* gci);
GreedyCoverInstance* decapsule_GreedyCoverInstance(PyObject* py_gci);

void del_GreedyCoverInstance(PyObject* py_gci);

vector<size_t> create_size_t_vector_from_list(PyObject* py_list);
PyObject* create_list_from_size_t_vector(const vector<size_t>& v);

#ifdef __cplusplus
extern "C" {
#endif

static PyObject* _new_GreedyCoverInstance(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_at(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_effective_at(PyObject* self, PyObject* args, PyObject* keywds);

static PyObject* _GreedyCoverInstance_size(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_n_elements(PyObject* self, PyObject* args, PyObject* keywds);

static PyObject* _GreedyCoverInstance_get_max_coverage(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_get_leftovers(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_get_multisets_incomplete_cover(PyObject* self, PyObject* args, PyObject* keywds);

static PyObject* _GreedyCoverInstance_add_multiset(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_delete_multiset(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance_cover(PyObject* self, PyObject* args, PyObject* keywds);

static PyObject* _GreedyCoverInstance_solution(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance__coverage_until(PyObject* self, PyObject* args, PyObject* keywds);
static PyObject* _GreedyCoverInstance__n_elements_remaining(PyObject* self, PyObject* args, PyObject* keywds);

static PyMethodDef gci_methods[] = {
    { "_new_GreedyCoverInstance", (PyCFunction)_new_GreedyCoverInstance, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_at", (PyCFunction)_GreedyCoverInstance_at, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_effective_at", (PyCFunction)_GreedyCoverInstance_effective_at, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_size", (PyCFunction)_GreedyCoverInstance_size, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_n_elements", (PyCFunction)_GreedyCoverInstance_n_elements, METH_VARARGS | METH_KEYWORDS, "" },

    { "_GreedyCoverInstance_get_max_coverage", (PyCFunction)_GreedyCoverInstance_get_max_coverage, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_get_leftovers", (PyCFunction)_GreedyCoverInstance_get_leftovers, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_get_multisets_incomplete_cover", (PyCFunction)_GreedyCoverInstance_get_multisets_incomplete_cover, METH_VARARGS | METH_KEYWORDS, "" },

    { "_GreedyCoverInstance_add_multiset", (PyCFunction)_GreedyCoverInstance_add_multiset, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_delete_multiset", (PyCFunction)_GreedyCoverInstance_delete_multiset, METH_VARARGS | METH_KEYWORDS, "" },

    { "_GreedyCoverInstance_cover", (PyCFunction)_GreedyCoverInstance_cover, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance_solution", (PyCFunction)_GreedyCoverInstance_solution, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance__coverage_until", (PyCFunction)_GreedyCoverInstance__coverage_until, METH_VARARGS | METH_KEYWORDS, "" },
    { "_GreedyCoverInstance__n_elements_remaining", (PyCFunction)_GreedyCoverInstance__n_elements_remaining, METH_VARARGS | METH_KEYWORDS, "" },
    { NULL }
};

static struct PyModuleDef gcimodule = {
    PyModuleDef_HEAD_INIT,
    "_c_multiset_multicover",
    NULL,
    -1,
    gci_methods
};

PyMODINIT_FUNC PyInit__c_multiset_multicover(void)
{
    return PyModule_Create(&gcimodule);
}

#ifdef __cplusplus
}
#endif

#endif // PYTHON_INTERFACE_H