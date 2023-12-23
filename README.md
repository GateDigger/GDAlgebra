# GDAlgebra
is a tiny computer algebra project (which I decided to learn C++ on).

## Overview
At this point, the only notable implement is the univariate_polynomial.hpp container template. The template is written directly on pointer arithmetic and allows to specify
  - base coefficient type
  - degree type
  - leading zeroes trim mode

Currently implemented functionality includes:
  - evaluation according to Horner's scheme
  - access to coefficients through subscript
    - bound-checked for consts
    - unchecked for non-consts
  - destructive add, sub
  - destructive mul, div by a constant
  - lightweight to_string conversion
  - mul/div by x^n as shifts
  - add, sub
  - mul by a constant
  - schoolbook mul
  - Karatsuba's mul
  - div_mod
  - equality / nonequality operators

The intent is to allow operations between containers of different coefficient types and different trim modes, if they are compatible. algebraic_type_closures.hpp is an attempt to facilitate the type compatibility.

## TODO
  - GCD
  - Square-free factorization
  - Numerical root searching for pseudo-dense coefficient types
  - Toom-Cook ?
  - FFT multiplication ?
  - ...
  - Proper unit tests

## Disclaimer
I am relatively new to C++ and this is long-term, not very thoroughly tested work in progress.

## License

MIT License

Copyright (c) 2023 GateDigger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
