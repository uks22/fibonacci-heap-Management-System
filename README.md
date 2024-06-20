# Fibonacci Heap Memory Allocation System

## Overview

This C program implements a memory allocation system using a Fibonacci heap approach. The program manages memory blocks efficiently by utilizing Fibonacci numbers to maintain free and allocated memory lists thus manages malloc() and free() near to O(1) Time Complexity. Here's a breakdown of how the system works and its key functionalities:

## Files and Structures

- **File**: main.c
- **Structures**:
  - `struct node`: Represents a memory block with start and end addresses, and a pointer to the next block.
  - `struct heap`: Contains arrays for Fibonacci numbers, free lists (`fibnode`), and allocated lists (`allocnode`).

## Implemented Functions

1. **initialize_heap()**: Initializes the heap by calculating Fibonacci numbers up to a specified size. Sets up free lists and allocated lists accordingly.

2. **deleteheap(int n)**: Deallocates memory used by Fibonacci numbers, free lists, and allocated lists when the program exits.

3. **_malloc_(int size, int n)**: Allocates memory of a specified size using Fibonacci heap principles. Finds a suitable free block and updates lists accordingly.

4. **merge_free(int n)**: Merges adjacent free blocks in the free lists to optimize memory usage.

5. **_free_(int loc, int n)**: Frees up allocated memory at a specified location, adding it back to the free lists and merging adjacent free blocks.

6. **displayAllocatedlist(int n)**: Displays the current state of allocated memory blocks for each Fibonacci number size.

7. **displayfreelist(int n)**: Displays the current state of free memory blocks for each Fibonacci number size.

## Example Execution

- The program initializes with a specified size of the heap.
- It demonstrates allocating memory blocks of different sizes.
- It shows freeing allocated memory blocks and merging adjacent free blocks.
- Displays the state of free and allocated memory lists after each operation.

## Data Structures Used

- **Arrays of Linked Lists**: Used to manage free (`fibnode`) and allocated (`allocnode`) memory blocks based on sizes defined by Fibonacci numbers.
- **Structures**: Represent memory blocks with start and end addresses, facilitating efficient memory management operations.

## Integration and Usage

- Users interact with the system through `malloc` and `free`-like functions, which operate in near-constant time due to the efficient management of free lists using Fibonacci heap principles.
- The system ensures optimal memory usage by merging adjacent free blocks and efficiently allocating new blocks based on Fibonacci number sizes.

---

This markdown file provides an overview of the Fibonacci heap-based memory allocation system implemented in C, highlighting its design, functionalities, and usage scenarios.
