#include "GameMechs.h"
#include "MacUILib.h"


GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false; // sets exitFlag to false 

    // initializes the board size
    boardSizeX = 20;
    boardSizeY = 10;

    // initialize food position and symbol
    foodPos.setObjPos(-1, -1, 'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;

    foodPos.setObjPos(-1, -1, 'o');
}

bool GameMechs::getExitFlagStatus()
{
    // returns the status of the exitFlag
    return exitFlag;
}

char GameMechs::getInput()
{
    // takes the input that the player uses 
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();

        if (input == 27) // exits the game when the escape key is pressed
        {
            exitFlag = true;
        }
    }
    
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX; // returns the x-dimension of the board
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY; // returns the y-dimension of the board
}

void GameMechs::setExitTrue()
{
    exitFlag = true; // sets the exitFlag to true
}

void GameMechs::setInput(char this_input)
{
    input = this_input; 
}

void GameMechs::clearInput()
{
    input = 0; // clears the input that the player has used previously 
}

int GameMechs::getScore()
{
    return score; // returns the current score 
}

void GameMechs::incrementScore()
{
    score++; // increases the score by 1
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag; // returns the status of the loseFlag
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;  // sets loseFlag to true
}

void GameMechs::generateFood(objPosArrayList* blockoff)
{
    objPos tempPos;
    int i, x = 0;
    bool validPos;

    while(validPos == false)
    {
        x = 0;

        // makes sure that the food appears within the range of the borders
        foodPos.x = (rand() % 28) + 1;
        foodPos.y = (rand() % 13) + 1; 

        // loops through the snake's body to make sure that the food does not appear on the snake 
        for(i = 0; i < blockoff->getSize(); i++)
        {
            blockoff->getElement(tempPos, i);
            
            if(foodPos.x == tempPos.x && foodPos.y == tempPos.y)
            {
                x++;
            }
        }

        // if x is less than 1, that means a valid food position is found; if not, that means a new food position needs to be found
        if(x < 1)
        {
            validPos = true;
        } else{
            validPos = false;
        }

    }

}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos); // gets the food position 
}
