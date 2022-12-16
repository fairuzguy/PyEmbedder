/** Python 'Helper' Class
    Credit goes to 'arnavguddu' from codeproject.com for providing a tutorial, address below:
    https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code.
    This code is slightly modified, you can compare to the .hpp file supplied in the tutorial.
**/

#ifndef PYHELPER_H
#define PYHELPER_H
#pragma once

#include <Python.h>

class CPyInstance
{
public:
    CPyInstance()
    {
        Py_Initialize();
    }

    ~CPyInstance()
    {
        Py_Finalize();
    }
};


class CPyObject
{
private:
    PyObject *p;

public:
    /// Main constructors
    CPyObject() : p(NULL)
    {

    }
    CPyObject(PyObject* _p) : p(_p)
    {

    }

    /// Destructor (called automatically)
    ~CPyObject()
    {
        Release();
    }

    /// ___________________________ Functions _____________________________ ///
    /// Getter
    PyObject* getObject()
    {
        return p;
    }

    /// Setter
    PyObject* setObject(PyObject* _p)
    {
        return(p=_p);
    }

    /// Increasing reference call (can be used more often)
    PyObject* AddRef()
    {
        if(p)
        {
            Py_INCREF(p);
        }
        return(p);
    }

    /// Releases pointer p
    void Release()
    {
        if(p)
        {
            Py_DECREF(p);
        }
        p = NULL;
    }

    /// Operator object
    PyObject* operator ->()
    {
        return p;
    }

    /// Existence check
    bool is()
    {
        return p ? true : false;
    }

    /// I don't know what this means...
    operator PyObject*()
    {
        return p; /// perhaps this is an analog to the operator object?
    }

    /// Setting the operator object
    PyObject* operator = (PyObject* pp)
    {
        p = pp;
        return p;
    }

    /// again, why?
    operator bool()
    {
        return p ? true : false;
    }
};


#endif // PYHELPER_H
