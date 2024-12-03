#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

//constructor - intiializes array list
objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP; //can change later

    aList = new objPos[arrayCapacity];
}

//destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;    //current number of elements in list
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity) throw std::overflow_error("List already full (insertHead)");   //checks if theres space to insert

    //shifts elements to right to make space for head
    for (int i = listSize; i > 0; i--) 
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;     //inserts new element at head

    listSize++;
}

//inserts an emenets at the tail (end of list)
void objPosArrayList::insertTail(objPos thisPos)
{
   if (listSize >= arrayCapacity) throw std::overflow_error("List already full (insertTail)");  //checks capacity

   aList[listSize] = thisPos;   //adds element at end

   listSize++; 
}

//removes element at head (start of list)
void objPosArrayList::removeHead()
{
    if (listSize == 0) throw std::underflow_error("List is empty (removeHead)");    //checks if emptey

    //shifts eleents to left
    for (int i = 0; i < listSize - 1; i++) 
    {
        aList[i] = aList[i+1];
    }

    listSize--;
}

//removes the element at tail (end of list)
void objPosArrayList::removeTail()
{
   if (listSize == 0) throw std::underflow_error("List is empty (removeTail)");     //checks if list is emptey

   listSize--; 
}

//retrieves element at start of list
objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0) throw std::underflow_error("List is empty (getHeadElement)");    //checks if list is empty

    return aList[0];
}

//retrieves element at end of list
objPos objPosArrayList::getTailElement() const
{
   if (listSize == 0) throw std::underflow_error("List is empty (getTailElement)");     //checks if list is empty

    return aList[listSize-1]; 
}

//retrieves specific element
objPos objPosArrayList::getElement(int index) const
{
    if (index < 0  || index >= arrayCapacity) throw std::out_of_range("Index out of range (getElement)");       //checks if valid input

    return aList[index];
}