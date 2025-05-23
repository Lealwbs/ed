# TP1 - Sorting Algorithms Project

## Overview
This project implements and analyzes various sorting algorithms in C++. It is designed for educational purposes, focusing on algorithm efficiency, cost analysis, and the impact of different parameters on sorting performance. The project reads input data from files, applies sorting algorithms, and outputs relevant statistics.

## Project Structure

- **src/**: Contains the main source code files.
  - `main.cpp`: Entry point. Handles input, initializes data, and runs sorting routines.
  - `ordenador.cpp` / `ordenador.hpp`: Implements the `Ordenador` class, which manages sorting and related operations.
  - `sorting_algorithms.cpp` / `sorting_algorithms.hpp`: Implements various sorting algorithms (e.g., QuickSort, InsertionSort) and statistics tracking.
  - `vector_manager.cpp` / `vector_manager.hpp`: Manages vector initialization and utility functions.
  - `stats.cpp` / `stats.hpp`: Handles statistics collection and reporting for sorting operations.
- **include/**: Header files for all classes and utilities.
- **bin/**: Compiled executables.
- **files/**: Contains input files, documentation, and test cases.
- **makefile**: For building the project.

## How It Works

1. **Input**: The program expects an input file with the following format:
   - `seed limiarCusto a b c tamanhoArray` (parameters for randomization, cost limits, and coefficients)
   - Followed by `tamanhoArray` integers (the array to be sorted)
2. **Initialization**:
   - Reads parameters and array from the file.
   - Initializes two arrays: one for sorting, one as a backup.
3. **Sorting**:
   - Sets up the sorting algorithm and statistics parameters.
   - Calculates the number of breaks (discontinuities) in the array.
   - Determines partition and break thresholds using custom logic.
   - Runs QuickSort (or other algorithms as needed).
4. **Statistics**:
   - Tracks comparisons, movements, and recursive calls.
   - Uses coefficients `a`, `b`, and `c` to compute a cost function.
   - Outputs statistics and results to the console.
5. **Cleanup**:
   - Closes files and deallocates memory.

## Main Components

- **Ordenador**: Central class for managing sorting and threshold logic.
- **SortingAlgorithms**: Static class for sorting routines and statistics.
- **Stats**: Tracks and prints statistics for each sorting run.
- **VectorManager**: Handles vector initialization and randomization.

## Compilation and Usage

1. **Compile**:
   ```bash
   make
   ```
   or manually:
   ```bash
   g++ -Iinclude -o bin/tp1.out src/*.cpp
   ```
2. **Run**:
   ```bash
   ./bin/tp1.out files/tests/teste1.txt
   ```
   Replace `teste1.txt` with your input file.

## Input File Example
```
1 100.0 0.01 -0.005 0.02 10
5 3 8 6 2 9 1 7 4 0
```
- `1`: Seed
- `100.0`: Cost threshold
- `0.01`, `-0.005`, `0.02`: Coefficients for cost calculation
- `10`: Array size
- Next 10 numbers: Array elements

## Output Example
```
size 10 seed 1 breaks 5
```

## Customization
- Change sorting algorithm or parameters in `main.cpp`.
- Add new algorithms in `sorting_algorithms.cpp` and update headers.
- Adjust statistics logic in `stats.cpp` as needed.

## Documentation
- See `files/TP1 Enunciado.pdf` for the project description.
- Example documentation and reports are in `files/Exemplo Documentação/`.

## Authors
- Ítalo Leal Lana Santos

## License
This project is for educational use. See documentation for details.
