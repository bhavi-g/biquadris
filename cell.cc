#include "cell.h"

using namespace std;

Cell::Cell(int x, int y, char fill): x{x}, y{y}, fill{fill}, isBlind{false} {}

bool Cell::isFilled(){
    if(fill == ' '){
	    return false;
    }
    return true;
}

int Cell::getX(){
    return x;
}

int Cell::getY(){
    return y;
}

char Cell::getFill(){
    return fill;
}

void Cell::incY(int amount){
    y += amount;
}

void Cell::incX(int amount){
    x += amount;
}

void Cell::setX(int newX){
    x = newX;
}

void Cell::setY(int newY){
    y = newY;
}

void Cell::setFill(char c){
    fill = c;
}

void Cell::blind(bool b) {
    isBlind = b;
}

ostream &operator<<(ostream &o, const Cell &cell) {
    if (cell.isBlind) {
        o << '?';
    } else {
        o << cell.fill;
    }
    return o;
}
