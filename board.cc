#include "board.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Board::Board(std::shared_ptr <Player> player1, std::shared_ptr <Player> player2, Graphics *g): player1{player1}, player2{player2},
																				  graphics{g} {}

void Board::printBoard(bool hasGraphics){
    const string sep = "      ";
    const int GRID_HEIGHT = 18;
    const int GRID_WIDTH = 11;
	player1 -> addBlock();
	player2 -> addBlock();

    cout << "Level:      " << player1 -> pLevel -> getLevel() << sep << "Level:      " << player2 -> pLevel -> getLevel() << endl;
    cout << "Score:      " << player1 -> score << sep << "Score:      " << player2 -> score << endl;
	cout << "High Score:     " << highScore << endl;
    cout << "+-----------+" << sep << "+-----------+" << endl;

    for(int y = 0; y < GRID_HEIGHT; y++){
		cout << '|';
		for(int x = 0; x < GRID_WIDTH; x++){
	    	cout << player1 -> grid[y][x];
		}

		cout << '|' << sep << '|';
	
		for(int x = 0; x < GRID_WIDTH; x++){
	    	cout << player2 -> grid[y][x];
		}

		cout << '|' << endl;
    }
    cout << "+-----------+" << sep << "+-----------+" << endl;
    cout << "Next:        " << sep << "Next:        " << endl;
	for(int i = 0; i < 4; i++){
		cout << player1 -> nextBlock -> blockGrid[0][i];
	}
	cout << "         " << sep;
	for(int i = 0; i < 4; i++){
		cout << player2 -> nextBlock -> blockGrid[0][i];
	}
	cout << endl;
	for(int i = 0; i < 4; i++){
		cout << player1 -> nextBlock -> blockGrid[1][i];
	}
	cout << "         " << sep;

	for(int i = 0; i < 4; i++){
		cout << player2 -> nextBlock -> blockGrid[1][i];
	}
	cout << '\n' << endl;
	if (hasGraphics) {
		graphics->renderBoard(*this);
	}
	player1 -> removeBlock();
	player2 -> removeBlock();
}

void Board::replaceCells(std::shared_ptr <Player>& player, Block* remove){
    for(auto c: remove->structure){
		player -> grid[c.getX()][c.getY()].setFill(' ');
    }
    for(auto c: player -> curBlock -> structure){
		player -> grid[c.getX()][c.getY()].setFill(c.getFill());
    }
}

void Board::drop(shared_ptr <Player>& player){
	while(checkDown(player)){
		player -> curBlock -> moveDown();
	}
	player -> placeBlock();
	player -> blocksDropped++;
	clearLines(player);
	if(player -> level == 4 && player -> blocksDropped != 0  && player -> blocksDropped % 5 == 0){
		dropStar(player);
		clearLines(player);
	}
}

void Board::dropStar(std::shared_ptr <Player>& player){
	for(int i = 3; i < 18; i++){
		if(i == 17 || player -> grid[i+1][5].isFilled()){
			player -> grid[i][5].setFill('*');
			return;
		}
	}

}

void Board::clearLines(shared_ptr <Player>& player){
	int numLinesCleared = 0;
	bool flag;
	for(int y = 17; y >= 0; y--){
		flag = true;
		for(int x = 0; x < 11; x++){
			if(!player -> grid[y][x].isFilled()){
				flag = false;
			}
			if(numLinesCleared > 0){
				player -> grid[y + numLinesCleared][x].setFill(player -> grid[y][x].getFill());
			}
		}
		if(flag){
			numLinesCleared++;
			for(int x = 0; x < 11; x++){
				player -> grid[y][x].setFill(' ');
			}
			for(size_t j = 0; j < player -> prevBlocks.size(); j++){
				for(size_t i = 0; i < player -> prevBlocks[j] -> structure.size(); i++){
					if(player -> prevBlocks[j] -> structure[i].getY() == y){
						player -> prevBlocks[j] -> structure.erase(player -> prevBlocks[j] -> structure.begin() + i);
						i--;
					}
				}
				if(player -> prevBlocks[j] -> structure.size() == 0){
					player -> score += (player -> prevBlocks[j] -> level + 1) * (player -> prevBlocks[j] -> level + 1);
					if (player -> score > highScore) {
						highScore = player -> score;
					}
					player -> prevBlocks.erase(player -> prevBlocks.begin() + j);
					j--;
				}
			}
		}
	}
	if(numLinesCleared > 0){
		player -> blocksDropped = 0;
		player -> score += (numLinesCleared + player -> getLevel()) * (numLinesCleared + player -> getLevel());
		if (player -> score > highScore) {
			highScore = player -> score;
		}
	}
	if(numLinesCleared >= 2){
		player -> hasSpecial = true;
	}
}

bool Board::rotate(shared_ptr <Player>& player, bool clockwise){
	if(checkRotate(player, clockwise)){
		player -> curBlock -> rotate(clockwise);
		if(!checkDown(player)){
			drop(player);
			return true;
		}
		else if(player -> curBlock -> getLevelHeavy()){
			return moveDown(player);
		}
	}
	return false;
}

bool Board::checkRotate(shared_ptr <Player>& player, bool clockwise){
	std::shared_ptr <Block> copy =  player -> curBlock -> cloneBlock();
	copy -> rotate(clockwise);
	for(auto c: copy -> structure){
		if(c.getY() >= 18 || c.getY() < 0 || c.getX() >= 11 || c.getX() < 0 || player -> grid[c.getY()][c.getX()].isFilled()){
			return false;
		}
	}
	return true;
}

bool Board::moveDown(shared_ptr <Player>& player){
    if(checkDown(player)){
		player -> curBlock -> moveDown();
		if(!checkDown(player)){
	    	drop(player);
			return true;
		}	
    }
	return false;
}

bool Board::moveLeft(shared_ptr <Player>& player){
    if(checkLeft(player)){
		player -> curBlock -> moveHorizontal(0);
		if(!checkDown(player)){
	    	drop(player);
			return true;
		}
		if(player -> curBlock -> getSpecialHeavy()){
			if(moveDown(player)){
				return true;
			}
			return moveDown(player);
		}
		if(player -> curBlock -> getLevelHeavy()){
			return moveDown(player);
		}
    }
	return false;
}

bool Board::moveRight(shared_ptr <Player>& player){
    if(checkRight(player)){
		player -> curBlock -> moveHorizontal(1);
		if(!checkDown(player)){
	    	drop(player);
			return true;
		}
		if(player -> curBlock -> getSpecialHeavy()){
			if(moveDown(player)){
				return true;
			}
			return moveDown(player);
		}
		if(player -> curBlock -> getLevelHeavy()){
			return moveDown(player);
		}
    }
	return false;
}

bool Board::checkDown(shared_ptr <Player>& player){   
    for(auto c: player -> curBlock -> structure){
		if(c.getY() >= 17 || player -> grid[c.getY() + 1][c.getX()].isFilled()){
	    	return false;
		}
    }
    return true;
}

bool Board::checkLeft(shared_ptr <Player>& player){
    for(auto c: player -> curBlock -> structure){
		if(c.getX() <= 0 || player -> grid[c.getY()][c.getX() - 1].isFilled()){
	    	return false;
		}
    }
	return true;
}

bool Board::checkRight(shared_ptr <Player>& player){
    for(auto c: player -> curBlock -> structure){
		if(c.getX() >= 10 || player -> grid[c.getY()][c.getX() + 1].isFilled()){
	    	return false;
		}
    }
	return true;
}

void Board::resetBoard(int p1Level, int p2Level){
    player1 -> reset(p1Level);
	player2 -> reset(p2Level);
}
