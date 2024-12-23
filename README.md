# Biquadris  

Biquadris is a modern, competitive twist on the classic Tetris game, built entirely in C++. It features a graphical interface supported by Xming and a robust design leveraging advanced software engineering principles. Players can enjoy a fully functional Tetris-inspired experience, complete with levels, scoring, and strategic gameplay mechanics.

## Features  
- Two-Player Competitive Mode: Play with a friend, each managing separate boards.  
- Text and Graphical Modes: Enjoy gameplay in a terminal or a fully graphical interface with color-coded blocks.  
- Levels and Difficulty: Supports levels 0–4, with unique block generation probabilities and challenges.  
- Command Interpreter: Issue commands like move, rotate, and drop, with shortcuts and multipliers for faster gameplay.  
- Scoring System: Earn points based on your level and cleared rows, with real-time tracking of current and high scores.  
- Special Actions: Trigger game-changing effects like "blind," "heavy," or "force" to disrupt your opponent’s strategy.  

## Design Patterns  
The architecture of Biquadris incorporates several design patterns for flexibility, scalability, and maintainability:  
- Model-View-Controller (MVC): Separates game logic, user input, and graphical/text displays.  
- Observer Pattern: Ensures real-time updates between the game state and its visual representations.  
- Decorator Pattern: Dynamically modifies block behaviors (e.g., "heavy" blocks).  
- Factory Method: Simplifies the creation of game objects like blocks and boards.  

## Gameplay Overview  
Each player has a board of 11 columns and 15 rows, with three extra rows reserved for block rotations. Players take turns placing tetrominoes (blocks) on their board. The game ends when a player can no longer place blocks on their board.  

### Levels  
- Level 0: Blocks appear in sequence from pre-defined files.  
- Level 1: Random blocks, with S and Z blocks having higher probabilities.  
- Level 2: Random blocks, with equal probabilities for all types.  
- Level 3: Introduces "heavy" blocks that drop an additional row after every move.  
- Level 4: Adds 1x1 "garbage" blocks if rows are not cleared frequently.  

## Installation and Setup  
1. Clone the repository:  
   ```bash
   [git clone https://github.com/username/biquadris.git](https://github.com/bhavi-g/biquadris.git)
   cd biquadris
   ```  
2. Build the project:  
   ```bash
   make
   ```  
3. Run the game:  
   ```bash
   ./biquadris
   ```  
4. For graphical mode, ensure Xming is running. Use `-text` for text-only mode:  
   ```bash
   ./biquadris -text
   ```  

## Commands  
- **left/right/down**: Move the block in the specified direction.  
- **clockwise/counterclockwise**: Rotate the block.  
- **drop**: Drop the block to the bottom of the board.  
- **levelup/leveldown**: Change the difficulty level.  
- **restart**: Start a new game.  

## Requirements  
- **C++ Compiler**: Compatible with `g++` (ensure `-std=c++20` support).  
- **Xming**: For graphical rendering on Windows.  
- **Linux/Unix Shell**: Use `ssh -Y` for remote connections with X11 forwarding enabled.  

## Future Enhancements  
- Add more levels and special block types.  
- Expand command-line options for customization.  
- Implement AI for single-player mode.  

## Credits  
This project was developed as part of the CS246 Fall 2024 course at the University of Waterloo.  
