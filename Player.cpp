#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    // sets the initial position of the player at the center of the board
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList = new objPosArrayList(); // creates a new list for player position
    playerPosList->insertHead(tempPos); // inserts the initial position into the list 

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    

    char input = mainGameMechsRef->getInput();
    
    // updates the player's position depending on the input of the player 
    switch(input)
    {
        case 'w': //up

            // does not allow the player to move down when it is moving up 
            if(myDir == UP || myDir == DOWN){
                break;
            }

            myDir = UP;
            break;
                
        case 'a': //left

            // does not allow the player to move right when it is moving left
            if(myDir == LEFT || myDir == RIGHT){
                break;
            }

            myDir = LEFT;
            break;
    
        case 's': //down

            // does not allow the player to move up when it is moving down 
            if(myDir == UP || myDir == DOWN){
                break;
            }

            myDir = DOWN;
            break;

        case 'd': //right

            // does not allow the player to move left when it is moving right
            if(myDir == RIGHT || myDir == LEFT)
            {
                break;
            }

            myDir = RIGHT;
            break;

        default:
            break;
    }    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos currHead; // hold the position information of the current head
    playerPosList->getHeadElement(currHead);

    // moves the player depending on their direction 
    switch(myDir){

        case STOP:
            break;

        case LEFT:
            currHead.x --;

            // wraps around the board if the snake touches the boundary
            if(currHead.x == 0){
                currHead.x = 28;
            }
            break;

        case RIGHT:
            currHead.x ++;

            // wraps around the board if the snake touches the boundary
            if(currHead.x == 29){
                currHead.x = 1;
            }
            break;

        case UP:
            currHead.y --;

            // wraps around the board if the snake touches the boundary
            if(currHead.y == 0){
                currHead.y = 13;
            }
            break;

        case DOWN:
            currHead.y ++;

            // wraps around the board if the snake touches the boundary
            if(currHead.y == 14){
                currHead.y = 1;
            }
            break;
    }

    // new current head should be inserted at the head of the list
    playerPosList->insertHead(currHead);

    // remove tail
    playerPosList->removeTail();

}

void Player::increasePlayerLength()
{
    // increases the player's length by addding an element at the position of the current tail
    objPos currTail;
    playerPosList->insertTail(currTail);
}


bool Player::checkSelfCollision()
{
    // checks if the head of the snake collides with its body
    bool checkCollision = false;
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    // checks each element of the body to see if it has collided with the head
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos tempBodyElement;
        playerPosList->getElement(tempBodyElement, i);

        // checks if the position of the head is equal to one of the elements of the body
        if(currHead.isPosEqual(&tempBodyElement))
        {
            checkCollision = true;
        }
    }

    return checkCollision;

}