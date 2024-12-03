#include "GameMechs.h"

//default constructor
GameMechs::GameMechs()
{
    exitFlag = false;
    loseFlag = false;
    input = 0;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    //Add food
    srand(static_cast<unsigned>(time(0)));  //initializes random number generation (food placement)
    foodPos.setObjPos(0, 0, 'O');
}

//parameterized constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    exitFlag = false;
    loseFlag = false;
    input = 0;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    //Add food
    srand(static_cast<unsigned>(time(0)));  //intitializes random number generation for food
    foodPos.setObjPos(0, 0, 'O');
}

// do you need a destructor? - NO
GameMechs::~GameMechs()
{
    //no dymnamic memory is allocated so no cleanup is needed.
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;    //current state of exit flag
}

bool GameMechs::getLoseFlagStatus() const
{ 
    return loseFlag;    //current state of lost flag
} 

char GameMechs::getInput() const
{
    return input;   //most recent input fromuser
}

int GameMechs::getScore() const
{
    return score;   //curent score (1 less than snake length)
}

void GameMechs::incrementScore()
{
    score++;    //increments score
}

//generates food randomly (not overlaping with the player)
void GameMechs::generateFood(const objPosArrayList& blockOff)
{
    int x, y;
    bool isOverlap;

    do
    {
        isOverlap = false;

        //random coordinates
        x = rand() % (boardSizeX - 2) + 1;
        y = rand() % (boardSizeY - 2) + 1;
        
        //checks for overlap
        for (int i = 0; i < blockOff.getSize(); i++) 
        {
            if (x == blockOff.getElement(i).pos->x && y == blockOff.getElement(i).pos->y) 
            {
                isOverlap = true;
            }
        }

    } while (isOverlap);

    foodPos.setObjPos(x, y, 'O');   //sets food position
}

objPos GameMechs::getFoodPos() const
{
    return foodPos;     //current position of food
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;  //width of board
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;  //height of board
}

void GameMechs::setExitTrue()
{
    exitFlag = true;    //exits the game
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;    //user lost the game
}

void GameMechs::setInput(char this_input)
{
    input = this_input;     //msot revent input from user
}

void GameMechs::clearInput()
{
    input = 0;  //clears user input
}