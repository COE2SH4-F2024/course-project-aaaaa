#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000 

//global pointers
GameMechs* gameMechs; //pointer to GameMechs object
Player* player; //pointer to Player object

//function prototypes
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

    int startSize = 1; //Starting length of snake
    
    //initializes game mechanics and player objects
    gameMechs = new GameMechs();
    player = new Player(gameMechs, startSize);

    //generates the first food (not overlaping with the player)
    objPosArrayList* playerPosList = player->getPlayerPos();
    gameMechs->generateFood(*playerPosList);
}

void GetInput(void)
{
    if (MacUILib_hasChar()) 
    {
        //checks for user input
        char input = MacUILib_getChar();
        gameMechs->setInput(input);

        //THIS IS TO TEST THAT FOOD CAN BE GENERATED RANDOMLY AROUND THE BOARD(NOT ON THE PLAYER)
        //if (input == 'f') 
        //{
        //    objPosArrayList* playerPosList = player->getPlayerPos();
        //    gameMechs->generateFood(*playerPosList);
        //}
    }
}

void RunLogic(void)
{
    //updates players direction and position
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    MacUILib_printf("Score: %d\n", gameMechs->getScore());  //displays score

    int rowNum = gameMechs->getBoardSizeY();    
    int colNum = gameMechs->getBoardSizeX();    

    //Need to add player and food objects
    objPosArrayList* playerPosList = player->getPlayerPos(); //gets player position
    objPos foodPosition = gameMechs->getFoodPos(); //gets food position

    //loops through each cell of the game board
    for (int row = 0; row < rowNum; row++) 
    {
        for (int col = 0; col < colNum; col++) 
        {
            if (row == 0 || row == rowNum - 1 || col == 0 || col == colNum - 1) 
            {
                MacUILib_printf("#");   //draws the outline
            }

            //Add FOod
            else if (row == foodPosition.pos->y && col == foodPosition.pos->x) 
                {
                    MacUILib_printf("%c", foodPosition.getSymbol());
                }

            else 
            {
                bool isSegment = false;
                
                //Add snake body - checks if the current tile contains one of the snake's segments
                for (int i = 0; i < playerPosList->getSize(); i++) 
                { 
                    objPos segmentPos = playerPosList->getElement(i);

                    if (row == segmentPos.pos->y && col == segmentPos.pos->x) 
                    { 
                        MacUILib_printf("%c", segmentPos.getSymbol());  //draws snake segment
                        isSegment = true;
                        break;
                    }
                }
                
                if (!isSegment) 
                {
                    MacUILib_printf(" ");
                }
            }

        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Press ESC to end game.");
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
        MacUILib_printf("You have won!\nScore: %d", gameMechs->getScore());
    }
    else {
        //Lose screen (finish later)
        MacUILib_printf("You have lost!\nScore: %d", gameMechs->getScore());
    }
    
    //Delete objects from the heap
    delete gameMechs;
    delete player;

    MacUILib_uninit();
}