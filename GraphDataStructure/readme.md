# Graph Data Structure

This C++ project implements an undirected graph data structure supporting graph set operations and basic queries. It provides operator overloading for union, intersection, and complement, and supports edge manipulation and reachability queries.

## Features

- **Graph Construction:** Create graphs by specifying vertices and edges.
- **Set Operations:**  
  - Union  
  - Intersection  
  - Complement
- **Edge Manipulation:**  
  - Add or remove edges interactively.
- **Reachability Query:**  
  - Check if one vertex is reachable from another.
- **Graph Printing:**  
  - Print adjacency lists.

## How to Run

1. **Compile the code:**
   ```sh
   g++ -o graph_ds code.cpp
   ```

2. **Run the program:**
   ```sh
   ./graph_ds
   ```

## Input Format

The program operates interactively with the following commands (one per line):

- `Graph`  
  - Enter: `n e` (`n`: number of vertices, `e`: number of edges)
  - Then enter `e` lines: `u v` (edge between `u` and `v`, 0-based indexing)
- `union <any_string>`  
  - Input another graph as above; computes union with the current graph.
- `intersection <any_string>`  
  - Input another graph as above; computes intersection with the current graph.
- `complement`  
  - Replaces the current graph with its complement.
- `add_edge u v`  
  - Adds an edge between vertices `u` and `v`.
- `remove_edge u v`  
  - Removes the edge between vertices `u` and `v`.
- `isReachable u v`  
  - Prints `Yes` if `v` is reachable from `u`, else `No`.
- `printGraph`  
  - Prints adjacency list of the current graph.
- `end`  
  - Terminates the program.

## Example Session

```
Graph
4 3
0 1
1 2
2 3
add_edge 0 2
isReachable 0 3
printGraph
end
```
