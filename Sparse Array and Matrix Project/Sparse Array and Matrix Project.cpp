#include<iostream>
using namespace std;

struct Node // struct for the ArrayLinkedList
{
	int data{};
	int index{};
	Node* next{};
	Node* prev{};

	Node(int data,int index):data(data),index(index){}
};

class ArrayLinkedList // in case of 1D Array
{
private:
	int array_size{};
	int ll_size{};
	Node* head{};
	Node* tail{};

	void insert_before(Node* node1, Node* node2) //O(1)time O(1)memory
	{
		Node* prev = node1->prev;
		node2->prev = prev;
		node2->next = node1;
		node1->prev = node2;

		if (prev)
			prev->next = node2;
		
		if (node1 == head)
			head = node2;

		ll_size++;
	}

	void insert(Node* node) //O(n)time O(1)memory
	{
		for (Node* selector = head; selector; selector = selector->next)
		{
			if (node->index < selector->index)
			{
				insert_before(selector, node);
				return;
			}
			else if (node->index == selector->index)
			{
				selector->data = node->data;
				return;
			}
		}
		insert_back(node);
	}

	void insert_back(Node* node) //O(1)time O(1)memory
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
		ll_size++;
	}

public:
	ArrayLinkedList(int array_size):array_size(array_size){}

	Node* get_head()
	{
		return head;
	}

	void link(Node* node1, Node* node2) //O(1)time O(1)memory
	{
		Node* prev = node1->prev;
		node2->prev = prev;
		node2->next = node1;
		node1->prev = node2;
		if (prev)
			prev->next = node2;
	}

	void set_value(int data, int index) //O(n)time O(1)memory
	{
		if (index >= array_size||index<0)
			return;

		Node* node = new Node(data, index);

		if (ll_size == 0)
		{
			head = tail = node;
			ll_size++;
			return;
		}
		else
			insert(node);
		
	}

	int get_value(int index) //O(n)time O(1)memory
	{
		if (index >= array_size || index < 0)
			return 0;

		for (Node* node = head; node; node = node->next)
		{
			if (node->index == index)
			{
				return node->data;
			}
		}

		return 0;
	}

	void print_array() //O(n)time O(1)memory
	{
		Node* node = head;

		cout << "Array view:\n";
		for (int i = 0; i < array_size; i++)
		{
			if (node && node->index == i)
			{
				cout << node->data << " ";
				node = node->next;
			}
			else
				cout << "0 ";
		}
		cout << "\n---------------------------------\n";
	}

	void print_array_nonzero() //O(n)time O(1)memory
	{
		cout << "Doubly Linked List view:\n";
		cout << "null <- ";
		for (Node* node = head; node; node = node->next)
		{
			cout << node->data;
			if (node->next)
				cout << " <-> ";
		}
		cout << " -> null\n---------------------------------\n";
	}

	void add(ArrayLinkedList& other) //O(n+m)time O(1)memory
	{
		if (other.array_size != array_size)
			return;

		Node* node1 = head;
		Node* node2 = other.head;


		for (int i = 0; i < array_size; i++)
		{
			if (!node2)
				return;
			else if (node1 && node2 && i == node1->index && i == node2->index)
			{
				node1->data += node2->data;
				node1 = node1->next;
				node2 = node2->next;
			}
			else if(node2->index==i)
			{
				Node* node = new Node  (node2->data, node2->index);
				insert(node);
				node2 = node2->next;
			}
		}
	}
};

//----------------------------------------NEXT IS The Matrix----------------------------------------

struct TwoDimNode // struct for the TwoDimArrayLinkedList
{
	int index{};
	TwoDimNode* next{};
	TwoDimNode* prev{};
	ArrayLinkedList* arr{};

	TwoDimNode(int row, int col) :index(row)
	{
		arr = new ArrayLinkedList(col);
	}
};

class TwoDimArrayLinkedList // in case of 2D Array
{
private:
	TwoDimNode* head{};
	TwoDimNode* tail{};
	int length{};
	int rows{}, columns{};

	void insert_before(TwoDimNode* node1, TwoDimNode* node2) // O(1)time O(1)memory
	{
		TwoDimNode* prev = node1->prev;
		node2->prev = prev;
		node2->next = node1;
		node1->prev = node2;

		if (prev)
			prev->next = node2;

		if (node1 == head)
			head = node2;

		length++;
	}

	void insert_back(TwoDimNode* node) // O(1)time O(1)memory
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
		length++;
	}

public:
	TwoDimArrayLinkedList(int row,int column):rows(row),columns(column){}

	void set_value(int data, int row, int column) // O(n)time O(1)memory
	{
		if (row >= rows || row < 0 || column >= columns || column < 0)
			return;

		if (length == 0)
		{
			TwoDimNode* node = new TwoDimNode(row, columns);
			node->arr->set_value(data, column);
			head = tail = node;
			length++;
			return;
		}
		else
		{
			for (TwoDimNode* selector = head; selector; selector = selector->next)
			{
				if (row < selector->index)
				{
					TwoDimNode* node = new TwoDimNode(row, columns);
					node->arr->set_value(data, column);
					insert_before(selector,node);
					return;
				}
				else if (row == selector->index)
				{
					selector->arr->set_value(data, column);
					return;
				}
			}

			TwoDimNode* node = new TwoDimNode(row, columns);
			node->arr->set_value(data, column);
			insert_back(node);
		}
	}

	int get_value(int row, int column) // O(n)time O(1)memory
	{
		if (row >= rows || row < 0 || column >= columns || column < 0)
			return 0;

		for (TwoDimNode* node1 = head; node1; node1 = node1->next)
		{
			if (node1->index == row)
			{
				for (Node* node2 = node1->arr->get_head(); node2; node2 = node2->next)
				{
					if (node2->index == column)
						return node2->data;
				}
			}
		}

		return 0;
	}

	void print() //O(N)time O(1)memory
	{
		TwoDimNode* node1 = head;

		cout << "Matrix view:\n";
		for (int i = 0; i < rows; i++)
		{
			Node* node2{};
			if (node1)
				node2 = node1->arr->get_head();

			cout << "row:" << i << "  ";
			for (int j = 0; j < columns; j++)
			{
				if (node1 && node2 && node1->index == i && node2->index == j)
				{
					cout << node2->data << " ";
					node2 = node2->next;
				}
				else
				{
					cout << "0 ";
				}
			}
			if (node1&& node1->index == i && node1->next)
				node1 = node1->next;
			cout << "\n";
		}
		cout << "---------------------------------\n";
	}

	void print_none_zero() // O(n)time O(1)memory
	{
		cout << "Doubly Linked List view:\n";
		for (TwoDimNode* node1 = head; node1; node1 = node1->next)
		{
			cout << "row:"<<node1->index<<"  null <- ";
			for (Node* node2 = node1->arr->get_head(); node2; node2 = node2->next)
			{
				cout<<node2->data;
				if (node2->next)
					cout << " <-> ";
			}
			cout << " -> null\n";
		}
		cout << "---------------------------------\n";
	}

	void add(TwoDimArrayLinkedList& other)
	{
		if (other.rows != rows || other.columns != columns)
			return;

		TwoDimNode* node1 = head;
		TwoDimNode* node2 = other.head;

		for (int i = 0; i < rows; i++)
		{
			if (!node2)
				return;

			if (node1 && node2 && node1->index == i && node2->index == i)
			{
				node1->arr->add(*(node2->arr));
				node1 = node1->next;
				node2 = node2->next;
			}
			else if (node2->index == i)
			{
				set_value(0, i, node2->arr->get_head()->index);

				if (node1 && node1->prev->index == i)
					node1 = node1->prev;
				else if (node1 && node1->next->index == i)
					node1 = node1->next;
				else
					node1 = tail;
				
				node1->arr->add(*(node2->arr));
				node1 = node1->next;
				node2 = node2->next;
			}
			
		}
	}
};

void test()
{
	/*ArrayLinkedList arr1(10);
	ArrayLinkedList arr2(10);

	arr1.set_value(10, 0);
	arr1.set_value(20, 1);
	arr1.set_value(30, 2);
	arr1.set_value(30, 10);

	arr1.print_array();
	arr1.print_array_nonzero();

	cout << arr1.get_value(0)<<" ";
	cout << arr1.get_value(1)<<" ";
	cout << arr1.get_value(2)<<" ";
	cout << arr1.get_value(3)<<" ";

	arr2.set_value(10, 0);
	arr2.set_value(20, 1);
	arr2.set_value(30, 2);
	arr2.set_value(40, 3);
	arr2.set_value(50, 4);

	arr2.print_array();
	arr2.print_array_nonzero();
	
	arr1.add(arr2);
	arr1.print_array();
	arr1.print_array_nonzero();

	arr2.print_array();
	arr2.print_array_nonzero();

	arr2.set_value(5, 4);
	arr2.print_array();
	arr2.print_array_nonzero();

	cout << arr2.get_value(10);*/

	TwoDimArrayLinkedList matrix(10, 10);
	matrix.set_value(5, 5, 5);
	matrix.set_value(4, 5, 5);
	matrix.set_value(5, 1, 5);
	matrix.set_value(5, 2, 5);
	matrix.set_value(5, 5, 6);
	matrix.print_none_zero();
	matrix.print();

	TwoDimArrayLinkedList matrix2(10, 10);
	matrix2.set_value(6, 6, 6);
	matrix2.set_value(5, 6, 6);
	matrix2.set_value(3, 3, 6);
	matrix2.set_value(4, 1, 5);
	matrix2.set_value(4, 2, 5);
	matrix2.set_value(6, 6, 7);
	matrix2.set_value(6, 7, 7);
	matrix2.print_none_zero();
	matrix2.print();

	matrix.add(matrix2);
	matrix.print();
	matrix.print_none_zero();
}

int main(void)
{
	test();

	return 0;
}