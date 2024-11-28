#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    int startX = boardX/2;
    int startY = boardY/2;

    playerPos.setObjPos(startX, startY, '*');

    myDir = STOP;

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    //updates direction based on input
    switch(input)
    {
        case 'w':
            if (myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = UP;
            }
            break;

        case 's':
            if (myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = DOWN;
            }
            break;

        case 'a':
            if (myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = LEFT;
            }
            break;

        case 'd':
            if (myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = RIGHT;
            }
            break;

        case 27:
            mainGameMechsRef->setExitTrue();
            break;

        default:
            break;
    }
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    int playerX = playerPos.pos->x;
    int playerY = playerPos.pos->y;

    switch (myDir)
    {
        case UP:
            playerY--;
            if (playerY < 1) 
            {
                playerY = boardY - 2; 
            }
            break;

        case DOWN:
            playerY++; 
            if (playerY >= boardY - 1)
            {
                playerY = 1; 
            }
            break;

        case LEFT:
            playerX--;
            if (playerX < 1) 
            {
                playerX = boardX - 2; 
            }
            break;

        case RIGHT:
            playerX++;
            if (playerX >= boardX - 1)
            {
                playerX = 1;
            }
            break;

        case STOP:

        default:
            break;
    }

    //update player's position
    playerPos.setObjPos(playerX, playerY, '*');
    
}

// More methods to be added