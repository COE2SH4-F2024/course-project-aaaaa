#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP; //can change later

    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity) throw std::overflow_error("List already full (insertHead)");

    for (int i = listSize; i > 0; i--) {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
   if (listSize >= arrayCapacity) throw std::overflow_error("List already full (insertTail)");

   aList[listSize] = thisPos;

   listSize++; 
}

void objPosArrayList::removeHead()
{
    if (listSize == 0) throw std::underflow_error("List is empty (removeHead)");

    for (int i = 0; i < listSize - 1; i++) {
        aList[i] = aList[i+1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
   if (listSize == 0) throw std::underflow_error("List is empty (removeTail)");

   listSize--; 
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0) throw std::underflow_error("List is empty (getHeadElement)");

    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
   if (listSize == 0) throw std::underflow_error("List is empty (getTailElement)");

    return aList[listSize-1]; 
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0  || index >= arrayCapacity) throw std::out_of_range("Index out of range (getElement)");

    return aList[index];
}