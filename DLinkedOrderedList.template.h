//Ali Jilani 250791966
//#include "DLinkedOrderedList.h"
//#include <stddef.h>
#ifndef Assert
#include <stdio.h>
#ifndef _DEBUG
#define Assert(expr,msg) 
#else
#define Assert(expr,msg) { if (expr) { } else { printf("ASSERT(%s) FAILED:\n    %s\n", #expr, msg); __asm { int 0x3 } } }
#endif
#endif

//Creating Empty Doubly Linked Ordered List
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::DLinkedOrderedList()
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
}

//Copy Constructor of Doubly Linked Ordered List
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::DLinkedOrderedList(DLinkedOrderedList<Item, Order> const& copy)
{	
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
	for (Node* newNode = copy.m_head; newNode != NULL; newNode = newNode->next)
	{
		insert(newNode->value);
	}
}

//Destructor for Doubly Linked Ordered List
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::~DLinkedOrderedList()
{
	Node * here = m_head;
	Node *nextNode;
	while (here != NULL)
	{
		nextNode = here->next;
		delete here;
		here = nextNode;
	}
}

//Size finding function
template <class Item, class Order>
unsigned int DLinkedOrderedList<Item, Order>::size() const
{
	return m_size;
}

//Checker to see if Doubly Linked Ordered List is empty
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order>::isEmpty() const
{
	return m_size == 0;
}

//Function that guides the iterator to the beginning of the Doubly Linked Ordered List (based on Direction)
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator DLinkedOrderedList<Item, Order>::begin(Direction direction)
{
	if (direction == FORWARD) 
	{
		return Iterator(m_head, *this, direction);
	}
	else
	{
		return Iterator(m_tail, *this, direction);
	}
}

//Function guides the iterator to the end of the Doubly Linked Ordered List
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator DLinkedOrderedList<Item, Order>::end(Direction direction)
{
	return Iterator(NULL, *this, direction);
}

//Insert item into the Doubly Linked Ordered List, and have it ordered correctly
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator DLinkedOrderedList<Item, Order>::insert(Item item)
{
	//Check if the List being inserted into is Empty
	if (isEmpty())
	{
		m_head = new Node(item, NULL, NULL);
		m_tail = new Node(item, NULL, NULL);
		m_size++;
		return this->begin();
	}

	//If the List has 1 Item
	else if (m_size == 1)
	{
		if (Order::compare(item, m_head->value)) //Compare to see where it needs to be placed
		{
			m_head = new Node(item, m_tail, NULL);
			m_tail->prev = m_head;
			m_size++;
			return this->begin();
		}

		else //make it the head of the list
		{
			m_tail = new Node(item, NULL, m_head);
			m_head->next = m_tail;
			m_size++;
			return this->end();
		}
	}

	else //if the size is greater than 1
	{
		Iterator r = this->begin(); //r is used out of the scope of the loop

		for (r; r != this->end(); ++r)
		{
			if (Order::compare(item, *r)) break; //find where to put the inserted value
		}

		if (r.m_node == m_head) // If it belongs at the front
		{
			m_head = new Node(item, r.m_node, NULL);
			(r.m_node)->prev = m_head;
			m_size++;

			return this->begin();
		}

		else if (r.m_node == NULL) // If it belongs at the back
		{
			r.m_node = m_tail;
			m_tail = new Node(item, NULL, r.m_node);
			(r.m_node)->next = m_tail;
			m_size++;

			return this->end();
		}

		else // if it belongs in the middle
		{

			Iterator y = r;
			((--r).m_node)->next = new Node(item, y.m_node, (y.m_node)->prev);
			(y.m_node)->prev = (r.m_node)->next;
			m_size++;

			return y;
		}
	}
}

//Remove an Item, return true if the item is found in the list
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order>::remove(Item item)
{
	for (Iterator w = this->begin(); w != this->end(); ++w) // Search through the list
	{
		if (*w == item) // If you find it
		{
			Iterator temp1 = w, temp = w;
			if (w.m_node == m_head && m_head == m_tail) // if its the only item in the list
			{
				delete w.m_node;
				m_head = m_tail = NULL;
				m_size--;
			}
			else if (w.m_node == m_head) // if its the head of the list
			{
				(++temp1).m_node->prev = NULL;
				m_head = temp1.m_node;
				delete temp.m_node;
				m_size--;
			}
			else if (w.m_node == m_tail) // if its the tail of the list
			{
				(--temp1).m_node->next = NULL;
				m_tail = temp1.m_node;
				delete temp.m_node;
				m_size--;
			}
			else // if its in the middle
			{
				((--temp1).m_node)->next = (temp.m_node)->next;
				temp1.m_node = temp.m_node;
				((++temp1).m_node)->prev = (temp.m_node)->prev;
				delete temp.m_node;
				m_size--;
			}

			return 1;
		}
	}

	return 0;
}

//Remove the Node 'itr' is pointing to, whilst returning the Item
template <class Item, class Order>
Item DLinkedOrderedList<Item, Order>::remove(Iterator& itr)
{

	bool find = 0;
	Iterator q = this->begin();
	for (q; q != this->end(); ++q) // search the list
	{
		if (q.m_node == itr.m_node) // when you find it
		{
			find = 1;
			break;
		}
	}

	Assert((find == 1), "[NOT A VALID POSITION]");

	Item newItem = (q.m_node)->value; //make the new item
	remove(newItem);
	return newItem;

}

//Remove all 'item' valued Items in the list, return num of items removed.
template <class Item, class Order>
unsigned int DLinkedOrderedList<Item, Order>::removeAll(Item item)
{
	unsigned i = 0;
	for (Iterator t = this->begin(); t != this->end(); ++t) //search through the list
	{
		if (*t == item) // when you find the item
		{
			Iterator quick = t;
			Iterator quick1 = t;

			if (t.m_node == m_head && m_head == m_tail) // if item is the only item in the list
			{
				delete t.m_node;
				m_head = m_tail = NULL;
				m_size--;
				i++;
			}

			else if (t.m_node == m_head) // if its the front of the list
			{
				(++quick).m_node->prev = NULL;
				m_head = quick1.m_node;
				delete quick1.m_node;
				t.m_node = m_head;
				m_size--;
				i++;
			}

			else if (t.m_node == m_tail) // if its the end of the list
			{
				(--quick).m_node->next = NULL;
				m_tail = quick1.m_node;
				--t;
				delete quick1.m_node;
				m_size--;
				i++;
			}

			else // if its in the middle
			{
				((--quick).m_node)->next = (quick1.m_node)->next;
				quick.m_node = quick1.m_node;
				((++quick).m_node)->prev = (quick1.m_node)->prev;
				--t;
				delete quick1.m_node;
				m_size--;
				i++;
			}
		}
	}
	return i;

}
