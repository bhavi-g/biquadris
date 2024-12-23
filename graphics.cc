#include "graphics.h"
#include <string>
#include <iostream>

Graphics::Graphics()
    : window(std::make_unique<Xwindow>(600, 520)) // Default dimensions for 2-player boards + score area
{}

// Draws the entire board graphically
void Graphics::renderBoard(const Board& board) {
    const int boardWidth = 11 * cellSize; // 11 columns
    const int boardHeight = 18 * cellSize; // 18 rows

    // Clear the window
    window->fillRectangle(0, 0, window->getWidth(), window->getHeight(), Xwindow::White);

    // Draw Player 1's board
    for (int y = 0; y < 18; ++y) {
        for (int x = 0; x < 11; ++x) {
            char fill = board.player1->grid[y][x].getFill();
            int color;
            switch (fill) {
                case 'I': color = Xwindow::Red; break;
                case 'J': color = Xwindow::Green; break;
                case 'L': color = Xwindow::Blue; break;
                case 'T': color = Xwindow::Teal; break;
                case 'S': color = Xwindow::Yellow; break;
                case 'Z': color = Xwindow::Pink; break;
                case 'O': color = Xwindow::Purple; break;
                case '?': color = Xwindow::Gray; break;
                case '*': color = Xwindow::Brown; break;
                default: color = Xwindow::White; break; // Empty space
            }
            window->fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, color);
        }
    }
    //separator for players
    window->fillRectangle(11 * cellSize, 0, 2 * cellSize, 18 * cellSize, Xwindow::Black);
    // Draw Player 2's board (offset by spacing)
    for (int y = 0; y < 18; ++y) {
        for (int x = 0; x < 11; ++x) {
            char fill = board.player2->grid[y][x].getFill();
            int color;
            switch (fill) {
                case 'I': color = Xwindow::Red; break;
                case 'J': color = Xwindow::Green; break;
                case 'L': color = Xwindow::Blue; break;
                case 'T': color = Xwindow::Teal; break;
                case 'S': color = Xwindow::Yellow; break;
                case 'Z': color = Xwindow::Pink; break;
                case 'O': color = Xwindow::Purple; break;
                case '?': color = Xwindow::Gray; break;
                case '*': color = Xwindow::Brown; break;
                default: color = Xwindow::White; break; // Empty space
            }
            window->fillRectangle(boardWidth + spacing + (x * cellSize), y * cellSize, cellSize, cellSize, color);
        }
    }

    // Render the scores
    renderScores(board.player1, board.player2);
    std::string hScore = "High Score: " + std::to_string(board.highScore);
    window->drawString(10, 19 * cellSize + 20, hScore);
}

// Draw the scores and levels for both players
void Graphics::renderScores(std::shared_ptr <Player> player1, std::shared_ptr <Player> player2) {
    const int scoreY = 19 * cellSize; // Below the grid

    std::string player1Score = "P1: Level " + std::to_string(player1->getLevel()) +
                               " Score: " + std::to_string(player1->score);
    std::string player2Score = "P2: Level " + std::to_string(player2->getLevel()) +
                               " Score: " + std::to_string(player2->score);
    

    window->drawString(10, scoreY, player1Score);
    window->drawString(window->getWidth() / 2 + 10, scoreY, player2Score);
}
