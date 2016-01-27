#include "DLinkedOrderedList.h"
#include "StandardFunctors.h"
#include <iostream>

using namespace std;

int main() 
{
	DLinkedOrderedList<int, IsLess> a;

	//"For example, if object DLinkedOrderedList<int, IsLess> a; contains integers {3,5,6,9,12,19}"
	a.insert(19);
	a.insert(12);
	a.insert(9);
	a.insert(3);
	a.insert(6);
	a.insert(5);
	
	
	//"the for-loop should print out 3 5 6 9 12 19 on the console"
	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(); k != a.end(); ++k)
	{
		cout << *k << " ";
	}
	//cout << *k << " ";

	cout << endl;

	//"the for-loop should generate output 19 12 9 6 5 3 on the console."
	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(BACKWARD); k != a.end(BACKWARD); ++k)
	{
		cout << *k << " ";	}	cout << endl;	cout << "Size of the List: " << a.size() << endl; //List size function	cout << "Is the List Empty?: " << a.isEmpty() << endl; //List Empty function

	a.remove(9); // Testing the Remove function
	cout << "Remove 9 " << endl;

	//"the for-loop should print out 3 5 6 12 19 on the console"
	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(); k != a.end(); ++k)
	{
		cout << *k << " ";
	}

	cout << endl;

	cout << "Try removing '24'" << endl;
	a.remove(24);// Testing removing something that isn't in the List

	//"the for-loop should print out 3 5 6 12 19 on the console"
	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(); k != a.end(); ++k)
	{
		cout << *k << " ";
	}

	cout << endl;

	cout << "Insert 4,4,4, and then use the removeAll function" << endl;
	a.insert(4);
	a.insert(4);
	a.insert(4);

	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(); k != a.end(); ++k)
	{
		cout << *k << " ";
	}
	cout << endl;
	a.removeAll(4); //Using the Remove all function

	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(); k != a.end(); ++k)
	{
		cout << *k << " ";
	}
	cout << endl;

	//Iterator based functions
	DLinkedOrderedList<int, IsLess>::Iterator t = a.begin();
	++t;
	++t;
	cout << "Remove: " << a.remove(t) << endl;

	DLinkedOrderedList<int, IsLess>::Iterator y = a.begin();
	++y;
	++y;
	//Iterator decrement test
	--y;
	cout << "Kill: " << y.kill() << endl;

	cout << "The final List: ";
	for (DLinkedOrderedList<int, IsLess>::Iterator k = a.begin(); k != a.end(); ++k)
	{
		cout << *k << " ";
	}
	cout << endl;
	
	cout << "Copy Constructor create List 'b' with 'a'" << endl;
	DLinkedOrderedList<int, IsLess> b = DLinkedOrderedList<int, IsLess>(a);
	for (DLinkedOrderedList<int, IsLess>::Iterator k = b.begin(); k != b.end(); ++k)
	{
		cout << *k << " ";
	}
	cout << endl;

}