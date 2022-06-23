#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	double data;
	Node *leftchild, *rightchild, *parent;
	int bf;
	int height;
};

Node *root = NULL;
Node *current = NULL;

Node* createNode(double value) {
	Node *node = new Node();
	node->leftchild = node->rightchild = node->parent = NULL;
	node->height = node->bf = 0;
	node->data = value;
	return node;
}

bool contains(Node *node, double value) {
	if (node == NULL) return false;
	if (value < node->data) return contains(node->leftchild, value);
	if (value > node->data) return contains(node->rightchild, value);
	return true;
}

void update(Node *node) {
	int leftNodeHeight = (node->leftchild == NULL) ? -1 : node->leftchild->height;
	int rightNodeHeight = (node->rightchild == NULL) ? -1 : node->rightchild->height;

	node->height = 1 + max(leftNodeHeight, rightNodeHeight);

	node->bf = rightNodeHeight - leftNodeHeight;
}

Node* leftRotation(Node *node) {
	Node *oldParent = node->parent;
	Node *newParent = node->rightchild;

	node->rightchild = newParent->leftchild;
	if (newParent->leftchild != NULL) newParent->leftchild->parent = node;
	newParent->leftchild = node;
	node->parent = newParent;
	newParent->parent = oldParent;

	update(node);
	update(newParent);
	return newParent;
}

Node* rightRotation(Node *node) {
	Node *oldParent = node->parent;
	Node *newParent = node->leftchild;

	node->leftchild = newParent->rightchild;
	if (newParent->rightchild != NULL) newParent->rightchild->parent = node;
	newParent->rightchild = node;
	node->parent = newParent;
	newParent->parent = oldParent;

	update(node);
	update(newParent);
	return newParent;
}

Node* leftLeftCase(Node *node) {
	return rightRotation(node);
}

Node* leftRightCase(Node *node) {
	node->leftchild = leftRotation(node->leftchild);
	return leftLeftCase(node);
}

Node* rightRightCase(Node *node) {
	return leftRotation(node);
}

Node* rightLeftCase(Node *node) {
	node->rightchild = rightRotation(node->rightchild);
	return rightRightCase(node);
}

Node* balance(Node *node) {
	// left heavy
	if (node->bf < -1) {
		// left-left case
		if (node->leftchild->bf <= 0) {
			return leftLeftCase(node);

		// left-right case
		} else {
			return leftRightCase(node);
		}

	// right heavy
	} else if (node->bf > 1) {
		// right-right case
		if (node->rightchild->bf >= 0) {
			return rightRightCase(node);

		// right-left case
		} else {
			return rightLeftCase(node);
		}
	}

	// bf is either -1, 0, 1
	return node;
}

Node* insert(Node *node, Node *parent, double value) {
	if (node == NULL) {
		current = createNode(value);
		current->parent = parent;
		return current;
	}

	if (value < node->data) node->leftchild = insert(node->leftchild, node, value);
	else node->rightchild = insert(node->rightchild, node, value);	

	update(node);

	return balance(node);
}

bool insert(double value) {
	if (!contains(root, value)) {
		root = insert(root, NULL, value);
		return true;
	}
	else return false;
}

double findMin(Node* node) {
	while (node->leftchild != NULL) 
		node = node->leftchild;
	return node->data;
}

Node* remove(Node *node, double value) {
	if (node == NULL) return NULL;

	if (value < node->data) 
		node->leftchild = remove(node->leftchild, value);
	else if (value > node->data) 
		node->rightchild = remove(node->rightchild, value);
	else {

		if (node->leftchild == NULL) {
			Node *tmp = node->rightchild;
			if (tmp != NULL) tmp->parent = node->parent;
			free(node);
			return tmp;
		}
		else if (node->rightchild == NULL) {
			Node *tmp = node->leftchild;
			if (tmp != NULL) tmp->parent = node->parent;
			free(node);
			return tmp;
		}
		else {
			// if node to remove has both left & right subtree
			// search min value from right subtree
			double replaceValue = findMin(node->rightchild);
			node->data = replaceValue;

			// delete the duplicate
			node->rightchild = remove(node->rightchild, replaceValue);
		}
	}

	update(node);

	return balance(node);
}

Node* removeSubTree(Node* node) {
	if (node == NULL) return NULL;
	else if (node->leftchild == NULL && node->rightchild == NULL) {
		free(node);
		return NULL;
	}

	node->leftchild = removeSubTree(node->leftchild);
	node->rightchild = removeSubTree(node->rightchild);

	free(node);
	return NULL;
}

Node* removeSubTree(Node *node, double value) {
	if (node == NULL) return NULL;

	if (value < node->data)
		node->leftchild = removeSubTree(node->leftchild, value);
	else if (value > node->data)
		node->rightchild = removeSubTree(node->rightchild, value);
	else 	
		return removeSubTree(node);

	update(node);
	return node;
}


Node* balanceAll(Node *node) {
	if (node == NULL) return NULL;
	else {
		node->leftchild = balanceAll(node->leftchild);
		node->rightchild = balanceAll(node->rightchild);
		return balance(node);
	}
}

bool isBalance = false;
void checkBalance(Node* node) {
	if (node == NULL) return;
	else if (node->bf <= -2 || node->bf >= 2) {
		isBalance = false;
		return;
	}
	else isBalance = true;

	checkBalance(node->leftchild);
	if (isBalance)
		checkBalance(node->rightchild);
}

void balanceAll() {
	while (!isBalance) {
		root = balanceAll(root);
		checkBalance(root);
	}
}

void moveToLeftchild() {
	if (current != NULL) {
		if (current->leftchild != NULL)
			current = current->leftchild;
		else
			cout << "\n!ERROR: CURRENT NODE DOESN'T HAVE LEFT CHILD\n";
	} else 
		cout << "\n!ERROR: THE TREE IS EMPTY\n";
}

void moveToRightchild() {
	if (current != NULL) {
		if (current->rightchild != NULL)
			current = current->rightchild;
		else
			cout << "\n!ERROR: CURRENT NODE DOESN'T HAVE RIGHT CHILD\n";
	} else
		cout << "\n!ERROR: THE TREE IS EMPTY\n";
}

void moveToParent() {
	if (current != NULL) {
		if (current->parent != NULL)
			current = current->parent;
		else
			cout << "\n!ERROR: THIS IS THE ROOT NODE\n";
	} else 
		cout << "\n!ERORR: THE TREE IS EMPTY\n";
}

void printCurrent() {
	if (current != NULL)
		cout << "\n!CURRENT NODE: " << current->data << endl;
	else
		cout << "\n!ERROR: TREE IS EMPTY\n";
}

void preorder(Node *node) {
	if (node == NULL) return;
	else {
		cout << node->data << " ";
		preorder(node->leftchild);
		preorder(node->rightchild);
	}
}

void postorder(Node *node) {
	if (node == NULL) return;
	else {
		postorder(node->leftchild);
		postorder(node->rightchild);
		cout << node->data << " ";
	}
}

void inorder(Node *node) {
	if (node == NULL) return;
	else {
		inorder(node->leftchild);
		cout << node->data << " ";
		inorder(node->rightchild);
	}
}

void printPtr() {
	if (current == NULL)
		cout << "--- CURRENT: -  || PARENT: -  || LEFT: -  || RIGHT: -\n";
	else {
		cout << "--- CURRENT: " << current->data << "  || ";
		if (current->parent == NULL)
			cout << "PARENT: -  || ";
		else
			cout << "PARENT: " << current->parent->data << "  || ";

		if (current->leftchild == NULL)
			cout << "LEFT: -  || ";
		else
			cout << "LEFT: " << current->leftchild->data << " || ";

		if (current->rightchild == NULL)
			cout << "RIGHT: -";
		else
			cout << "RIGHT: " << current->rightchild->data;

		cout << endl;
	}
}

int main() {
	int input;
	while (true) {
		cout << endl
			 << " 0. Exit\n"
			 << " 1. Initialize Tree\n"
			 << " 2. Add a node\n"
			 << " 3. Move to left child\n"
			 << " 4. Move to right child\n"
			 << " 5. Move to parent\n"
			 << " 6. Print current node\n"
			 << " 7. Print Pre Order  [N-L-R]\n"
			 << " 8. Print Post Order [L-R-N]\n"
			 << " 9. Print In Order   [L-N-R]\n"
			 << "10. Remove Current Node\n"
			 << "11. Remove Current Sub-tree\n";

		printPtr();
		
		cout << "Your input: "; cin >> input;

		switch (input) {
			case 0:
				exit(0);
			case 1:
				if (root != NULL) {
					root = removeSubTree(root);
					current = root;
					cout << "\n!TREE INITIALIZED\n";
				}
				else
					cout << "\n!ERROR: THE TREE IS EMPTY\n";
				break;
			case 2:
				double value;
				cout << "Add node: "; cin >> value;
				if (insert(value))
					cout << "\n!NODE INSERTED SUCCESSFULLY\n";
				else
					cout << "\n!ERROR: NODE ALREADY EXIST\n";
				break;
			case 3:
				moveToLeftchild();
				break;
			case 4:
				moveToRightchild();
				break;
			case 5:
				moveToParent();
				break;
			case 6: 
				printCurrent();
				break;
			case 7:
				if (root != NULL) {
					cout << "\n!PRE ORDER: ";
					preorder(root);
					cout << endl;
				} else
					cout << "\n!ERROR: TREE IS EMPTY\n";
				break;
			case 8:
				if (root != NULL) {
					cout << "\n!POST ORDER: ";
					postorder(root);
					cout << endl;
				} else 
					cout << "\n!ERROR: TREE IS EMPTY\n";
				break;
			case 9:
				if (root != NULL) {
					cout << "\n!IN ORDER: ";
					inorder(root);
					cout << endl;
				} else
					cout << "\n!ERROR: TREE IS EMPTY\n";
				break;
			case 10:
				if (root != NULL) {
					root = remove(root, current->data);
					// set current back to root after every node removal
					current = root;
					cout << "\n!NODE DELETED SUCCESSFULLY\n";
				} else
					cout << "\n!ERROR: TREE IS EMPTY\n";
				break;
			case 11:
				if (root != NULL) {
					root = removeSubTree(root, current->data);
					// balance the whole tree
					balanceAll();
					// set current back to root after every sub tree removal
					current = root; 
				} else
					cout << "\n!ERROR: TREE IS EMPTY\n";
				break;
		}
	}
	return 0;
}