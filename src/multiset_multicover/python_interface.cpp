#include "python_interface.h"

GreedyCoverInstance* create_greedy_cover_instance(size_t n_elements)
{
    if (n_elements <= 0)
        throw Exception("Number of elements must be positive.");

    GreedyCoverInstance* gci = new GreedyCoverInstance(n_elements);
    return gci;
}

PyObject* capsule_GreedyCoverInstance(GreedyCoverInstance* gci)
{
    PyObject* py_gci = PyCapsule_New(
        gci, "multiset_multipacking.GreedyCover.GreedyCoverInstance", del_GreedyCoverInstance);
    return py_gci;
}

GreedyCoverInstance* decapsule_GreedyCoverInstance(PyObject* py_gci)
{
    GreedyCoverInstance* gci = (GreedyCoverInstance*)PyCapsule_GetPointer(
        py_gci, "multiset_multipacking.GreedyCover.GreedyCoverInstance");
    return gci;
}

void del_GreedyCoverInstance(PyObject* py_gci)
{
    GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
    delete gci;
}

PyObject* create_list_from_size_t_vector(const vector<size_t>& v)
{
    PyObject* py_list = PyList_New(v.size());
    if (!py_list)
        throw Exception("Cannot allocate memory for list.");

    for (size_t i = 0; i < v.size(); ++i) {
        PyObject* num = PyLong_FromSize_t(v[i]);
        if (!num) {
            Py_DECREF(py_list);
            throw Exception("Cannot allocate memory for list.");
        }
        PyList_SET_ITEM(py_list, i, num);
    }
    return py_list;
}

vector<size_t> create_size_t_vector_from_list(PyObject* py_list)
{
    size_t n = PyList_Size(py_list);
    vector<size_t> v(n);
    for (size_t i = 0; i < n; ++i) {
        PyObject* py_item = PyList_GetItem(py_list, i);
        if (PyLong_Check(py_item)) {
            size_t num = PyLong_AsSize_t(py_item);
            v[i] = num;
        } else {
            throw Exception("Non integer value found.");
        }
    }
    return v;
}

#ifdef __cplusplus
extern "C" {
#endif
PyObject* _new_GreedyCoverInstance(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_n_elements = NULL;
    static const char* kwlist[] = { "n_elements", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|O", (char**)kwlist, &py_n_elements))
        return NULL;

    try {
        size_t n_elements = PyLong_AsSize_t(PyNumber_Long(py_n_elements));
        GreedyCoverInstance* gci = create_greedy_cover_instance(n_elements);
        PyObject* py_gci = capsule_GreedyCoverInstance(gci);
        return py_gci;
    } catch (std::exception const& e) {
        string s = "Could not construct greedy cover instance: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_at(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    PyObject* py_index = NULL;
    static const char* kwlist[] = { "gci", "index", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "OO", (char**)kwlist, &py_gci, &py_index))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        if (PyLong_Check(py_index) && PyIndex_Check(py_index)) {
            auto mset = gci->at(PyLong_AsSize_t(py_index));
            PyObject* elements = create_list_from_size_t_vector(mset.get_elements());
            PyObject* multiplicities = create_list_from_size_t_vector(mset.get_multiplicities());
            PyObject* pp = PyTuple_Pack(2, elements, multiplicities);
            return pp;
        } else {
            throw Exception("Non integer index found.");
        }
    } catch (std::exception const& e) {
        string s = "Could not index element: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_effective_at(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    PyObject* py_index = NULL;
    static const char* kwlist[] = { "gci", "index", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "OO", (char**)kwlist, &py_gci, &py_index))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        if (PyLong_Check(py_index) && PyIndex_Check(py_index)) {
            auto mset = gci->at(PyLong_AsSize_t(py_index));
            PyObject* elements = create_list_from_size_t_vector(mset.get_elements());
            PyObject* leftovers = create_list_from_size_t_vector(mset.get_leftovers());
            PyObject* pp = PyTuple_Pack(2, elements, leftovers);
            return pp;
        } else {
            throw Exception("Non integer index found.");
        }
    } catch (std::exception const& e) {
        string s = "Could not index element: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_size(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return PyLong_FromSize_t(gci->size());
    } catch (std::exception const& e) {
        string s = "Could not get instance size: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_n_elements(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;
    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return PyLong_FromSize_t(gci->n_elements());
    } catch (std::exception const& e) {
        string s = "Could not get instance n elements: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_get_max_coverage(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return create_list_from_size_t_vector(gci->get_max_coverage());
    } catch (std::exception const& e) {
        string s = "Could not get instance max coverage: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_get_leftovers(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return create_list_from_size_t_vector(gci->get_leftovers());
    } catch (std::exception const& e) {
        string s = "Could not get instance leftovers: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_get_multisets_incomplete_cover(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return create_list_from_size_t_vector(gci->get_multisets_incomplete_cover());
    } catch (std::exception const& e) {
        string s = "Could not get instance multisets with incomplete cover: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_add_multiset(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    PyObject* py_elements = NULL;
    PyObject* py_mult = NULL;
    static const char* kwlist[] = { "gci", "elements", "mult", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "OO|O", (char**)kwlist, &py_gci, &py_elements, &py_mult))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        if (py_mult == NULL || py_mult == Py_None)
            gci->add_multiset(create_size_t_vector_from_list(py_elements));
        else
            gci->add_multiset(create_size_t_vector_from_list(py_elements), create_size_t_vector_from_list(py_mult));

        Py_INCREF(Py_None);
        return Py_None;
    } catch (std::exception const& e) {
        string s = "Could not add multiset: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_delete_multiset(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    PyObject* py_index = NULL;
    static const char* kwlist[] = { "gci", "index", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "OO", (char**)kwlist, &py_gci, &py_index))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        if (PyLong_Check(py_index) && PyIndex_Check(py_index))
            gci->delete_multiset(PyLong_AsSize_t(py_index));
        else
            throw Exception("Non integer value found.");

        Py_INCREF(Py_None);
        return Py_None;
    } catch (std::exception const& e) {
        string s = "Could not delete multiset: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_cover(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    PyObject* py_coverage = NULL;
    PyObject* py_max_iters = NULL;
    static const char* kwlist[] = { "gci", "coverage", "max_iters", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "OO|O", (char**)kwlist, &py_gci, &py_coverage, &py_max_iters))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        vector<size_t> solution;

        size_t max_iters;
        if (py_max_iters == NULL || py_max_iters == Py_None)
            max_iters = 0;
        else {
            if (PyLong_Check(py_max_iters))
                max_iters = PyLong_AsSize_t(py_max_iters);
            else
                throw Exception("Non integer value found.");
        }

        if (PyLong_Check(py_coverage)) {
            size_t coverage = PyLong_AsSize_t(py_coverage);
            solution = gci->cover(coverage, max_iters);
        } else {
            auto coverage = create_size_t_vector_from_list(py_coverage);
            solution = gci->cover(coverage, max_iters);
        }

        return create_list_from_size_t_vector(solution);
    } catch (std::exception const& e) {
        string s = "Could not run the cover algorithm: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance_solution(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return create_list_from_size_t_vector(gci->solution);
    } catch (std::exception const& e) {
        string s = "Could not get solution: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance__coverage_until(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return create_list_from_size_t_vector(gci->_coverage_until);
    } catch (std::exception const& e) {
        string s = "Could not get step coverage: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}

PyObject* _GreedyCoverInstance__n_elements_remaining(PyObject* self, PyObject* args, PyObject* keywds)
{
    PyObject* py_gci = NULL;
    static const char* kwlist[] = { "gci", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", (char**)kwlist, &py_gci))
        return NULL;

    try {
        GreedyCoverInstance* gci = decapsule_GreedyCoverInstance(py_gci);
        return create_list_from_size_t_vector(gci->_n_elements_remaining);
    } catch (std::exception const& e) {
        string s = "Could not get n elements remaining: " + string(e.what());
        PyErr_SetString(PyExc_BaseException, s.c_str());
        return NULL;
    }
}
#ifdef __cplusplus
}
#endif