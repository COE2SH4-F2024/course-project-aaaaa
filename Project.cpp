#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs; //pointer to GameMechs object
Player* player; //pointer to Player object


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    gameMechs = new GameMechs();
    player = new Player(gameMechs);
}

void GetInput(void)
{
    if (MacUILib_hasChar()) {
        gameMechs->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    MacUILib_printf("Score: %d\n", gameMechs->getScore());

    int rowNum = gameMechs->getBoardSizeY();
    int colNum = gameMechs->getBoardSizeX();

    //Need to add player and food objects
    
    objPos playerPosition = player->getPlayerPos(); //gets player position

    for (int row = 0; row < rowNum; row++) {
        for (int col = 0; col < colNum; col++) {
            if (row == 0 || row == rowNum - 1 || col == 0 || col == colNum - 1) {
                MacUILib_printf("#");
            }
            else if (row == playerPosition.pos->y && col == playerPosition.pos->x)
            {
                MacUILib_printf("%c", playerPosition.getSymbol()); //draws the player '*'
            }
            //Add snake body
            //Add items

            else MacUILib_printf(" "); //temporary: replace when adding snake body and items

        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    if (!gameMechs->getLoseFlagStatus()) {
        //Win screen (finish later)
        MacUILib_printf("Win screen");
    }
    else {
        //Lose screen (finish later)
        MacUILib_printf("Lose screen");
    }
    
    //Delete objects from the heap
    delete gameMechs;
    delete player;

    MacUILib_uninit();
}
