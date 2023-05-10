#pragma once
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList() = default;

template <typename T>
LinkedList<T>::~LinkedList() = default;

template <typename T>
ListNode<T>* LinkedList<T>::MakeNode(T data)
{
	ListNode<T>* newNode = new ListNode<T>;
	ListNode<T>* last = _head;

	newNode->Data = data;
	newNode->Next= nullptr;

	if (_head == nullptr)
	{
		_head = newNode;
		return newNode;
	}

	while (last->Next!= nullptr)
	{
		last = last->Next;
	}
	last->Next= newNode;
	return newNode;
}

template <typename T>
ListNode<T>* LinkedList<T>::MakeNode(ListNode<T>** head, T data)
{
	ListNode<T>* newNode = new ListNode<T>;
	ListNode<T>* last = *head;

	newNode->Data = data;
	newNode->Next= nullptr;

	if (*head == nullptr)
	{
		*head = newNode;
		_head = newNode;
		return newNode;
	}

	while (last->Next!= nullptr)
	{
		last = last->next;
	}
	last->Next= newNode;
	return newNode;
}

template <typename T>
ListNode<T>* LinkedList<T>::InsertFirst(T data)
{
	ListNode<T>* newNode = new ListNode<T>;

	newNode->Data = data;
	newNode->Next = _head;
	_head = newNode;

	return newNode;
}

template <typename T>
ListNode<T>* LinkedList<T>::InsertFirst(ListNode<T>** head, T data)
{
	ListNode<T>* newNode = new ListNode<T>;

	newNode->Data = data;
	newNode->Next= *head;
	*head = newNode;
	_head = newNode;

	return newNode;
}

template <typename T>
void LinkedList<T>::InsertAfter(ListNode<T>* lastNode, T data)
{
	ListNode<T>* newNode = new ListNode<T>;

	newNode->Data = data;
	newNode->Next = lastNode->Next;

	lastNode->Next = newNode;
}

template <typename T>
void LinkedList<T>::DeleteList()
{
	ListNode<T>* pTemp = _head;

	while (pTemp != nullptr)
	{
		ListNode<T>* next = pTemp->Next;
		delete pTemp;
		pTemp = next;
	}

	_head = nullptr;
}

template <typename T>
void LinkedList<T>::DeleteList(ListNode<T>** node)
{
	ListNode<T>* pTemp = *node;

	while (pTemp != nullptr)
	{
		ListNode<T>* next = pTemp->Next;
		delete pTemp;
		pTemp = next;
	}

	*node = nullptr;
}

template <typename T>
void LinkedList<T>::DeleteAfter(ListNode<T>* node)
{
	if (node != nullptr && node->Next!= nullptr)
	{
		ListNode<T>* pTemp = node->Next;
		node->Next = pTemp->Next;

		delete pTemp;
	}
}

template <typename T>
void LinkedList<T>::DeleteAt(ListNode<T>** node, int pos)
{
	ListNode<T>* nodeToDelete = GetNode(*node, pos);

	if (pos == 0)
	{
		*node = nodeToDelete->Next;
		_head = *node;
		delete nodeToDelete;
		return;
	}
	
	ListNode<T>* parentNode = GetNode(*node, pos - 1);
	parentNode->Next = nodeToDelete->Next;
	delete nodeToDelete;
}

template <typename T>
void LinkedList<T>::DeleteAt(int pos)
{
	ListNode<T>* nodeToDelete = GetNode(pos);
	if (pos == 0 && _head != nullptr
		)
	{
		_head = nodeToDelete->Next;
		delete nodeToDelete;
		return;
	}

	ListNode<T>* parentNode = GetNode(pos - 1);
	parentNode->Next = nodeToDelete->Next;
	delete nodeToDelete;
}


template <typename T>
ListNode<T>* LinkedList<T>::GetNode(int pos)
{
	if (pos == 0)
		return _head;

	ListNode<T>* node = _head;

	int count = 0;
	while (node != nullptr)
	{
		if (count == pos)
		{
			//std::cout << "Data stored at position " << pos << " is: " << node->Data << std::endl;
			return node;
		}
		count++;
		node = node->Next;
	}

	return nullptr;
}

template <typename T>
ListNode<T>* LinkedList<T>::GetNode(ListNode<T>* node, int pos)
{
	int count = 0;
	while (node != nullptr)
	{
		if (count == pos)
		{
			//std::cout << "Data stored at position " << pos << " is: " << node->Data << std::endl;
			return node;
		}
		count++;
		node = node->Next;
	}

	return nullptr;
}

template <typename T>
ListNode<T>* LinkedList<T>::GetLastNode()
{
	ListNode<T>* tempNode = GetNode(0);

	while (tempNode != nullptr)
	{
		if (tempNode->Next == nullptr)
			return tempNode;

		tempNode = tempNode->Next;
	}

	return nullptr;
}

template <typename T>
ListNode<T>* LinkedList<T>::Find(ListNode<T>* node, T val)
{
	ListNode<T>* pTemp = node->Next;

	while (pTemp->Next!= nullptr && pTemp->Data != val)
	{
		pTemp = pTemp->Next;
	}

	return pTemp;
}

template <typename T>
int LinkedList<T>::GetIndex(ListNode<T>* node)
{
	ListNode<T>* tempNode = _head;
	int index = 0;
	while (tempNode != nullptr)
	{
		if (tempNode == node)
		{
			return index;
		}
		index++;
		tempNode = tempNode->Next;
	}
}


template <typename T>
void LinkedList<T>::PrintList(ListNode<T>* node)
{
	while (node != nullptr)
	{
		std::cout << std::setw(5) << "| " << node->Data << " |-->";
		node = node->Next;

		if (node == nullptr)
		{
			std::cout << "| NULL |" << std::endl;
		}

		std::cout << std::endl;
	}
}

#endif