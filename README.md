# NIST Statistical Test Suite (nist-sts)

A portable, self-contained implementation of the NIST Statistical Test Suite for Random and Pseudorandom Number Generators for Cryptographic Applications. 

This repository provides a robust toolkit to evaluate the randomness of bit sequences. It is designed with portability and ease of integration in mind, avoiding external mathematical dependencies to ensure smooth cross-platform compatibility.

## 🚀 Features

* **Self-Contained Architecture:** Designed to be highly portable with zero external dependency bloat. 
* **Built-in Mathematical Operations:** Includes a custom implementation of the Cooley-Tukey Radix-2 Fast Fourier Transform (FFT) algorithm, enabling efficient processing of bit sequences natively.
* **Standardized Testing:** Evaluates the randomness of sequences following the guidelines established by the National Institute of Standards and Technology (NIST).

## 🛠️ Prerequisites

Since the project is entirely self-contained, the requirements to build and run the suite are minimal:

* A modern C/C++ compiler (GCC, Clang, or MSVC)
* CMake (version 3.10 or higher recommended)
* Git

## 📦 Building the Project

You can build the project using CMake. Follow these standard steps from the root of the repository:

```bash
# Clone the repository
git clone [https://github.com/jagranados-dev/nist-sts.git](https://github.com/jagranados-dev/nist-sts.git)
cd nist-sts

# Create a build directory
mkdir build && cd build

# Configure and compile
cmake ..
cmake --build .
```

## 💻 Usage

(Note: Update this section with specific command-line arguments or code integration examples once the repository overhaul is complete.)

By default, the suite processes an input bit sequence and outputs the P-values for the executed statistical tests, indicating whether the sequence can be considered random.

## 🤝 Contributing

Contributions are welcome! If you would like to improve the performance, add support for more tests, or fix a bug, please feel free to open an issue or submit a Pull Request.

- Fork the Project

- Create your Feature Branch (git checkout -b feature/AmazingFeature)

- Commit your Changes (git commit -m 'Add some AmazingFeature')

- Push to the Branch (git push origin feature/AmazingFeature)

- Open a Pull Request

## 📄 License

This project is distributed under the MIT License. See LICENSE for more information.