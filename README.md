```markdown
# SquareMat Matrix Library

`SquareMat` is a C++ library for working with square matrices. It supports a wide range of operations including addition, multiplication, determinant, transpose, and more, all with operator overloading.

## 📁 Project Structure

```

MatrixProject/
├── include/
│   └── SquareMat.hpp         # Header file with class definition
│   └── doctest.h             # Doctest framework header
├── main/
│   └── Main.cpp              # Example usage file
├── src/
│   └── SquareMat.cpp         # Implementation file
├── test/
│   └── test_SquareMat.cpp    # Unit tests using doctest
├── Makefile                  # Makefile for compilation
└── README.md                 # This documentation file

````

## 🛠️ Building & Running
````
### Run memory checks with valgrind:
```bash
make test       # Compiles and runs the tests
```

### Run memory checks with valgrind:

```bash
make valgrind    # Checks for memory leaks
```

### Compile and run main example:

```bash
make Main        # Compiles and run the main
```

## 🧪 Tests

Tests are written using [doctest](https://github.com/doctest/doctest) and cover:

* Constructors and access
* Matrix addition and subtraction
* Scalar and matrix multiplication
* Negation (`-`) and transpose (`~`)
* Determinant calculation (`!`)
* Comparison operators (`==`, `<`, `>`, etc.)
* Compound assignment (`+=`, `*=`, etc.)
* Edge cases and exception handling

## ⚙️ Implementation Notes

* Matrices are zero-initialized upon creation.
* Accessing out-of-bounds indices throws `std::out_of_range`.
* Invalid matrix sizes (e.g., negative or zero) throw `std::invalid_argument`.
* Memory is manually managed using `new`/`delete`, and verified using Valgrind.


## ✍️ Author

Or Bibi
📧 [orbibiariel@gmail.com](mailto:orbibiariel@gmail.com)


