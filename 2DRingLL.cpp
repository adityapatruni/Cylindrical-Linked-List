//March 8, 2020
#include <iostream>
#include <memory>
using namespace std;
template <typename T> class Node { //Your T has to support either int or float
public:
	shared_ptr<T> pValue; //pValue is a pointer to an object of type T
	shared_ptr<Node<T>> row_next;//Points to the next node in the same row
	shared_ptr<Node<T>> col_next;//Points to the nexe node in the same col
	Node() {}
	Node(T v) { pValue = make_shared<T>(v); }// pValue.reset(new T(v)); will also work,but slower
};

template <typename T> class Ring2D {
public:
	shared_ptr<Node<T>> head;//Points to the node at first row and first column
	Ring2D() {};


	Ring2D(const initializer_list<T>& I); //initializer_list
	~Ring2D();
	Ring2D(const Ring2D<T>& R);//copy constructor
	void operator=(const Ring2D<T>& R);//Lvalue operator=; copy assignment
	Ring2D(Ring2D<T>&& R);//move constructor
	void operator=(Ring2D<T>&& R);//Rvalue operator=; move assignment
	Ring2D<T> ThreeTimes();//Return a Ring2D with values being three times of the current Ring2D

	void DeleteRow(int r);//Delete row r of Ring2D
	//If r is out of range, simply do nothing and return.
};
template<typename T> Ring2D<T>::Ring2D(const initializer_list<T>& I) {
	auto i = I.begin();
	T rows = *(I.begin());
	T r = rows;
	i++;
	T columns = *(I.begin() + 1);
	T c = columns;
	i++;
	auto j = I.end() - 1;
	while (j != I.begin() + 1) {
		shared_ptr<Node<T>> newNode = make_shared<Node<T>>(*j);
		newNode->col_next = head;
		head = newNode;
		j--;
	}
	c = columns;
	r = rows;
	shared_ptr<Node<T>> cursor = head;
	shared_ptr<Node<T>> cursorR = head;
	shared_ptr<Node<T>> rowStart = head;
	while (1) {
		while (c > 1) {
			cursor = cursor->col_next;
			c--;
		}
		c = columns;
		if (cursor->col_next != nullptr) {
			rowStart->row_next = cursor->col_next;
			cursor->col_next = rowStart;
			rowStart = rowStart->row_next;
			cursor = rowStart;
		}
		else {
			cursor->col_next = rowStart;
			break;
		}
	}
	cursor = head;
	while (r > 1) {
		cursorR = cursor->row_next;	
		while (c > 1) {
			cursor = cursor->col_next;
			cursorR = cursorR->col_next;
			cursor->row_next = cursorR;
			c--;
		}
		cursor = cursor->col_next;
		cursor = cursor->row_next;	
		c = columns;
		r--;
		if (r == 1) {
			cursorR = head;
			if (cursor->row_next == nullptr) {
				while (c > 0) {
					cursor->row_next = cursorR;
					cursorR = cursorR->col_next;
					cursor = cursor->col_next;
					c--;
				}
			}
		}
	}
	cout << "Initializer_list" << endl;
}
template <typename T> Ring2D<T>::~Ring2D() { //Destructor
	if (!head) {
		cout << "Destrutor" << endl;
		return;
	}
	if (head) {
		shared_ptr<Node<T>> cursor = head;
		shared_ptr<Node<T>> rowStart = head;
		shared_ptr<Node<T>> colStart = head;
		while (1) {
			while (1) {
				if (cursor->col_next == rowStart) {
					break;
				}
				cursor = cursor->col_next;
			}
			cursor->col_next.reset();
			rowStart = rowStart->row_next;
			if (rowStart == head) {
				break;
			}
			cursor = rowStart;
		}
		cursor = head;
		while (1) {
			while (1) {
				if (cursor == nullptr) {
					cout << "Destructor" << endl;
					return;
				}
				if (cursor->row_next == colStart) {
					break;
				}
				cursor = cursor->row_next;
			}
			cursor->row_next.reset();
			colStart = colStart->col_next;
			if (colStart == head) {
				break;
			}
			cursor = colStart;
		}
		cout << "Destructor" << endl;
	}
	
}

template <typename T> Ring2D<T>::Ring2D(const Ring2D<T>& R) { //Copy Constructor
	if (!R.head) return;
	shared_ptr<Node<T>> rowStart1 = R.head;
	shared_ptr<Node<T>> cursor1 = R.head;
	int rows = 0;
	int columns = 0;
	int r = rows;
	int c = columns;
	while (1) {
		cursor1 = cursor1->col_next;
		columns++;
		if (cursor1 == R.head) {
			break;
		}
	}
	while (1) {
		rowStart1 = rowStart1->row_next;
		rows++;
		if (rowStart1 == R.head) {
			break;
		}
		
	}
	int j = rows * columns;
	while (j > 0) {
		shared_ptr<Node<T>> newNode = make_shared<Node<T>>(0);
		newNode->col_next = head;
		head = newNode;
		j--;
	}
	c = columns;
	r = rows;
	shared_ptr<Node<T>> cursor = head;
	shared_ptr<Node<T>> cursorR = head;
	shared_ptr<Node<T>> rowStart = head;
	while (1) {
		while (c > 1) {
			cursor = cursor->col_next;
			c--;
		}
		c = columns;
		if (cursor->col_next != nullptr) {
			rowStart->row_next = cursor->col_next;
			cursor->col_next = rowStart;
			rowStart = rowStart->row_next;
			cursor = rowStart;
		}
		else {
			cursor->col_next = rowStart;
			break;
		}
	}
	cursor = head;
	while (r > 1) {
		cursorR = cursor->row_next;
		while (c > 1) {
			cursor = cursor->col_next;
			cursorR = cursorR->col_next;
			cursor->row_next = cursorR;
			c--;
		}
		cursor = cursor->col_next;
		cursor = cursor->row_next;
		c = columns;
		r--;
		if (r == 1) {
			cursorR = head;
			if (cursor->row_next == nullptr) {
				while (c > 0) {
					cursor->row_next = cursorR;
					cursorR = cursorR->col_next;
					cursor = cursor->col_next;
					c--;
				}
			}
		}
	}
	cursor = head;
	rowStart = head;
	shared_ptr<Node<T>> cursorO = R.head;
	shared_ptr<Node<T>> cursorRO = R.head;
	shared_ptr<Node<T>> rowStartO = R.head;
	while (1) {
		while (1) {
			cursor->pValue = cursorO->pValue;
			if (cursor->col_next == rowStart) {
				break;
			}
			cursor = cursor->col_next;
			cursorO = cursorO->col_next;
		}
		rowStart = rowStart->row_next;
		rowStartO = rowStartO->row_next;
		if (rowStartO == R.head) {
			break;
		}
		cursor = rowStart;
		cursorO = rowStartO;
	}
	cout << "Copy Constructor" << endl;
}

template <typename T> void Ring2D<T>::operator=(const Ring2D<T>& R) { //copy assignment
	if (head) {
		head->col_next.reset();
		head->row_next.reset();
		head.reset();
	}
	if (!R.head) return;
	shared_ptr<Node<T>> rowStart1 = R.head;
	shared_ptr<Node<T>> cursor1 = R.head;
	int rows = 0;
	int columns = 0;
	int r = rows;
	int c = columns;
	while (1) {
		cursor1 = cursor1->col_next;
		columns++;
		if (cursor1 == R.head) {
			break;
		}
	}
	while (1) {
		rowStart1 = rowStart1->row_next;
		rows++;
		if (rowStart1 == R.head) {
			break;
		}

	}
	int j = rows * columns;
	while (j > 0) {
		shared_ptr<Node<T>> newNode = make_shared<Node<T>>(0);
		newNode->col_next = head;
		head = newNode;
		j--;
	}
	c = columns;
	r = rows;
	shared_ptr<Node<T>> cursor = head;
	shared_ptr<Node<T>> cursorR = head;
	shared_ptr<Node<T>> rowStart = head;
	while (1) {
		while (c > 1) {
			cursor = cursor->col_next;
			c--;
		}
		c = columns;
		if (cursor->col_next != nullptr) {
			rowStart->row_next = cursor->col_next;
			cursor->col_next = rowStart;
			rowStart = rowStart->row_next;
			cursor = rowStart;
		}
		else {
			cursor->col_next = rowStart;
			break;
		}
	}
	cursor = head;
	while (r > 1) {
		cursorR = cursor->row_next;
		while (c > 1) {
			cursor = cursor->col_next;
			cursorR = cursorR->col_next;
			cursor->row_next = cursorR;
			c--;
		}
		cursor = cursor->col_next;
		cursor = cursor->row_next;
		c = columns;
		r--;
		if (r == 1) {
			cursorR = head;
			if (cursor->row_next == nullptr) {
				while (c > 0) {
					cursor->row_next = cursorR;
					cursorR = cursorR->col_next;
					cursor = cursor->col_next;
					c--;
				}
			}
		}
	}
	cursor = head;
	rowStart = head;
	shared_ptr<Node<T>> cursorO = R.head;
	shared_ptr<Node<T>> cursorRO = R.head;
	shared_ptr<Node<T>> rowStartO = R.head;
	while (1) {
		while (1) {
			cursor->pValue = cursorO->pValue;
			if (cursor->col_next == rowStart) {
				break;
			}
			cursor = cursor->col_next;
			cursorO = cursorO->col_next;

		}
		rowStart = rowStart->row_next;
		rowStartO = rowStartO->row_next;
		if (rowStartO == R.head) {
			break;
		}
		cursor = rowStart;
		cursorO = rowStartO;
	}
	cout << "Copy Assignment" << endl;
}
template <typename T> Ring2D<T>::Ring2D(Ring2D<T>&& R) { //Move Constructor
	head = R.head;
	R.head.reset();
	cout << "Move Constructor" << endl;
}

template <typename T> void Ring2D<T>::operator=(Ring2D<T>&& R) { //Move Assignment
	if (head) {
		head->col_next.reset();
		head->row_next.reset();
		head.reset();
	}
	head = R.head;
	R.head.reset();
	cout << "Move Assignment" << endl;
}
template <typename T> Ring2D<T> Ring2D<T>::ThreeTimes() {
	Ring2D<T> temp = *this;
	if (!head) {
		return temp;
	}
	shared_ptr<Node<T>> rowStart = temp.head;
	shared_ptr<Node<T>> cursor = temp.head;
	while (1) {
		while (1) {
			*(cursor->pValue) = *(cursor->pValue)*3;
			if (cursor->col_next == rowStart) {
				break;
			}
			cursor = cursor->col_next;

		}
		rowStart = rowStart->row_next;
		if (rowStart == temp.head) {
			break;
		}
		cursor = rowStart;
	}
	return temp;
}
template <typename T> void Ring2D<T>::DeleteRow(int r) {
	shared_ptr<Node<T>> cursor = this->head;
	shared_ptr<Node<T>> counter = this->head;
	shared_ptr<Node<T>> prev;
	shared_ptr<Node<T>> next;
	shared_ptr<Node<T>> newHead;
	int rows = 0;
	while (1) {
		counter = counter->row_next;
		rows++;
		if (counter == this->head) {
			break;
		}
	}
	if (r > rows || r <= 0 ) {
		return;
	}
	if (r == 1 && rows == 1) {
		this->head.reset();
		return;
	}
	if (r > 1) {
		while (r > 1) {
			prev = cursor;
			cursor = cursor->row_next;
			next = cursor->row_next;
			r--;
		}
		prev->row_next = next;
		if (cursor == this->head) {
			this->head = next;
		}
		cursor.reset();
		return;
	}
	if (r == 1 && rows > 1) {
		next = cursor->row_next;
		newHead = next;
		while (rows > 1) {
			prev = cursor;
			cursor = cursor->row_next;
			if (cursor == this->head) {
				prev->row_next = next;
				break;
			}
		}this->head = newHead;
		cursor.reset();	
		return;
	}
	
}

template <typename T> ostream& operator<<(ostream& str, const Ring2D<T>& R) {
	if (!R.head) return str;
	shared_ptr<Node<T>> rowStart = R.head;
	shared_ptr<Node<T>> cursor = R.head;
	while (1) {
		while (1) {
			str << *(cursor->pValue) << " ";
			if (cursor->col_next == rowStart) {
				break;
			}
			cursor = cursor->col_next;
			
		}
		str << endl;
		rowStart = rowStart->row_next;
		if (rowStart == R.head) {
			break;
		}
		cursor = rowStart;
	}
	return str;
}

int main() {
	Ring2D<int> R1{ 3, 4,  1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12};//initializer_list
	cout << R1 << endl << endl;

	
	Ring2D<int> R2{ R1 };//copy constructor
	cout << R2 << endl << endl;
	Ring2D<int> R3;
	R3 = R1;//copy assignment
	cout << R3 << endl << endl;
		

	Ring2D<int> R4;
	R4 = R1.ThreeTimes();//this is pointing to object R1
		//Compiler will convert it to R4.operator=(R1.ThreeTimes());
		//copy constructor -- declare temp and initialize it to R1
		//move constructor -- create hidden (temporary) copy
		//destructor-- delete temp becuase it goes out of scope
		//move assignment -- Assign value from hidden copy to R4
		//destructor-- delete hidden copy because it goes out of scope
	cout << R1 << endl << endl;

	R4.DeleteRow(2);
	cout << R4 << endl << endl;
	R4.DeleteRow(2);
	cout << R4 << endl << endl;
	R4.DeleteRow(1);
	cout << R4 << endl << endl;

	return 0;
}



