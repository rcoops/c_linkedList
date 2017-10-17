// raaSimpleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>

struct linkedListElement
{
	linkedListElement *m_pNext;
	linkedListElement *m_pLast;
	int m_iData;
};

typedef enum { HEAD, TAIL } end; // Defining constants would be better

linkedListElement *g_pHead = 0;
linkedListElement *g_pTail = 0;
int g_iSize = 0;

void printList();

bool isInList(linkedListElement *pElement);

linkedListElement* createNewElement(int data);

void pushHead(linkedListElement *pElement);
void pushTail(linkedListElement *pElement);
void insertBefore(linkedListElement *pElement, linkedListElement *pTarget);
void insertAfter(linkedListElement *pElement, linkedListElement *pTarget);

linkedListElement* deleteElement(linkedListElement *pElement);

linkedListElement* popHead();
linkedListElement* popTail();

void pushAndPrintNewElement(linkedListElement *pElement, int data, end endToPush);
void createAndPushElement(linkedListElement *pElement, int data, end endToPush);
void printElement(linkedListElement *pElement, int uiCount);

int main(char* args[])
{
	linkedListElement *pElement=0;

	pushAndPrintNewElement(pElement, 4, HEAD);

	pushAndPrintNewElement(pElement, 2, TAIL);

	pushAndPrintNewElement(pElement, 8, HEAD);

	pushAndPrintNewElement(pElement, 5, HEAD);

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\nDeleting head by popping\n~~~~~~~~~~~~~~~~~~~~~~~~\n");
	delete popHead();
	printList();

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\nDeleting tail by popping\n~~~~~~~~~~~~~~~~~~~~~~~~\n");
	delete popTail();
	printList();

	printf("\n~~~~~~~~~~~~~~~~~~~~~~\nPushing tail onto head\n~~~~~~~~~~~~~~~~~~~~~~\n");
	pushHead(popTail());
	printList();

	pushAndPrintNewElement(pElement, 3, HEAD);

	printf("\n~~~~~~~~~~~~~~~~~~~~~~\nPushing head onto tail\n~~~~~~~~~~~~~~~~~~~~~~\n");
	pushTail(popHead());
	printList();

	linkedListElement *newElement = createNewElement(9);
	
	_getch();
	return 0;
}

linkedListElement* getAt(int index) {
	if (g_iSize - 1 >= index) {
		linkedListElement *pCurrentElement = g_pHead;
		for (int i = 0; i < index; i++) {
			pCurrentElement = pCurrentElement->m_pNext;
		}
		return pCurrentElement;
	}
	return 0;
}

void pushAndPrintNewElement(linkedListElement *pElement, int data, end endToPush) {
	char *headOrTail = endToPush == HEAD ? "HEAD" : "TAIL";
	printf("\nAdding %d to %s\n~~~~~~~~~~~~~~~~\n", data, headOrTail);

	createAndPushElement(pElement, data, endToPush);
	
	printList();
}

void createAndPushElement(linkedListElement *pElement, int data, end endToPush) {
	pElement = createNewElement(data);

	endToPush == HEAD ? pushHead(pElement) : pushTail(pElement);
}

void printList()
{
	int uiCount=0;
	int *puiCount = &uiCount;
	printf("        NULL\n");
	printf("         ^\n");
	printf("         |\n");
	for(linkedListElement *pElement=g_pHead;pElement;pElement=pElement->m_pNext) {
		printElement(pElement, uiCount++);
	}
	printf("         |\n");
	printf("         v\n");
	printf("        NULL\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");
}

void printElement(linkedListElement *pElement, int uiCount) {
	printf(" ------------------\n");
	printf("| Element:   %d     |\n", uiCount); // single digits =(
	printf("|------------------|\n");
	printf("| Node: %d   |\n", pElement);
	printf("| Data:      %d     |\n", pElement->m_iData);
	printf(" ------------------\n");
}

linkedListElement* createNewElement(int data)
{
	linkedListElement *pElement=new linkedListElement;

	pElement->m_pLast=0;
	pElement->m_pNext=0;

	// initialise data
	pElement->m_iData = data;

	return pElement;
}

linkedListElement* deleteElement(linkedListElement *pElement)
{
	linkedListElement *pE=pElement;

	if(pE)
	{
		// Don't think I need to set the pointer if we're setting the stuct to null?
		// remove from list
		if (isInList(pE)) {
			return 0;
			//remove(pE);
		}
		// may also want to clean up data
		delete pE;
		pE=0;
	}

	return pE;
}

bool isInList(linkedListElement *pElement)
{
	return pElement == g_pHead
		|| (pElement->m_pNext || pElement->m_pLast)
		|| pElement == g_pTail;
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
		g_iSize++;
	}
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
		g_iSize++;
	}
}

void insertBefore(linkedListElement *pElement, linkedListElement *pTarget) {
	// check if element & target exist
	if (!isInList(pElement) && isInList(pTarget)) {
		if (pTarget == g_pHead) {
			pushHead(pElement);
		}else {
			// Add new additional link between the target and last
			pElement->m_pLast = pTarget->m_pLast; 
			pElement->m_pNext = pTarget;

			// Point target's last's next and target's last at elemet
			pTarget->m_pLast = pTarget->m_pLast->m_pNext = pElement;

			g_iSize++; // increment size
		}
	}
}

void insertAfter(linkedListElement *pElement, linkedListElement *pTarget) {
	// check if element & target exist
	if (!isInList(pElement) && isInList(pTarget)) {
		if (pTarget == g_pTail) {
			pushTail(pElement);
		} else {
			// Add new additional link between the target and last
			pElement->m_pNext = pTarget->m_pNext;
			pElement->m_pLast = pTarget;

			// Point target's last's next and target's last at elemet
			pTarget->m_pNext = pTarget->m_pNext->m_pLast = pElement;

			g_iSize++; // increment size
		}
	}
}

linkedListElement* popHead()
{
	linkedListElement *pElement = g_pHead;

	if (pElement) { // Check if any elements in list (g_pHead == 0)
		if (pElement == g_pTail) { // Check is element tail? (1 item list)
			g_pHead = g_pTail = 0;  // Set globals to null

			return pElement;
		} else { // multi-item list
			g_pHead = g_pHead->m_pNext; // set list head to next element
			g_pHead->m_pLast = pElement->m_pNext = 0; // break links

			return pElement;
		}

		g_iSize--;
	}

	return 0;
}

linkedListElement* popTail()
{
	linkedListElement *pElement = g_pTail;

	if (pElement) {  // Check if any elements in list (g_pHead == 0)
		if (pElement == g_pHead) { // Check is element head? (1 item list)
			g_pHead = g_pTail = 0; // Set globals to null

			return pElement;
		}
		else {
			g_pTail = g_pTail->m_pLast; // set list tail to last element
			g_pTail->m_pNext = pElement->m_pLast = 0; // break links

			return pElement;
		}

		g_iSize--;
	}

	return 0;
}

void remove(linkedListElement *pElement)
{
	if (pElement->m_pNext) {
		pElement->m_pNext->m_pLast = pElement->m_pLast;
	} else {
		g_pTail = pElement->m_pLast;
	}
	if (pElement->m_pLast) {
		pElement->m_pLast->m_pNext = pElement->m_pNext;
	} else {
		g_pHead = pElement->m_pNext;
	}

	g_iSize--;
}
