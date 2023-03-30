#pragma once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <iomanip>

template <typename T>
struct ListNode
{
	T Data;
	ListNode* Next;
};

template <typename T>
class LinkedList
{
private:
	ListNode<T>* _head = nullptr;
public:
	LinkedList();
	~LinkedList();
	ListNode<T>* MakeNode(T data);
	ListNode<T>* MakeNode(ListNode<T>** head, T data);
	ListNode<T>* InsertFirst(T data);
	ListNode<T>* InsertFirst(ListNode<T>** head, T data);

	void InsertAfter(ListNode<T>* lastNode, T data);
	void DeleteList();
	void DeleteList(ListNode<T>** node);
	void DeleteAfter(ListNode<T>* node);
	void DeleteAt(ListNode<T>** node, int pos);
	ListNode<T>* GetNode(int pos);
	ListNode<T>* GetNode(ListNode<T>* node, int pos);
	ListNode<T>* Find(ListNode<T>* node, int val);
	void PrintList(ListNode<T>* node);
};

#endif