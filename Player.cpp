#include "Player.h"

//initializes the player object
Player::Player(GameMechs* thisGMRef, int startSize)
{
    mainGameMechsRef = thisGMRef;   //references game mechanics obect

    //gets board dimensions
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    //sets players initial location to the center of the board
    int startX = boardX/2;
    int startY = boardY/2;

    playerPosList = new objPosArrayList();  //lsit to store player position

    playerPosList->insertHead(objPos(startX, startY, '*'));     //places head of snake at starting position

    for (int i = 1; i < startSize; i++) 
    { 
        playerPosList->insertTail(objPos(startX-i, startY, '*'));   //Inserts tails to start length
    }
    
    myDir = STOP;   //snake starts stationary until user input
}

//destructor
Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;   //pointer to players position list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    //updates direction based on input
    switch(input)
    {
        case 'w':   //up
            if (myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = UP;
            }
            break;

        case 's':   //down
            if (myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = DOWN;
            }
            break;

        case 'a':   //left
            if (myDir == UP || myDir == DOWN)
            {
                myDir = LEFT;
            }
            break;

        case 'd':   //right
            if (myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = RIGHT;
            }
            break;

        case 27:    //exit flag
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;

        default:
            break;
    }

    mainGameMechsRef->clearInput();
}

//moves player and updates position
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    //Gets coordinates of head
    int playerX = playerPosList->getElement(0).pos->x;
    int playerY = playerPosList->getElement(0).pos->y;

    //updates the position based on the direction
    switch (myDir)
    {
        case UP:
            playerY--;
            if (playerY < 1) 
            {
                playerY = boardY - 2;   //vertical wrap around
            }
            break;

        case DOWN:
            playerY++; 
            if (playerY >= boardY - 1)  
            {
                playerY = 1;    //vertical wrap around
            }
            break;

        case LEFT:
            playerX--;
            if (playerX < 1) 
            {
                playerX = boardX - 2;   //horizontal wrap around
            }
            break;

        case RIGHT:
            playerX++;
            if (playerX >= boardX - 1)  
            {
                playerX = 1;    //horizontal wrap around
            }
            break;

        case STOP:

        default:
            break;
    }

    //update player's position (if moving)
    if (myDir != STOP) {
        if (!checkSelfCollision(playerX, playerY)) 
        {
            //update player's position (add new head and remove tail)
            playerPosList->insertHead(objPos(playerX, playerY, '*'));
        }

        else 
        {
            //ends game if self collision occurs
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }

        //checks for collision with food
        objPos foodPos = mainGameMechsRef->getFoodPos();
        bool grew = false;

        if (playerX == foodPos.pos->x && playerY == foodPos.pos->y) 
        {
            //food consumed - add to score and grow by 1
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

//checks if player collides with itself
bool Player::checkSelfCollision(int x, int y) {
    bool selfCollision = false;

    for (int i = 1; i < playerPosList->getSize(); i++)  //starts from 1 to avoid checking head
    { 
            Pos* segmentPos = playerPosList->getElement(i).getObjPos().pos;

            if (segmentPos->x == x && segmentPos->y == y) 
            {
                selfCollision = true;   //checks if ant segment matches given coordinates
                break;
            }
    }

    return selfCollision;
}