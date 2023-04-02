#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct List {
	NODE* p_head;
	NODE* p_tail;
};

NODE* createNode(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->p_next = NULL;
	return newNode;
}

void addHead(NODE*& pHead, int data)
{
	NODE* newNode = createNode(data);
	if (pHead == NULL)
	{
		pHead = newNode;
		return;
	}
	NODE* pCurr = pHead;
	pHead = newNode;
	pHead->p_next = pCurr;
}

void printList(NODE*& pHead)
{
	NODE* pCurr = pHead;
	if (pHead == NULL) return;
	while (pCurr != NULL)
	{
		cout << pCurr->key << " ";
		pCurr = pCurr->p_next;
	}
	cout << "\n";
}

void addTail(NODE*& pHead, int data)
{
	if (pHead == NULL) addHead(pHead, data);
	else
	{
		NODE* pCurr = pHead;
		while (pCurr->p_next != NULL)
		{
			pCurr = pCurr->p_next;
		}
		pCurr->p_next = createNode(data);
	}
}

void removeHead(NODE*& pHead)
{
	if (pHead == NULL) return;
	else
	{
		NODE* pCurr = pHead;
		pCurr = pCurr->p_next;
		delete pHead;
		pHead = pCurr;
	}
}

void removeTail(NODE*& pHead)
{
	if (pHead == NULL) return;
	else
	{
		NODE* pre = NULL;
		NODE* Tail = pHead;

		if (pHead->p_next == NULL)
		{
			delete pHead;
			pHead = NULL;
			return;
		}

		while (Tail->p_next != NULL)
		{
			pre = Tail;
			Tail = Tail->p_next;
		}
		delete Tail;
		pre->p_next = NULL;
	}
}

void removeAll(NODE*& pHead)
{
	if (pHead == NULL) return;
	else
	{
		while (pHead != NULL)
		{
			removeTail(pHead);
		}
	}
}

int findPos(NODE* pHead, int val) {
	int pos = -1;
	int n = 0;

	NODE* pCurrent = pHead;
	while (pCurrent != NULL) {
		if (pCurrent->key == val) {
			pos = n;
			break;
		}
		pCurrent = pCurrent->p_next;
		n++;
	}

	return pos;
}

void removeBefore(NODE*& pHead, int val) {
	NODE* pCurrent = pHead;
	if (pCurrent == NULL || pCurrent->p_next == NULL) {
		return;
	}

	// position of node needed to delete
	int pos = findPos(pHead, val) - 1;

	if (pos < 0) {
		return;
	}

	if (pos == 0) {
		removeHead(pHead);
		return;
	}

	for (int i = 0; i < pos - 1; i++) {
		pCurrent = pCurrent->p_next;
	}

	NODE* temp = pCurrent->p_next;
	pCurrent->p_next = temp->p_next;
	delete temp;
}

void removeAfter(NODE*& pHead, int val)
{
	if (pHead == NULL)
	{
		return;
	}
	NODE* current = pHead;
	while (current != NULL && current->key != val)
	{
		current = current->p_next;
	}
	if (current == NULL || current->p_next == NULL)
	{
		return;
	}
	NODE* temp = current->p_next;
	current->p_next = temp->p_next;
	delete temp;
}

void addPos(NODE* pHead, int data, int pos) {
	if (pos < 0)
		return;
	NODE* temp = new NODE;
	temp->key = data;
	temp->p_next = NULL;
	NODE* pCurr = pHead;
	for (int i = 0; i < pos - 1; i++) {
		pCurr = pCurr->p_next;
	}
	temp->p_next = pCurr->p_next;
	pCurr->p_next = temp;
}


void RemovePos(NODE*& pHead, int pos)
{

	NODE* pCur = pHead;

	int SizeList = 0;
	while (pCur != NULL)
	{
		SizeList++;
		pCur = pCur->p_next;
	}

	if (SizeList - 1 < pos) return;
	if (pos == 0)
	{
		removeHead(pHead);
		return;
	}
	if (pos == 1)
	{
		removeAfter(pHead, pHead->key);
		return;
	}

	pCur = pHead;
	while (pCur != NULL)
	{
		pos--;
		pCur = pCur->p_next;
		if (pos == 1) break;
	}

	NODE* temp = pCur->p_next->p_next;
	//cout<<pCur->key<<" "<<temp->key<<endl;
	delete pCur->p_next;
	pCur->p_next = temp;

}

void addBefore(NODE*& pHead, int data, int val)
{
	if (!pHead)
		return;

	NODE* pCur = pHead;
	NODE* pPrev = NULL;

	if (pHead->key == val)
	{
		addHead(pHead, data);
		pPrev = pCur;
		pCur = pCur->p_next;
	}

	while (pCur)
	{
		if (pCur->key == val)
		{
			addHead(pPrev->p_next, data);
		}
		pPrev = pCur;
		pCur = pCur->p_next;
	}
}

void addAfter(NODE*& pHead, int data, int val)
{
	NODE* current = pHead;
	NODE* afterCur = pHead->p_next;

	if (pHead == NULL)
	{
		return;
	}

	while (current->p_next != NULL)
	{
		if (current->key == val)
		{
			//cout<<afterCur->key;
			NODE* newNode = createNode(data);
			current->p_next = newNode;
			newNode->p_next = afterCur;
			//return;
			//printList(pHead);
		}

		else if (current->p_next == NULL)
		{
			addTail(pHead, data);
		}

		current = current->p_next;
		afterCur = current->p_next;
	}

}
int countAppearance(NODE*& pHead, int val)
{
	NODE* pCur = pHead;
	int count = 0;
	while (pCur != NULL)
	{
		if (pCur->key == val)
			count++;
		pCur = pCur->p_next;
	}
	return count;
}

NODE* reverseList(NODE*& pHead)
{
	NODE* newHead = NULL;
	NODE* pCur = pHead;
	while (pCur != NULL)
	{
		addHead(newHead, pCur->key);
		pCur = pCur->p_next;
	}
	return newHead;
}

int main()
{
	NODE* p = NULL;
	int data;
	int a[5] = { 1, 3, 3, 4, 5 };
	for (int i = 0; i < 5; i++)
	{
		addHead(p, a[i]);
	}
	
	printList(p);
	NODE* q = NULL;
	q = reverseList(p);
	printList(q);
}