#include "GameMechs.h"

GameMechs::GameMechs()
{
    exitFlag = false;
    loseFlag = false;
    input = 0;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    //Add food
    srand(static_cast<unsigned>(time(0)));
    foodPos.setObjPos(0, 0, 'O');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    exitFlag = false;
    loseFlag = false;
    input = 0;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    //Add food
    srand(static_cast<unsigned>(time(0)));
    foodPos.setObjPos(0, 0, 'O');
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{ 
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(const objPos& blockOff)
{
    int x, y;

    do
    {
        x = rand() % (boardSizeX - 2) + 1;
        y = rand() % (boardSizeY - 2) + 1;
    } while (x == blockOff.pos->x && y == blockOff.pos->y);

    foodPos.setObjPos(x, y, 'O');
}

objPos GameMechs::getFoodPos() const
{
    return foodPos;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here