#include <iostream>
using namespace std;

struct Node {
	int id;
	string name;
	int age;
	Node *next;
};

Node *head, *tail, *current;

void printAll() {
	cout << "\nQueue: ";
	if (head == NULL) {
		cout << "empty";
	} else {		
		Node *temp = head;

		cout << endl;
		while (temp != NULL) {
			cout << "[" << temp->id << ", " << temp->name << ", " << temp->age << "]\n";
			temp = temp->next;
		}
	}
}

void enqueue() {
	// for getting leftover "\n" from cin
	string dummy;

	Node *newNode = new Node();

	cout << "Enter id: "; cin >> newNode->id;
	getline(cin, dummy);
	cout << "Enter name: "; getline(cin, newNode->name);
	cout << "Enter age: "; cin >> newNode->age;

	newNode->next = NULL;

	if (head == NULL) head = tail = current = newNode;
	else {
		Node *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next  = current = tail = newNode;
	}
}

void dequeue() {
	Node *temp = head;

	if (head == NULL) {
		cout << "\n!INVALID OPERATION: QUEUE IS EMPTY\n";
		return;
	} else if (head == tail) {
		head = tail = current = NULL;
	} else {
		if (current != head)
			head = head->next;
		else 
			head = current = head->next;
	}

	cout << "\n!ID " << temp->id << " HAS BEEN REMOVED\n";
	free(temp);
}

void initialize() {
	if (head == NULL) {
		cout << "\n!INVALID OPERATION: QUEUE IS EMPTY\n";
	} else {
		while(head != NULL){
			dequeue();
		}
		cout << "\n!LINKED LIST CLEARED\n";
	}
}

void printCurrent() {
	cout << "\nCurrent: ";
	if (current == NULL) {
		cout << "null\n";
	} else {
		cout << "[" << current->id << ", " << current->name << ", " << current->age << "]\n";
	}
}

void printHead() {
	cout << "\nHead: ";
	if (head == NULL) {
		cout << "null\n";
	} else {
		cout << "[" << head->id << ", " << head->name << ", " << head->age << "]\n";
	}
}

void printTail() {
	cout << "\nTail: ";
	if (tail == NULL) {
		cout << "null\n";
	} else {
		cout << "[" << tail->id << ", " << tail->name << ", " << tail->age << "]\n";
	}
}

void moveNext() {
	if (head == NULL) {
		cout << "\n!INVALID OPERATION: QUEUE IS EMPTY\n";
	} else {
		if (current->next != NULL) {
			current = current->next;
		} else {
			cout << "\n!INVALID OPERATION: THIS IS THE LAST ELEMENT\n";
		}
	}
}

void moveHead() {
	if(head == NULL){
		cout << "\n!INVALID OPERATION: QUEUE IS EMPTY\n";
	} else {
		current = head;
	}
}

void menu() {
	int ans;
	while (true) {
		printAll();
		printCurrent();
		cout << "\nMENU\n"
			 << "1. enqueue\n"
			 << "2. dequeue\n"
			 << "3. move next\n"
			 << "4. move previous\n"
			 << "5. print head\n"
			 << "6. print tail\n"
			 << "7. print current\n"
			 << "8. print all\n"
			 << "9. move to head\n"
			 << "10. Initialize\n"
			 << "0. EXIT\n";
		cin >> ans;

		switch (ans) {
			case 1:
				enqueue();
				break;
			case 2:
				dequeue();
				break;
			case 3:
				moveNext();
				break;
			case 4:
				cout << "\n!INVALID OPERATION: SINGLE LINKED LIST DOESN'T HAVE PREVIOUS FUNCTIONALITY\n";
				break;
			case 5:
				printHead();
				break;
			case 6:
				printTail();
				break;
			case 7:
				printCurrent();
				break;
			case 8:
				printAll();
				break;
			case 9:
				moveHead();
				break;
			case 10:
				initialize();
				break;
			case 0:
				exit(0);
		}
	}
}

int main() {
	// initialize with empty linked list
	head = tail = current = NULL;

	menu();

	return 0;
}