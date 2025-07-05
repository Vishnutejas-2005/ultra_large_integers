# UltraLarge Integers ADT

## Overview
The **UltraLarge Integers** project implements an Abstract Data Type (ADT) in C that provides support for variable-length integers (referred to as "UltraLarge Integers"). These integers overcome the limitations of standard data types in C by allowing operations on numbers of arbitrary size, constrained only by a prespecified maximum length.

## Features
1. **Initialization and Management**
   - Dynamically allocate memory for UltraLarge Integers.
   - Resize memory as needed during operations.

2. **Arithmetic Operations**
   - Addition of two UltraLarge Integers.
   - Subtraction of two UltraLarge Integers.

3. **Comparison**
   - Compare two UltraLarge Integers for equality or relative size.

4. **File-Based Operations**
   - Read target value and integers from a text file.
   - Compute the number of pairs of integers that satisfy a given condition based on the target.

5. **Hashmap Optimization**:
   - Implements a hashmap for storing and retrieving ultralarge integers efficiently.
   - Significantly improves the time complexity for large datasets by avoiding repetitive computations.

6. **Comprehensive Utilities**:
   - Memory management for ultralarge integers.
   - Functions for resizing, assigning, and printing ultralarge integers.

## Project Structure
- **`uint.h`**: Header file defining the UltraLarge Integer structure and function prototypes.
- **`uint.c`**: Implementation of UltraLarge Integer operations.
- **`count_pairs.py`**: Python script showcasing integration with the C library for file-based computations.
- **Makefile**: Build instructions for compiling the project.

## Key Functions
### C Functions
#### UltraLarge Integer Operations
- `void uinteger_init(UInteger *num)`
- `void uinteger_free(UInteger *num)`
- `void uinteger_add(UInteger *result, const UInteger *a, const UInteger *b)`
- `void uinteger_subtract(UInteger *result, const UInteger *a, const UInteger *b)`
- `int uinteger_compare(const UInteger *a, const UInteger *b)`

#### File Handling
- `int open_file(char *filename)`:
  - Reads a file containing a target, number of integers, and the integers themselves.
  - Computes and returns results based on the target value.

### Python Functions
- `count_pairs(data, target)` (naive implementation for testing)
- `count_pairs_file(filename)` (invokes the C library to process file-based data)

## How to Use
### Compilation
1. Ensure you have a C compiler installed.
2. Run the following command to build the project:
   ```bash
   make
   ```

### Running the Program
1. Prepare a text file with the following format:
   ```
   <target>
   <number of integers>
   <integer 1>
   <integer 2>
   ...
   ```
   Example:
   ```
   10
   5
   15
   25
   5
   20
   30
   ```

2. Execute the Python script to call the C library:
   ```bash
   python3 main.py <filename>
   ```

## Example
Given a file `input.txt` with the content:
```
10
5
15
25
5
20
30
```
Running:
```bash
python3 main.py input.txt
```
Will output the number of pairs of integers satisfying the target condition.

## Future Enhancements
- Extend to support multiplication and division.
- Optimize memory usage and improve algorithm efficiency for large datasets.
- Add more extensive testing and benchmarks.


## 👥 Contributors

- [@sashank-810](https://github.com/sashank-810)
- [@skmanoj2006](https://github.com/skmanoj2006)
- [@Vishnutejas-2005](https://github.com/Vishnutejas-2005)

## Contributing
Feel free to fork this repository and submit pull requests. Suggestions, bug reports, and feature requests are welcome.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

