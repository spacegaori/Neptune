# Neptune

Header-only matrix library built with CMake, tested with GoogleTest.

## Description

My goal is to prepare a robust matrix library that will make use of future C++ standard library features like `mdarray`, `mdspan`, `submdspan`, and `std::linalg`. I have been learning a lot by rebuilding `matrix.hpp` from scratch each time with a better understanding and a clearer direction.

I will leave the matrix in its most simple form and focus on creating an appropriate test suite.

## Goals

- Create a basic test suite covering all constructors and methods.
- Understand constructor keywords like `constexpr`, `explicit`, `default`, `noexcept`.
- Understand PMR (Polymorphic Memory Resources) and AA (Allocator Awareness).

## Executing test

> ⚠️ **Make sure to use a compiler with the `<mdspan>` header.**

```
mkdir build && cd build
cmake ..
make
make test
```

### References

[Machine Learning in C](https://youtube.com/playlist?list=PLpM-Dvs8t0VZPZKggcql-MmjaBdZKeDMw&si=dW-US0T3M2LF6xOO)

[micrograd](https://youtu.be/VMj-3S1tku0?si=GI7DL3ghyKl25IKf)

[tinygrad](https://youtu.be/Xtws3-Pk69o?si=GedGe5IxK9zErTbb)

[Getting Allocators out of Our Way](https://youtu.be/RLezJuqNcEQ?si=C6eabvCggDyrfURy)
