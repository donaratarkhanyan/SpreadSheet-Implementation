# SpreadSheet

This is a C++ implementation of a Spreadsheet. It allows users to create, modify, and display cells in a spreadsheet grid, supporting various data types and formulas.

## Features

- Create a spreadsheet with dynamic rows and columns.
- Store different data types (e.g., strings, integers, floats).
- Support basic mathematical operations.
- Load and save spreadsheet data to/from a file.
- Add, edit, and delete cells.
- Display the spreadsheet in a tabular format.
- Implement cell referencing and formula evaluation.

## Installation

### Prerequisites

- C++11 or higher
- CMake (optional, for building)
- A C++ compiler like `g++` or `clang++`

### Steps

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/spreadsheet.git
    ```

2. Navigate to the project directory:

    ```bash
    cd spreadsheet
    ```

3. Compile the project:

    ```bash
    g++ -std=c++11 -o spreadsheet main.cpp
    ```

4. Run the application:

    ```bash
    ./spreadsheet
    ```

## Usage

After running the application, you can perform the following operations:

1. **Create a new spreadsheet**:
   - Specify the number of rows and columns.
  
2. **Add or edit cell data**:
   - Enter values in any cell, supporting integers, floats, or strings.

3. **Display the spreadsheet**:
   - The entire spreadsheet grid can be displayed in a formatted table.

4. **Save and load**:
   - Save your spreadsheet to a file for later use or load an existing spreadsheet.

5. **Evaluate formulas**:
   - Cells can contain basic formulas (e.g., `=A1 + B2`).

### Example

```plaintext
+----+----+----+
| A  | B  | C  |
+----+----+----+
| 10 | 20 |    |
+----+----+----+
|    | 30 | 40 |
+----+----+----+
