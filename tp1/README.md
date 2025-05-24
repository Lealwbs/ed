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
1 100.0 0.01 -0.005 0.02 100
5 31 65 96 6 595 652 26 262 21 21 548 1 2 948 4 1 15 165 15 184 81 515 151 2 1 213 3 231 313 131 31 318 41 515 48 6 6 16 19 19 19 91 48 86 86 14 9 76 43 23 64 3 2 3 6 4 7 74 5 6 16 42 85 75 3 46 59 5 84 1 6 15 464 4 51 516 151 65 1 15 15 15 15 65 2 65 1 651 848 2 8 4 2 12 65 78 44 23 56
```
- `1`: Seed
- `100.0`: Cost threshold
- `0.01`, `-0.005`, `0.02`: Coefficients for cost calculation
- `100`: Array size
- Next 100 numbers: Array elements

## Output Example
```
size 100 seed 1 breaks 41

iter 0
mps 2 cost 7.585000000 cmp 767 move 609 calls 148
mps 21 cost 4.255000000 cmp 731 move 699 calls 22
mps 40 cost 5.355000000 cmp 1052 move 1073 calls 10
mps 59 cost 6.105000000 cmp 1279 move 1353 calls 4
mps 78 cost 6.105000000 cmp 1279 move 1353 calls 4
mps 97 cost 6.105000000 cmp 1279 move 1353 calls 4
nummps 6 limParticao 21 mpsdiff 2.230000

iter 0
qs lq 1 cost 3.260000000 cmp 391 move 218 calls 22
in lq 1 cost 0.410000000 cmp 177 move 276 calls 1
qs lq 10 cost 3.650000000 cmp 486 move 330 calls 22
in lq 10 cost 4.430000000 cmp 981 move 1080 calls 1
qs lq 19 cost 4.290000000 cmp 558 move 358 calls 25
in lq 19 cost 6.850000000 cmp 1465 move 1564 calls 1
qs lq 28 cost 3.210000000 cmp 536 move 482 calls 13
in lq 28 cost 7.805000000 cmp 1656 move 1755 calls 1
qs lq 37 cost 3.450000000 cmp 580 move 534 calls 16
in lq 37 cost 8.530000000 cmp 1801 move 1900 calls 1
qs lq 46 cost 4.170000000 cmp 618 move 502 calls 25
in lq 46 cost 8.775000000 cmp 1850 move 1949 calls 1
numlq 6 limQuebras 10 lqdiff 6.440000
```

## Customization
- Change sorting algorithm or parameters in `main.cpp`.
- Add new algorithms in `sorting_algorithms.cpp` and update headers.
- Adjust statistics logic in `stats.cpp` as needed.

## Documentation
- See `files/TP1 Enunciado.pdf` for the project description.
- Example documentation and reports are in `TP1_Documentacao.pdf`.

## Authors
- Ítalo Leal Lana Santos

## License
This project is for educational use. See documentation for details.
