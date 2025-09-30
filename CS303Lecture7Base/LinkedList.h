#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

namespace myList {
	template <typename ItemType>
	class LinkedList {

	private:
		struct DNode {
			ItemType data;
			DNode* nextPtr;
			DNode* prevPtr;

			DNode() : data(0), nextPtr(nullptr), prevPtr(nullptr) {}


			// Constructor
			DNode(const ItemType& data_item, DNode* prev, DNode* next) :
				data(data_item),
				prevPtr(prev),
				nextPtr(next) {}
		};

		DNode* head;
		DNode* tail;
		int numItems;


	public:

		class iterator {
			friend class LinkedList;

		private:
			DNode* current;			// A pointer to the current DNode 

		public:
			iterator(DNode* position) :
				current(position) {
				std::cout << "Default constructor\n";
			}

			//used for *iterator = newValue
			ItemType& operator*() const {
				std::cout << "myIterator* = newValue\n";
				if (current == nullptr)
					throw std::invalid_argument("Attempt to dereference end()");

				return current->data;
			}

			//used to get current data value:  example iterator->data()
			ItemType* operator->() const {
				std::cout << "Using myIterator->\n";
				if (current == nullptr)
					throw std::invalid_argument("Attempt to dereference end()");

				return &(current->data);
			}

			// Equality comparison
			bool operator==(const iterator& other) const {
				return current == other.current;
			}

			iterator& operator++() {
				std::cout << "prefix operator ++\n";
				if (current == nullptr)
					throw std::invalid_argument("Attempt to advance past end()");
				current = current->nextPtr;

				return *this;
			}

			iterator operator++(int) {
				std::cout << "postfix operator ++\n";
				// Make a copy of the current value.
				iterator return_value = *this; //*this returns a dereferenced pointer
				// Advance self forward.
				++(*this);
				// Return old value.
				return return_value;   // Return the value prior to increment
			}

			iterator& operator--() {
				std::cout << "postfix operator --\n";
				if (current->prevPtr == nullptr)   // no prior elements
					throw std::invalid_argument("There are no previous elements");
				else
					current = current->prevPtr;
				return *this;
			}


			iterator  operator--(int) {
				std::cout << "prefix operator --\n";
				// Make a copy of the current value.
				iterator return_value = *this;
				// Move self backward.
				if (current)
					current = current->prevPtr;
				// Return old value.
				return return_value;   // Return the value prior to decrement
			}
		};


		class constIterator {

		private:
			DNode* current;			// A pointer to the current DNode 

		public:
			constIterator(DNode* position) :
				current(position) {
				std::cout << "Default constructor\n";
			}

			//used for *iterator = newValue
			const ItemType& operator*() const {
				std::cout << "myIterator* = newValue\n";
				if (current == nullptr)
					throw std::invalid_argument("Attempt to dereference end()");

				return current->data;
			}

			//used to get current data value:  example iterator->data()
			const ItemType* operator->() const {
				std::cout << "Using myIterator->\n";
				if (current == nullptr)
					throw std::invalid_argument("Attempt to dereference end()");

				return &(current->data);
			}

			// Equality comparison
			bool operator==(const constIterator& other) const {
				return current == other.current;
			}

			constIterator& operator++() {
				std::cout << "prefix operator ++\n";
				if (current == nullptr)
					throw std::invalid_argument("Attempt to advance past end()");
				current = current->nextPtr;

				return *this;
			}

			constIterator operator++(int) {
				std::cout << "postfix operator ++\n";
				// Make a copy of the current value.
				constIterator return_value = *this; //*this returns a dereferenced pointer
				// Advance self forward.
				++(*this);
				// Return old value.
				return return_value;   // Return the value prior to increment
			}

			constIterator& operator--() {
				std::cout << "postfix operator --\n";
				if (current->prevPtr == nullptr)   // no prior elements
					throw std::invalid_argument("There are no previous elements");
				else
					current = current->prevPtr;
				return *this;
			}
			constIterator  operator--(int) {
				std::cout << "prefix operator --\n";
				// Make a copy of the current value.
				constIterator return_value = *this;
				// Move self backward.
				if (current)
					current = current->prevPtr;
				// Return old value.
				return return_value;   // Return the value prior to decrement
			}
		};

		LinkedList();
		DNode* getHeadPtr() { return head; }
		DNode* getTailPtr() { return tail; }
		iterator begin() { return head; }
		iterator end() { return tail; }
		size_t getNumItems() { return numItems; }
		bool empty() { return numItems == 0; }
		void pushBack(const ItemType& d);
		void pushFront(const ItemType& d);

		ItemType back();
		ItemType front();

		ItemType popBack();
		ItemType popFront();
		string printList() const;

		bool find(const ItemType& d);
		bool remove(const ItemType& d);

		void insert(const size_t pos, const ItemType& newValue);
		bool addBefore(const ItemType& item, const ItemType& value);

		//DESTRUCTOR
		~LinkedList() {
			cout << "Calling destructor\n";
			while (head != nullptr) {
				DNode* current = head;
				head = head->nextPtr;
				delete current;
			}
			tail = nullptr;
			numItems = 0;
		}

		//COPY CONSTRUCTOR
		LinkedList(LinkedList<ItemType>& other) : head(nullptr), tail(nullptr), numItems(0) {
			cout << "Calling copy constructor\n";
			iterator itr = other.begin();
			for (int i = 0; i < other.numItems - 1; i++) {
				pushBack(*itr);
				itr++;
			}
		}

		//COPY ASSIGNMENT
		LinkedList<ItemType>& operator= (const LinkedList<ItemType>& other) {
			cout << "Calling copy assignment\n";
			if (this == &other) return *this;

			//create a node for currPtr
			DNode* currPtr = other.head;
			while (!(currPtr == nullptr)) {
				pushBack(currPtr->data);
				currPtr = currPtr->nextPtr;
			}
			return *this;
		}


 
		//PRE:  sends an iterator position - we are erasing the node at ‘pos’
		//POST: verifies position is valid.
		//          special case 1: the list is empty – throw error
		//          special case 2: pos is nullptr – throw error
		//      if valid, saves the value, checks for special case deletion
		//	        special case 3: removes the head pointer
		//	        special case 4: removes the tail pointer
		//          ‘normal’ erase


		iterator erase(iterator pos) {
			cout << "erase position insert with pos\n";
			//special case 1: the list is empty
			if (numItems == 0)
				throw std::invalid_argument("Attempt to call erase on an empty list");

			//special case 2: points to the end of the list
			if (pos == nullptr)
				throw std::invalid_argument("Attempt to call erase with nullptr");

			// Create an iterator that references the position following pos.
			iterator return_value = pos;
			++return_value;

			// special case 3: removes the head pointer
			if (pos == this->head) {
				this->popFront();
				return return_value;
			}
			// special case 4: removes the tail pointer
			else if (pos == this->tail) {
				this->popBack();
				return return_value;
			}
			else {  // Remove a node in the interior of the list.
				iterator removed_node = pos;
				removed_node.current->prevPtr->nextPtr = removed_node.current->nextPtr;

				removed_node.current->nextPtr->prevPtr = removed_node.current->prevPtr;
				delete removed_node.current;
				--this->numItems;
				return return_value;
			}
		}
 
		//PRE:  accepts an iterator to the location of item to insert & a value
		//POST: verifies position is valid.
		//      adds list to front if 'pos' is the head or list is empty
		//      add to end of list if 'pos' is nullptr
		//      otherwise, creates the node & adjusts prev & next pointers
		//      returns iterator that points to the new value
		iterator insert(iterator pos, const ItemType& newValue) {
			cout << "insert with pos\n";
			//pos is set to headptr or list is empty
			if (empty() || pos == this->head) {
				pushFront(newValue);
				return head;
			}
			//pos is set to nullptr
			else if (pos == nullptr) {
				pushBack(newValue);
				return iterator(tail);
			}

			// otherwise, creates the node & adjusts prev & next pointers
			DNode* newItem = new DNode;
			newItem->data = newValue;
			newItem->nextPtr = pos.current;
			newItem->prevPtr = pos.current->prevPtr;
			pos.current->prevPtr->nextPtr = newItem;
			pos.current->prevPtr = newItem;
			++this->numItems;

			return iterator(newItem);
		}

		void insert(const ItemType& newValue) {
 
			LinkedList<ItemType>::iterator itr = this->begin();

			while (!(itr == this->end()) && *itr < newValue)
				++itr;

			if (!(itr == nullptr) && *itr < newValue)
				++itr;

			insert(itr, newValue);
		}

		ItemType operator[] (size_t n) {
			ItemType temp = 0;
			if (n > numItems - 1)
				throw exception("Accessing out of range\n");
			else if (numItems == 0)
				throw exception("No Elements in the list\n");
			size_t i = 0;
			DNode* tempPtr;
			tempPtr = head;

			while (tempPtr != nullptr) {
				if (i == n) {
					temp = tempPtr->data;
					return temp;
				}
				tempPtr = tempPtr->nextPtr;
				++i;
			}
			cout << endl;
			return temp;
		}
	};
	//########################################################################################
	//default constructor
	template <typename ItemType>
	LinkedList<ItemType>::LinkedList() {
		cout << "default constructor\n";
		head = nullptr;
		tail = nullptr;
		numItems = 0;
	}

	template <typename ItemType>
	void LinkedList<ItemType>::pushBack(const ItemType& d) {
		cout << "pushback\n";

		if (head == nullptr) {
			pushFront(d);
		}
		else {
			DNode* newItem = new DNode;
			newItem->data = d;
			newItem->nextPtr = nullptr;
			newItem->prevPtr = tail;
			tail->nextPtr = newItem;
			tail = newItem;
		}
		++numItems;
	}

	template <typename ItemType>
	void LinkedList<ItemType>::pushFront(const ItemType& d) {
		cout << "pushfront\n";
		DNode* newItem = new DNode;
		newItem->data = d;
		newItem->nextPtr = nullptr;
		newItem->prevPtr = nullptr;

		if (head == nullptr) {
			head = newItem;
			tail = newItem;
		}
		else {
			newItem->nextPtr = head;
			head->prevPtr = newItem;
			head = newItem;
		}
		++numItems;
	}

	template <typename ItemType>
	ItemType LinkedList<ItemType>::back() {
		//list is empty
		if (tail == nullptr) {
			throw runtime_error("No items in list");
		}
		ItemType popItem = tail->data;
		return popItem;
	}

	template <typename ItemType>
	ItemType LinkedList<ItemType>::front() {
		//list is empty
		if (head == nullptr) {
			throw runtime_error("No items in list");
		}
		ItemType popItem = head->data;
		return popItem;
	}

	template <typename ItemType>
	ItemType LinkedList<ItemType>::popBack() {
		cout << "popback:  ";
		//list is empty
		if (tail == nullptr) {
			throw invalid_argument("No items in list");
		}

		DNode* delNode = tail;
		ItemType popItem = tail->data;
		tail = tail->prevPtr;
		delete delNode;
		delNode = nullptr;

		if (tail != nullptr)
			tail->nextPtr = nullptr;
		else
			head = nullptr;

		--numItems;
		return popItem;
	}

	template <typename ItemType>
	ItemType LinkedList<ItemType>::popFront() {
		cout << "popfront:  ";
		if (head == nullptr) {
			throw runtime_error("No items in list");
		}

		ItemType popItem = head->data;
		DNode* delPtr = head;
		if (head->nextPtr == nullptr)
			tail = nullptr;

		head = head->nextPtr;
		delete delPtr;
		delPtr = nullptr;
		--numItems;

		return popItem;
	}

	template <typename ItemType>
	string LinkedList<ItemType>::printList() const {
		//list is empty
		if (head == nullptr) {
			throw runtime_error("No items in list");
		}
		string out = "";
		LinkedList<ItemType>::constIterator cIt = head;

		out += "printList   " + to_string(numItems) + ": { ";
		while (!(cIt == nullptr)) {
			out += to_string(*cIt) + ", ";
			++cIt;
		}
		out += " }";
		return out;
	}

	template <typename ItemType>
	bool LinkedList<ItemType>::find(const ItemType& d) {

		if (numItems == 0) {
			return false;
		}

		DNode* tempPtr;
		tempPtr = head;

		while (tempPtr != nullptr && tempPtr->data != d) {
			tempPtr = tempPtr->nextPtr;
		}

		if (tempPtr == nullptr || tempPtr->data != d)
			return false;
		else
			return true;
	}




	//PRE:  sends an item value from the list
	//POST: search the list for the first value in the list matching 'd'
	//      return true if found; false if not
	template <typename ItemType>
	bool LinkedList<ItemType>::remove(const ItemType& d) {

		//special case 1: the list is empty
		if (numItems == 0)
			return false;

		DNode* tempPtr;
		tempPtr = head;

		//special case 2: delete head of list
		if (tempPtr != nullptr && tempPtr->data == d) {
			head = head->nextPtr;
			head->prevPtr = nullptr;
			delete tempPtr;
			tempPtr = nullptr;
			--numItems;
			return true;
		}

		//regular case: advance through list to find matching data or end of list
		while (tempPtr != nullptr
			&& tempPtr->data != d) {
			tempPtr = tempPtr->nextPtr;
		}

		if (tempPtr != nullptr
			&& tempPtr->data == d) {   //delete the next node

			tempPtr->prevPtr->nextPtr = tempPtr->nextPtr;
			if (tempPtr->nextPtr == nullptr) {
				tail = tempPtr->prevPtr;
			}
			else {
				tempPtr->nextPtr->prevPtr = tempPtr->prevPtr;
				tempPtr->nextPtr = tempPtr->nextPtr->nextPtr;
			}
			delete tempPtr;
			--numItems;
			return true;
		}
		return false;
	}

	template <typename ItemType>
	bool LinkedList<ItemType>::addBefore(const ItemType& d, const ItemType& value) {

		//d is value at headptr or list is empty
		if (head == nullptr || head->data == d) {
			pushFront(value);
			return true;
		}
		//if 'd' is not found - pushback
		else if (!find(d)) {
			pushBack(value);
			return true;
		}

		DNode* newItem = new DNode;
		newItem->data = value;
		newItem->nextPtr = nullptr;
		newItem->prevPtr = nullptr;

		//add before d

		DNode* tempPtr;
		tempPtr = head;

		while (tempPtr != nullptr
			&& tempPtr->nextPtr != nullptr
			&& tempPtr->nextPtr->data != d) {
			tempPtr = tempPtr->nextPtr;
		}

		if (tempPtr != nullptr
			&& tempPtr->nextPtr != nullptr
			&& tempPtr->nextPtr->data == d) {
			newItem->nextPtr = tempPtr->nextPtr;
			newItem->prevPtr = tempPtr;
			tempPtr->nextPtr->prevPtr = newItem;
			tempPtr->nextPtr = newItem;

			++numItems;
			return true;
		}
		return false;
	}

	template <typename ItemType>
	void LinkedList<ItemType>::insert(const size_t pos, const ItemType& newValue) {

		//d is value at headptr or list is empty
		if (pos < 0 || pos > numItems) {
			throw runtime_error("Invalid position provided");
		}

		DNode* newItem = new DNode;
		newItem->data = newValue;
		newItem->nextPtr = nullptr;
		newItem->prevPtr = nullptr;
		cout << pos << " = " << numItems << endl;

		if (pos == 0) {
			pushFront(newValue);
			return;
		}
		else if (pos == numItems) {
			pushBack(newValue);
			return;
		}

		DNode* tempPtr;
		tempPtr = head;
		size_t count = 0;

		while (tempPtr != nullptr
			&& count < pos - 1) {
			tempPtr = tempPtr->nextPtr;
			++count;
		}

		if (tempPtr != nullptr && count == pos - 1) {
			newItem->nextPtr = tempPtr->nextPtr;
			newItem->prevPtr = tempPtr;
			tempPtr->nextPtr->prevPtr = newItem;
			tempPtr->nextPtr = newItem;
			++numItems;
		}
	}

	
};