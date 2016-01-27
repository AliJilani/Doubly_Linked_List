//Ali Jilani 250791966

template <class Item, class Order>
DLinkedOrderedList<Item, Order>::Node::Node(Item val, Node* _next, Node* _prev)
{
	value = val;
	next = _next;
	prev = _prev;
}