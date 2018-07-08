# One-Dimensional Cellular Automaton

## Project description
This project was made in April 2017 as part of one of my university courses. It is an implementation of a one-dimensional cellular automaton (1dCA), with cells representing two states full and empty implemented as 1 and 0, respectively.
The first and last cells are always empty. The remaining cells are randomly seeded 1 or 0.

The values in the cells change over time. Each cell's value at the next time interval depends on its current value and the value of its two immediate neighbors.
The cell update rule is the following:

- (1) If the current cell is empty, and one of the two adjacent cells is full (but not both), then set the current cell to be full.
- (2) Otherwise, set the current cell to be empty.

By iterating through all current cells, the next "generation" of cells is created. 2 arrays store the data, because we cannot modify one generation until the next
generation is computed. 
Successive generations are printed to the screen by substitute characters:
"." for 0s and "*" for 1s. 

The program takes three command line arguments: 
- (1) A character "a" or "p" to indicate the type of execution (either array operations or pointer arithmetic)
- (2) The number of cells in the 1dCA
- (3) The number of generations to compute. 

If the number of arguments is incorrect, a "Usage" message is displayed before exiting.

In the program 2 separate implementations of the update function are created:
- (1) only using array operations
- (2) only using pointer arithmetic

The function to execute is deterimend by the "a" or "p" command line argument.
Only the update functions differ. The rest of the code-base is the same, otherwise.

Dynamic memory allocation is used to create the arrays we need to hold the 1dCA data, since we do not know the size of the arrays in advance.

A memory leak checker provided by memcheck.h and memcheck.c was supplied by my lecturer to help identify memory leaks.
