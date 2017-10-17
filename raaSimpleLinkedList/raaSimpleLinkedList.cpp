// raaSimpleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>

struct linkedListElement
{
	linkedListElement *m_pNext;
	linkedListElement *m_pLast;
	int *m_ipData;
};

linkedListElement *g_pHead = 0;
linkedListElement *g_pTail = 0;
int g_Size = 0;

void printList();

bool isInList(linkedListElement *pElement);

void pushHead(linkedListElement *pElement);
void pushTail(linkedListElement *pElement);
linkedListElement* createNewElement(int data);

linkedListElement* popHead();
linkedListElement* popTail();
linkedListElement* deleteElement(linkedListElement *pElement);

int main(char* argv[])
{
	linkedListElement *pElement=0;

	pElement=createNewElement(4);
	pushHead(pElement);

	pElement=createNewElement(2);
	pushTail(pElement);

	pElement=createNewElement(8);
	pushHead(pElement);

	pElement=createNewElement(5);
	pushTail(pElement);

	printList();

	delete popHead();
	delete popTail();

	pushHead(popTail());

	printf("\n\n\n");
	printList();

	_getch();
	return 0;
}

void printList()
{
	unsigned int uiCount=0;
	for(linkedListElement *pElement=g_pHead;pElement;pElement=pElement->m_pNext)
	{
		printf("Element: %d\n", uiCount++);
		printf("\tNode\n");
	}
}

linkedListElement* createNewElement(int data)
{
	linkedListElement *pElement=new linkedListElement;

	pElement->m_pLast=0;
	pElement->m_pNext=0;

	// initialise data
	pElement->m_ipData = &data;

	return pElement;
}

linkedListElement* deleteElement(linkedListElement *pElement)
{
	linkedListElement *pE=pElement;

	if(pE)
	{
		// Don't think I need to set the pointer if we're setting the stuct to null?
		// remove from list
		//remove(pE);

		// may also want to clean up data
		delete pE;
		pE=0;
	}

	return pE;
}

void pushHead(linkedListElement *pElement)
{
	if (pElement && !isInList(pElement)) {
		if (g_pHead) {
			g_pHead->m_pLast = pElement;
			pElement->m_pNext = g_pHead;
			g_pHead = pElement;
		} else {
			g_pHead = g_pTail = pElement;
		}
	}
}

bool isInList(linkedListElement *pElement)
{
	return pElement == g_pHead ||
		(pElement->m_pNext || pElement->m_pLast);
}

void pushTail(linkedListElement *pElement)
{
	if (pElement && !isInList(pElement)) {
		if (g_pTail) {
			g_pTail->m_pNext = pElement;
			pElement->m_pLast = g_pTail;
			g_pTail = pElement;
		} else {
			g_pHead = g_pTail = pElement;
		}
	}
}


linkedListElement* popHead()
{
	linkedListElement *pElement = g_pHead;

	if (pElement) { // Check if any elements in list (g_pHead == 0)
		if (pElement == g_pTail) { // Check is element tail? (1 item list)
			g_pHead = g_pTail = 0;

			return pElement;
		} else { // multi-item list
			g_pHead = g_pHead->m_pNext; // set list head to next element

			g_pHead->m_pLast = pElement->m_pNext = 0; // break links

			return pElement;
		}
	}

	return 0;
}

linkedListElement* popTail()
{
	linkedListElement *pElement = g_pTail;

	if (pElement) {
		if (pElement == g_pHead) {
			g_pHead = g_pTail = 0;

			return pElement;
		}
		else {
			g_pTail = g_pTail->m_pNext;

			g_pTail->m_pNext = pElement->m_pLast = 0;

			return pElement;
		}
	}

	return 0;
}