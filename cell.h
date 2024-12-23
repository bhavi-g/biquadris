#ifndef CELL_H
#define CELL_H
#include <iostream>

class Cell{
    int x;
    int y;
	bool isBlind;
    char fill;

    public:
	Cell(int x, int y, char fill);
	bool isFilled();
	int getX();
	int getY();
	void incY(int amount);
	void incX(int amount);
	void setX(int newX);
	void setY(int newY);
	char getFill();
	void setFill(char c);
	void blind(bool b);
    friend std::ostream &operator<<(std::ostream &o, const Cell &cell);
};

#endif
