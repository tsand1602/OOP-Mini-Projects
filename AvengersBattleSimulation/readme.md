# Avengers Battle Simulation

This C++ project simulates battles between Avengers and their enemies, using object-oriented programming concepts. Each character is equipped with a customizable suit, and the game progresses through interactive commands.

## Features

- **Suit Mechanics:** Each Avenger/enemy has a suit with power, durability, energy storage, and heat level.
- **Battle System:** Issue commands such as attack, repair, boost power, and upgrade suits.
- **Battle Log:** Tracks all actions during the simulation.
- **Win/Loss Logic:** Determines which side is winning based on suit stats.

## How to Run

1. **Compile the code:**
   ```sh
   g++ -o avengers_simulation code.cpp
   ```

2. **Run the simulation:**
   ```sh
   ./avengers_simulation
   ```

## Input Format

When you run the program, provide input in the following order:

1. **Three integers:**  
   - `k`: Number of suits  
   - `n`: Number of heroes  
   - `m`: Number of enemies  

2. **Suit details:**  
   For each of the `k` suits, input four integers:  
   - Power Level  
   - Durability  
   - Energy Storage  
   - Heat Level  

3. **Hero details:**  
   For each of the `n` heroes, input:  
   - Name (single word, no spaces)  
   - Attack Strength (integer)  

4. **Enemy details:**  
   For each of the `m` enemies, input:  
   - Name (single word, no spaces)  
   - Attack Strength (integer)  

5. **Type the command:**  
   ```
   BattleBegin
   ```
6. **Enter commands (one per line):**
   - `Attack <Avenger1> <Avenger2>`
   - `Repair <AvengerName> <amount>`
   - `BoostPowerByFactor <AvengerName> <factor>`
   - `BoostPower <AvengerName> <P> <D> <E> <H>`
   - `AvengerStatus <AvengerName>`
   - `Upgrade <AvengerName>`
   - `PrintBattleLog`
   - `BattleStatus`
   - `End` (to terminate the battle loop)

## Example Input

```
2 2 1
1000 500 300 0
1200 400 350 10
IronMan 200
Thor 250
Thanos 500
BattleBegin
Attack IronMan Thanos
Repair IronMan 100
BoostPowerByFactor Thor 20
PrintBattleLog
BattleStatus
End
```

## Example Commands

```
Attack IronMan Thanos
Repair IronMan 100
BoostPowerByFactor Thor 20
Upgrade IronMan
PrintBattleLog
BattleStatus
End
```
