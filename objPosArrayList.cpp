#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList; // returns the current number of elements in the array list
}

void objPosArrayList::insertHead(objPos thisPos)
{
    int i;

    // shifts all the elements over by one 
    for(i = sizeList; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);
    }

    aList[0].setObjPos(thisPos); // sets the new element at the beginning of the list 
    sizeList++; // increases the list size by 1
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[sizeList].setObjPos(thisPos); // inserts the element at the end of the list 
    sizeList++; // increases the list size by 1
}

void objPosArrayList::removeHead()
{
    int i;

    // remove the element at the beginning of the list, so all the elements are shift towards the beginning of the lsit by 1
    for(i = 0; i < sizeList - 1; i++)
    {
        aList[i].setObjPos(aList[i+1]);
    }
    sizeList--; // decreases the size of the list by 1
}

void objPosArrayList::removeTail()
{
    sizeList--; // removes the element at the end of the list so the list size decreases by 1
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]); // gets the element at the beginning of the array 
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]); // gets the last element of the list 
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]); // gets the element at a specified index
}
