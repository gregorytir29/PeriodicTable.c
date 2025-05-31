# PeriodicTable.c

## 🧪 Periodic Table CLI Application

This is a command-line application written in C that displays and interacts with the Periodic Table of Elements using data loaded from a CSV file. It was built as part of an individual project for a university-level Programming I course.

### 🛠️ Implementation Overview

Instead of hardcoding the periodic table manually into 2D arrays, I chose to implement a more flexible and scalable approach using a `typedef struct` to store each element's properties (such as name, symbol, group, atomic number, etc.), populated via CSV parsing.

The CSV file used was sourced from a reputable U.S. chemistry data repository and is read using the custom `readCSV()` function, which uses `fgets()` and `strtok()` for line-by-line tokenization and data extraction.

After data is loaded, the program branches into multiple function-specific screens (e.g. `F1()`, `F2()`, etc.), each of which handles different kinds of interaction:

- **F1**: Welcome screen, displayed at the start and end of the program.
- **F2, F3**: Element search by name or symbol using a basic linear search.
- **F4**: Group search functionality that allows searching by chemical group or family, with color-highlighted results in the full periodic table view.
- **F5, F6**: Additional screens handling extended interactions and filtering.

### 🧼 Input Handling & Terminal Output

Each input screen includes robust input validation and error messages in case of invalid entries. Input buffers are cleared using utility functions to prevent overflow or invalid parsing.

The program also includes a `printheader()` function to clear the terminal (supporting both Windows and UNIX-like systems) and print a consistent header (e.g. "Periodic Table of Elements") at the top of each view.

Search filtering is handled by a combination of functions such as `stringsearch()`, `isitred()`, and `printperiodic()`, which highlights matching elements in red using ANSI escape codes.

### ❗ Input Validation

- In single-element searches (F2/F3), the program requests re-entry immediately if the input is invalid.
- In group searches (F4), the input process restarts entirely if the criteria are incorrect.

### 📷 Sample Outputs

Screenshots of various views are available in the repository, including:
- Full periodic table layout
- Search-by-name and search-by-symbol results
- Group search with color highlights
- Final screen from VSCode (since `.exe` auto-closes)

---

✅ This project demonstrates practical use of file parsing, structured data in C, terminal-based UI control, and modular programming.

