# Event Dependency Analyser

This C++ project schedules various event types (Concerts, Theatre Shows, Weddings) and calculates the maximum net profit from a set of events that do not overlap in time. It uses object-oriented programming and dynamic programming to solve the weighted event scheduling problem.

## Features

- **Supports Multiple Event Types:**  
  - Concerts  
  - Theatre Shows  
  - Weddings  
  Each with its own profit calculation logic.
- **Non-overlapping Scheduling:**  
  Selects the optimal subset of non-overlapping events for maximum profit.
- **Dynamic Programming:**  
  Efficiently computes the solution using memoization and binary search for event dependencies.

## How to Run

1. **Compile the code:**
   ```sh
   g++ -o event_analyser code.cpp
   ```

2. **Run the program:**
   ```sh
   ./event_analyser
   ```

## Input Format

When you run the program, provide input in the following order:

1. **Number of events:**  
   An integer `n`.

2. **Event details for each event:**  
   For each event, input:
   - **Event type:**  
     - `1` for Concert  
     - `2` for Theatre Show  
     - `3` (or any other integer) for Wedding  

   - **For Concert (type 1):**  
     ```
     startTime endTime TicketPrice TicketsSold ArtistFee LogisticCost
     ```

   - **For Theatre Show (type 2):**  
     ```
     startTime endTime BaseTicketPrice TotalSeats VenueCost
     ```

   - **For Wedding (type 3):**  
     ```
     startTime endTime BaseAmount DecorationCost GuestCount VenueCost
     ```

## Example Input

```
3
1 10 20 500 100 20000 10000
2 8 15 400 120 9000
3 0 12 100000 15000 250 30000
```

## Output

- The program prints the maximum net profit (to two decimal places) achievable by scheduling a subset of non-overlapping events.

### Example Output

```
81900.00
```
