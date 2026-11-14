# ALGORITHM-EXPLORER
Design&amp;Analysis of Algorithms


# Algorithm Explorer

An educational full-stack application built to demonstrate manual data structures, recursive sorting algorithms, complexity metric tracking, and low-level systems programming interfaced through a modern web UI.

## Project Structure
- `datastructures.h` & `datastructures.c`: Custom pointer-based node stacks, queues, and execution metrics tracking.
- `sorting.h` & `sorting.c`: Modular implementation of recursive Merge Sort.
- `main.c`: CLI driver parsing arguments and formatting output metrics.
- `app.py`: Python Flask server bridging the compiled C binary with an interactive web dashboard.

## Getting Started & Compilation Instructions

1. **Compile the C Backend:**
   ```bash
   gcc -O2 main.c datastructures.c sorting.c -o algorithm_explorer