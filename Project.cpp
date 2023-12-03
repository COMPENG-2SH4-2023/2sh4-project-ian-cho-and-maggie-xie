#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM; // initializes game mechanics
Player* myPlayer; // initializes player 



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

   myGM = new GameMechs(30, 15);
   myPlayer = new Player(myGM);

   srand(static_cast<unsigned int>(time(nullptr))); // random number generator

   objPosArrayList* playerBody = myPlayer->getPlayerPos();

   myGM->generateFood(playerBody); // generates a food position while making sure that it is not on the player's body

}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myGM->getScore();
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempPos;
    objPos foodPos;

    myGM->getFoodPos(foodPos); // gets the position of the food 

    for(int i = 0; i < playerBody->getSize(); i++)
    {
        playerBody-> getElement(tempPos, i);

        if(myPlayer->checkSelfCollision() == true) // checks if the player collides with itself
        {
            myGM->setExitTrue(); // ends the game
            myGM->setLoseFlag();
        }

        if(tempPos.x == foodPos.x && tempPos.y == foodPos.y) // checks if the player's position is at the food position 
        {
            myGM->generateFood(playerBody); // generate another food at a different position 
            myPlayer->increasePlayerLength(); // increases the player's length 
            myGM->incrementScore(); // increments the score
        }

    }

}

void DrawScreen(void)
{
    int width = 30, length = 15;
    int i, j;
    int item;
    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    //draw the food at its current position
    objPos tempPos;
    objPos foodPos;
    myGM->getFoodPos(foodPos);

    MacUILib_clearScreen();  

    for(i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(j = 0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;

            // iterate through every element in the list and draws the player's body 
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            
            if (drawn) continue; // if player body was drawn, don't draw anything below

            // draws the border of the board 
            if(i == 0 || j == 0|| i == myGM->getBoardSizeY()-1 || j == myGM->getBoardSizeX()-1)
            {
                MacUILib_printf("#");
            }

            // draws the food 
            else if(j == foodPos.x && i == foodPos.y)
            {
                MacUILib_printf("%c", foodPos.symbol);
            }

            // draws a space everywhere else that is not occupied 
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("%c", '\n');
    }
    
    
    MacUILib_printf("Score: %d\n", myGM->getScore()); // displays the score on the board 

    if(myGM->getExitFlagStatus() == true)
    {
        MacUILib_printf("\nYOU LOST"); // displays the ending message if the player lost
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_uninit();

    // removes myGM and myPlayer from the heap
    delete myGM;
    delete myPlayer;
}
