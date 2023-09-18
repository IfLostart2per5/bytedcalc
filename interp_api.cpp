#define PY_SSIZE_T_CLEAN
#define ALLOW_AUTOINC_AS_OPTIONAL
#include <python3.11/Python.h>
#include "./interpreter.cpp"

static PyObject* pyinterpret(PyObject* self,PyObject*  args) {
  PyObject* valores;
  PyObject* instrucoes;
  PyObject* autoinc = Py_True;

  if (!PyArg_ParseTuple(args, "OO|O", &valores, &instrucoes,&autoinc))
    return NULL;

  if (!PyList_Check(valores) || !PyList_Check(instrucoes)) {
    PyErr_SetString(PyExc_TypeError, "Os valores e/ou instruções devem ser listas!");
    return NULL;
  }

  if (!PyBool_Check(autoinc)) {
    PyErr_SetString(PyExc_TypeError, "A flag de auto incremento/decremento do indice interno deve ser booleana!");
    return NULL;
  }

  Py_ssize_t tamanho1 = PyList_Size(valores);
  Py_ssize_t tamanho2 = PyList_Size(instrucoes);

  int instrucoes_[tamanho2];
  int valores_[tamanho1];

  for (Py_ssize_t i = 0; i < tamanho1; i++) {
    valores_[i] = PyLong_AsLong(PyList_GetItem(valores, i));
  }

  for (Py_ssize_t i = 0; i < tamanho2; i++) {
    instrucoes_[i] = PyLong_AsLong(PyList_GetItem(instrucoes, i));
  }

  std::vector<int> result;

  try {
    if (Py_IsTrue(autoinc)) {
  result = interpret(valores_, (int) tamanho1, instrucoes_, (int) tamanho2);
    }
    else {
      result = interpret(valores_,(int) tamanho1, instrucoes_, (int) tamanho2, false);
    }
  } catch (const char* e) {
    PyErr_SetString(PyExc_ValueError, "Erro: indices da pilha fora de intervalo");
    return NULL;
  };


  PyObject* lista = PyList_New(0);

  if (lista == NULL) {
    Py_DECREF(lista);
    PyErr_SetString(PyExc_ValueError, "Erro ao alocar a lista");
    return NULL;
  }

  for (int i = 0; i < result.size(); i++) {
    PyObject* valor = PyLong_FromLong(result[i]);

    if (valor == NULL) {
      Py_DECREF(valor);
      PyErr_SetString(PyExc_RuntimeError, "Erro na geração dos valores.");
      return NULL;
    }

    int r = PyList_Append(lista, valor);

    if (r == -1) {
      Py_DECREF(valor);
      PyErr_SetString(PyExc_RuntimeError, "Erro na criação da lista");
      return NULL;
    }
  }

  return lista;
}

static struct PyMethodDef methods[] = {
  {"interpret", pyinterpret,METH_VARARGS, "Interpreta bytecode de calculadora"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef modulo = {
  PyModuleDef_HEAD_INIT,
  "interp",
  "Python wrapper for interpret c++ function",
  -1,
  methods
};

PyMODINIT_FUNC PyInit_interp(void) {
  return PyModule_Create(&modulo);
}
