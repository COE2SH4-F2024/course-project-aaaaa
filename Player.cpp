#include "Player.h"

Player::Player(GameMechs* thisGMRef, int startSize)
{
    mainGameMechsRef = thisGMRef;

    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    int startX = boardX/2;
    int startY = boardY/2;

    playerPosList = new objPosArrayList();

    playerPosList->insertHead(objPos(startX, startY, '*'));

    for (int i = 1; i < startSize; i++) { //Inserts tails to start length
        playerPosList->insertTail(objPos(startX-i, startY, '*'));
    }
    

    myDir = STOP;

    // more actions to be included
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
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
            if (myDir == UP || myDir == DOWN)
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
            mainGameMechsRef->setLoseFlag();
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

    //Gets coordinates of head
    int playerX = playerPosList->getElement(0).pos->x;
    int playerY = playerPosList->getElement(0).pos->y;

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
    if (myDir != STOP) {
        if(!checkSelfCollision(playerX, playerY)) {
            //update player's position
            playerPosList->insertHead(objPos(playerX, playerY, '*'));
            playerPosList->removeTail();
        }
        else {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }

        objPos foodPos = mainGameMechsRef->getFoodPos();
        bool grew = false;

        playerPosList->insertTail(objPos(playerX, playerY, '*'));

        if (playerX == foodPos.pos->x && playerY == foodPos.pos->y) 
        {
            mainGameMechsRef->incrementScore();
            mainGameMechsRef->generateFood(*playerPosList);
            grew = true;
        } 

        if (!grew)
        {
            playerPosList->removeTail();
        }
    }

    
}

bool Player::checkSelfCollision(int x, int y) {
    bool selfCollision = false;

    for (int i = 1; i < playerPosList->getSize(); i++) { //starts from 1 to avoid checking head
            Pos* segmentPos = playerPosList->getElement(i).getObjPos().pos;

            if (segmentPos->x == x && segmentPos->y == y) {
                selfCollision = true;
                break;
            }
        }

    return selfCollision;
}