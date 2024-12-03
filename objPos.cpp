#include "objPos.h"

//default constructor
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

//parameterized constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

//destructor
objPos::~objPos() {
    delete pos;
}

//copy constructor
objPos::objPos(const objPos& other) {
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}

//copy assignment operator (deep copy)
objPos& objPos::operator = (const objPos& other) {
    if (this == &other) return *this; //Only runs operation if current object is not already equal to the other object

    delete pos;
    pos = nullptr;

    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;

    return *this;
}

//sets position and symbol
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

//sets position and symbol using indicidual paramaters
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//returns curernt objPos
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

//returns symbol of objPos
char objPos::getSymbol() const
{
    return symbol;
}

//compares position of objPos with another objPos
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

//returns symbol if positions are equal (null if not)
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}