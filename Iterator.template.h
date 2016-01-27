//Ali Jilani 250791966
//#include "DLinkedOrderedList.h"
//#include <stddef.h>

template <class Item, class Order>
DLinkedOrderedList<Item, Order>::Iterator::Iterator(Node* const node, DLinkedOrderedList<Item, Order>& list, Direction direction = FORWARD) : m_list(list)
{
	m_node = node;
	m_list = list;
	m_direction = direction;
}

template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator& DLinkedOrderedList<Item, Order>::Iterator::operator++()
{
	Assert(m_node != NULL, "[m_node == NULL]"); // precondition

	if (m_direction == FORWARD) 
	{
		m_node = m_node->next;
	}

	else 
	{
		m_node = m_node->prev;
	}

	return *this;
}

template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator& DLinkedOrderedList<Item, Order>::Iterator::operator--()
{
	Assert(m_node != NULL, "[m_node == NULL]"); // precondtion

	if (m_direction == FORWARD) 
	{
		m_node = m_node->prev;
	}

	else 
	{
		m_node = m_node->next;
	}

	return *this;
}

template <class Item, class Order>
bool DLinkedOrderedList<Item, Order>::Iterator::operator!=(Iterator const& b) const
{
	return m_node != b.m_node;
}

template <class Item, class Order>
Item& DLinkedOrderedList<Item, Order>::Iterator::operator*() const
{
	Assert(m_node != NULL, "m_node is NULL (in Operator*)");

	return m_node->value;
}

template <class Item, class Order>
Item DLinkedOrderedList<Item, Order>::Iterator::kill()
{
	return m_list.remove(*this);
}

