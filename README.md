## CortexC Simple C Interpreter

This repository contains a simple interpreter for a subset of the C language, written in C itself. It includes a tokenizer, a parser, and an evaluator for assembly instructions.


## Overview 
The interpreter is divided into several parts:

*  Definitions and Enumerations: The code starts with the definition of several constants and structures that are used throughout the program. It also defines a number of enumerations that represent different types of tokens that can be encountered in the input code.

* Tokenization: The next() function is responsible for tokenizing the input code. It reads characters from the input and classifies them into different types of tokens.

* Expression Parsing: The expr() and factor() functions are used for parsing expressions in the input code. However, these functions are not fully implemented in the provided code.

* Program Parsing: The program() function is responsible for parsing the entire program. It repeatedly calls the next() function to get tokens and processes them accordingly.

* Evaluation: The eval() function is an interpreter for the assembly instructions. It reads and executes the instructions one by one.

* Main Function: The main() function is the entry point of the program. It initializes the necessary data structures, reads the input code from a file, calls the program() function to parse the code, and finally calls the eval() function to execute the parsed code.

## Usage

To use the interpreter, you need to have a C compiler installed on your system. You can compile the interpreter itself using the following command:

```c
clang interpreter.c -o interpreter
```
Then, you can use the compiled interpreter to interpret and run a C program as follows:

```bash
zig build
```

Please note that the interpreter is quite simple and may not support all features of the C language. Also, the code seems to be incomplete and may not work correctly as is. For example, the expr() and factor() functions are not fully implemented.

## Contributing 

Contributions are welcome! If you find a bug or want to add a new feature, feel free to create a pull request.
