# Graph Algorithms

This C++ project implements several graph algorithms on directed graphs, including cycle detection, strongly connected components, topological sorting, and finding the maximum “hype” path. The project demonstrates object-oriented design and algorithmic approaches for graph-based problems.

## Features

- **Cycle Detection:** Check if the directed graph has a cycle.
- **Strongly Connected Components (SCC):** Find the number and maximum size of SCCs.
- **Topological Sort:** Output a valid topological order of nodes (if possible).
- **Maximum Hype Path:** Compute the path with the maximum accumulated hype score, accounting for SCCs.

## How to Run

1. **Compile the code:**
   ```sh
   g++ -o graph_algorithms code.cpp
   ```

2. **Run the program:**
   ```sh
   ./graph_algorithms
   ```

## Input Format

When you run the program, provide input in the following order:

1. **Two integers:**  
   - `N`: Number of nodes (events)  
   - `M`: Number of directed edges  

2. **Node data:**  
   - `N` integers: Hype score for each node (space separated, 0-based indexing in code, but edges use 1-based indices)

3. **Edge data:**  
   - `M` lines, each with two integers `u v` (edge from `u` to `v`, both 1-based indices)

4. **Queries:**  
   - An integer `Q`: Number of queries  
   - For each query, an integer specifying the query type:
     - `1` → Cycle detection (`YES`/`NO`)
     - `2` → Print number and max size of SCCs
     - `3` → Print a valid topological order, or `NO` if not possible
     - `4` (or any other number) → Print the maximum possible hype path

## Example Input

```
5 6
10 20 30 40 50
1 2
2 3
3 4
4 5
2 4
4 2
3
1
2
4
```

## Example Output

```
YES
2 3
120
```
