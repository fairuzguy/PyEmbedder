#include <iostream>
#include "pyhelper.h"

using namespace std;

int main()
{
    /// Method 1: Calling a whole python script (not very interactive, hard to access python memory)
    {
        char filename[] = "hellocobra.py";  /// file we are opening (.py)
        FILE* fp;                           /// file pointer, lets python access memory address

        Py_Initialize();                    /// Calling python interpreter
        /// _______________________ PYTHON CODE (can still use C++ here) ____________________________ ///

        fp = _Py_fopen(filename, "r");      /// python interpreter opens file (.py)
        PyRun_SimpleFile(fp, filename);     /// reads file, compiles-->runs program

        /// _________________________________________________________________________________________ ///
        Py_Finalize();                      /// Destroying python interpreter
    }
    cout << "Method one complete.\n" << endl;



    /// Method 2: Calling individual strings, referencing PyObjects
    {
        CPyInstance pyInstance;             /// Calling python interpreter

        PyRun_SimpleString("print('Hellow World from Embedded Python!!!')");

        CPyObject p;                        /// creating a python object 'p'
        p = PyLong_FromLong(50);            /// setting p as a 'long' type, giving it a value of 50
        cout << PyLong_AsLong(p) << endl;   /// output the value of p. See how we can use the same variable across python and C++?
    }                                       /// Automatically destroys interpreter at this point (out of scope)
    cout << "Method two complete.\n" << endl;



    /// Method 3: Whole bunch of stuff -> importing modules and calling individual functions (big leagues)
    {
        CPyInstance hInstance;
        CPyObject sysPath = PySys_GetObject((char*)"path");
        PyList_Append(sysPath, PyUnicode_FromString("."));

        CPyObject pName = PyUnicode_FromString("testmodule"); /// name of module for import
        CPyObject pModule = PyImport_Import(pName); /// importing python module

        if(pModule) /// checks if the module exists/imported correctly
        {
            CPyObject pFunc = PyObject_GetAttrString(pModule, "getInteger"); /// reference to python function to call it
            if (pFunc && PyCallable_Check(pFunc)) /// checks if the function exists and can be called
            {
                CPyObject pValue = PyObject_CallObject(pFunc, NULL); /// calls function, returns to C++ python object (need to know the type)
                cout << "getInteger() = " << PyLong_AsLong(pValue) << endl; /// printing the returned value from python function (need to know the type)
            }
            else
            {
                cout << "ERROR: Function 'getInteger()' could not be found or could not be run." << endl;
            }
        }
        else
        {
            cout << "ERROR: Module 'testmodule' could not be imported." << endl;
        }

    }
    cout << "Method 3 complete.\n" << endl;

    return 0;
}
