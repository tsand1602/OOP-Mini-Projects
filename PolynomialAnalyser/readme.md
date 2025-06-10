# Polynomial Analyser

This C++ project provides functionality to work with polynomials. It supports polynomial creation, arithmetic operations (addition, subtraction, multiplication), evaluation at a given value, and printing of polynomial expressions.

## Features

- **Polynomial Construction:**  
  - Create polynomials by specifying degree and coefficients.
- **Arithmetic Operations:**  
  - Addition, subtraction, and multiplication of polynomials.
- **Evaluation:**  
  - Evaluate a polynomial at a given value.
- **Printing:**  
  - Print polynomial expressions in a readable format.

## How to Run

1. **Compile the code:**
   ```sh
   g++ -o polynomial_analyser code.cpp
   ```

2. **Run the program:**
   ```sh
   ./polynomial_analyser
   ```

## Input Format

The program operates interactively with the following commands (one per line):

- `Polynomial <name>`  
  - Enter the degree of the polynomial.
  - Enter the coefficients from highest to lowest degree.
- `add <name1> <name2> <result_name>`  
  - Adds two polynomials and stores the result.
- `subtract <name1> <name2> <result_name>`  
  - Subtracts the second polynomial from the first and stores the result.
- `multiply <name1> <name2> <result_name>`  
  - Multiplies two polynomials and stores the result.
- `evaluate <name> <value>`  
  - Evaluates the polynomial at the given value.
- `print <name>`  
  - Prints the polynomial expression.
- `end`  
  - Terminates the program.

## Example Session

```
Polynomial P
2
1 0 -3
Polynomial Q
1
2 4
add P Q R
print R
evaluate R 2
end
```
