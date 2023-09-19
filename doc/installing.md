# Installing
To install, just clone this repository with:
```sh
git clone https://www.github.com/IfLostart2per5/bytedcalc
```
Ensure that you have a C++ compiler, because the interpreter core is made in C++.

Now, run:
```sh
cd bytedcalc
# or python/py on windows
python3 setup.py build_ext --inplace
```

It will make you be able to test the interpreter with python (aih).

### OR

just use it normally in C++:

```cpp
// util for less verbosity
#define ALLOW_AUTOINC_AS_OPTIONAL
#include "./interpreter.cpp"

int main() {
  // you have to use traditional arrays
  int values[] = {1, 3, 5};
  int values_size = 3;
  int instructions[] = {1, 1, 1, 7, 3, 8, 3, 0};
  int instructions_size = 8;

  //its already included in interpreter.cpp
  std::vector<int> result = interpret(values, values_size, instructions, instructions_size);

  std::cout << result[0] << std::endl;
  return 0;
}
```

You decides the way that you wanna test, compile as a python extension, or uses the C++ way directly ;)

References:
1. [Structure of the interpreter](./README.md)
2. [Instructions](./instructions.md)

