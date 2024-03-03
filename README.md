<p align="center">
  <img src="https://github.com/alvarorichard/CortexC/assets/102667323/002eab8a-29ac-435f-a792-e58067ba79e0" alt="Imagem logo" />
</p>

## Simple C Interpreter

[![GitHub license](https://img.shields.io/github/license/alvarorichard/CortexC)](alvarorichard/CortexC/blob/master/LICENSE)
![GitHub stars](https://img.shields.io/github/stars/alvarorichard/CortexC)
![GitHub languages top](https://img.shields.io/github/languages/top/alvarorichard/CortexC)
[![GitHub contributors](https://img.shields.io/github/contributors/alvarorichard/CortexC)](https://github.com/alvarorichard/CortexC/graphs/contributors)
[![CI](https://github.com/vitorcarvalho67/TSLibraryAPI/workflows/CI/badge.svg)](https://github.com/alvarorichard/CortexC/actions)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/alvarorichard/CortexC)](https://github.com/alvarorichard/CortexC/commit/main)
![GitHub last commit](https://img.shields.io/github/last-commit/alvarorichard/CortexC)

This repository contains a simple interpreter for a subset of the C language, written in C itself. It includes a tokenizer, a parser, and an evaluator for assembly instructions. The interpreter is capable of interpreting and running simple C programs, but it does not support all features of the C language.

## Overview 
The interpreter is divided into several parts:

* Definitions and Enumerations: The code starts with the definition of several constants and structures that are used throughout the program. It also defines a number of enumerations that represent different types of tokens that can be encountered in the input code.

* Tokenization: The next() function is responsible for tokenizing the input code. It reads characters from the input and classifies them into different types of tokens.

* Expression Parsing: The expr() and factor() functions are used for parsing expressions in the input code. However, these functions are not fully implemented in the provided code.

* Program Parsing: The program() function is responsible for parsing the entire program. It repeatedly calls the next() function to get tokens and processes them accordingly.

* Evaluation: The eval() function is an interpreter for the assembly instructions. It reads and executes the instructions one by one.

* Main Function: The main() function is the entry point of the program. It initializes the necessary data structures, reads the input code from a file, calls the program() function to parse the code, and finally calls the eval() function to execute the parsed code.

## How to use the interpreter

To use the interpreter, you need to have a C compiler installed on your system. You can compile the interpreter itself using the following command:

Clone this repository and compile the interpreter using the following command:
```bash
git clone https://github.com/alvarorichard/CortexC.git
```

Navigate to the directory containing the source code:
```bash
cd CortexC
```

Compile the source code using the following command:
```bash
clang main.c -lfunction_parameter -o main
```

Then, you can use the compiled interpreter to interpret and run a C program as follows:
```bash
zig build
```

Please note that the interpreter is quite simple and may not support all features of the C language. Also, the code seems to be incomplete and may not work correctly as is. For example, the expr() and factor() functions are not fully implemented.

## Contributing

Contributions are welcome! If you find a bug or want to add a new feature, feel free to create a pull request.
