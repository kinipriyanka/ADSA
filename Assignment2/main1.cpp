/*
 * main1.cpp
 *
 *  Created on: Sep 2, 2018
 *      Author: Priyanka
 *	Marks -100/100
 */
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//check AVL tree is empty
int isEmpty = 0;

//Node class
struct Node{

	//node attributes
	int value;
	Node* left;
	Node* right;
	int treeHeight;

	//functions of Node
	int height(Node*);
	Node* insertChild(Node*, int);
	Node* insertRoot(Node*, int);
	Node* deleteNode(Node*, int);
	Node* rotateRight(Node*);
	Node* rotateLeft(Node*);
	int balanceTree(Node*);
	Node* getMaxLeftNode(Node*);
	Node* decideRotation(Node*, int, int, char);
	void printPreOrder(Node*);
	void printInOrder(Node*);
	void printPostOrder(Node*);
};

int Node::height(Node* tree){
	if(tree!=NULL)
		return tree->treeHeight;
	else
		return 0;
}
//insert root for initial iteration
Node* Node::insertRoot(Node* tree, int value){
	tree = new Node();
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	tree->treeHeight = 1;
	return tree;
}

// insert into node->leaf node
Node* Node::insertChild(Node* tree,int value){
	cout<< "Inserting" << endl;
	if(tree == NULL){
		return(insertRoot(tree,value));
	}
	if(value < tree->value){
		tree->left = insertChild(tree->left, value);
	}else if(value > tree->value){
		tree->right = insertChild(tree->right, value);
	}else{
		return tree;
	}

	if(tree!=NULL){
		tree->treeHeight = ((height(tree->left) > height(tree->right))? height(tree->left) : height(tree->right))+1;
	}

	int balHeight = balanceTree(tree);
	return decideRotation(tree,balHeight,value,'A');
}

Node* Node::deleteNode(Node* tree, int value){
	if(tree == NULL){
		return tree;
	}
	if(value < tree->value){
		tree->left = deleteNode(tree->left,value);
	}
	else if(value > tree->value){
		tree->right = deleteNode(tree->right,value);
	}
	else if(value == tree->value){
		if(tree->left == NULL && tree->right == NULL){
			tree = NULL;
		}
		else if(tree->left == NULL && tree->right != NULL){
			tree = tree->right;
		}
		else if(tree->left != NULL && tree->right == NULL){
			tree = tree->left;
		}
		else{
			Node* temp = getMaxLeftNode(tree->left);
			tree->value = temp->value;
			tree->left = deleteNode(tree->left,temp->value);
		}	
	}
	if(tree !=NULL){
		tree->treeHeight = ((height(tree->left) > height(tree->right))? height(tree->left) : height(tree->right))+1;
	}

	int balHeight = balanceTree(tree);
	return decideRotation(tree,balHeight,value,'D');
	
}

//right rotation of node
Node* Node::rotateRight(Node* root){
	Node* root_left = root->left;
	Node* left_right = root_left->right;

	root_left->right = root;
	root->left = left_right;

	//height of tree
	if(root!=NULL || root->left!=NULL || root->right!=NULL)
		root->treeHeight = ((height(root->left) > height(root->right)) ? height(root->left) : height(root->right))+1;

	if(root_left!=NULL || root_left->left!=NULL || root_left->right!=NULL)
		root_left->treeHeight = ((height(root_left->left) > height(root_left->right)) ? height(root_left->left) : height(root_left->right))+1;
	//new root
	return root_left;
}

//left rotation of node
Node* Node::rotateLeft(Node* root){
	Node* root_right = root->right;
	Node* right_left = root_right->left;

	root_right->left = root;
	root->right = right_left;

	//height of tree
	if(root!=NULL || root->left!=NULL || root->right!=NULL)
		root->treeHeight = ((height(root->left) > height(root->right)) ? height(root->left) : height(root->right))+1;

	if(root_right!=NULL || root_right->left!=NULL || root_right->right!=NULL)
		root_right->treeHeight = ((height(root_right->left) > height(root_right->right)) ? height(root_right->left) :  height(root_right->right))+1;

	//new root
	return root_right;
}

//check degree of node
int Node::balanceTree(Node* tree){
	if(tree != NULL){
		if(tree->left == NULL && tree->right == NULL)
			return 0;
		else if(tree->left == NULL && tree->right !=NULL)
			return 0-height(tree->right);
		else if(tree->left !=NULL && tree->right == NULL)
			return height(tree->left)-0;
		else
			return (height(tree->left)- height(tree->right));
	}
	return 0;
}

//for root more than one child get the max child from root's left branch traverse right child
Node* Node::getMaxLeftNode(Node* tree){
	Node* AVLtemp = tree;
	while(AVLtemp->right != NULL){
		AVLtemp = AVLtemp->right;
	}
	return AVLtemp;
}

Node* Node::decideRotation(Node* tree, int balHeight, int value, char inODel){
	if(inODel == 'A'){
		//left-left
		if(balHeight >1 && value < tree->left->value){
			return rotateRight(tree);
		}
		//left-right
		if(balHeight >1 && value > tree->left->value){
			tree->left = tree->rotateLeft(tree->left);
			return rotateRight(tree);
		}
		//right-right
		if(balHeight < -1 && value > tree->right->value){
			return rotateLeft(tree);
		}
		//right-left
		if(balHeight < -1 && value < tree->right->value){
			tree->right = rotateRight(tree->right);
			return rotateLeft(tree);
		}
		
	}else if(inODel == 'D'){
		//left-left
		if(balHeight >1 && balanceTree(tree->left)>=0){
			return rotateRight(tree);
		}
		//left-right
		if(balHeight >1 &&  balanceTree(tree->left)<0){
			tree->left = rotateLeft(tree->left);
			return rotateRight(tree);
		}
		//right-right
		if(balHeight < -1 && balanceTree(tree->right)<=0){
			return rotateLeft(tree);
		}
		//right-left
		if(balHeight < -1 && balanceTree(tree->right)>0){
			tree->right = rotateRight(tree->right);
			return rotateLeft(tree);
		}
		
	}
	return tree;
}

/*
 * printing based on PRE, POST or IN
 * */
void Node::printPreOrder(Node* tree){
	if(tree!=NULL){
		cout << tree->value << " ";
		if(isEmpty == 0) 
			isEmpty=1;
		printPreOrder(tree->left);
		printPreOrder(tree->right);
	}
}

void Node::printInOrder(Node* tree){
	if(tree != NULL){
		printInOrder(tree->left);
		cout << tree->value << " ";
		if(isEmpty == 0) 
			isEmpty=1;
		printInOrder(tree->right);
	}
}

void Node::printPostOrder(Node* tree){
	if(tree!= NULL){
		printPostOrder(tree->left);
		printPostOrder(tree->right);
		cout << tree->value << " ";
		if(isEmpty == 0) 
			isEmpty=1;
	}
}

//MAIN Method
int main(){
	char largechars[1000000];
	std::vector<char*> v;
	string decision,order;
	int value;
	Node* binaryTree = NULL;

	//reading input
	cin.getline(largechars, 1000000);

	//split based on space
	char* chars_array = strtok(largechars, " ");
	while(chars_array)
	{
		v.push_back(chars_array);
		chars_array = strtok(NULL, " ");
	}

	//check if to add or delete
	for(unsigned int i=0;i<v.size()-1;i++){
		decision=v[i];
		value = stoi(decision.substr(1, decision.size()-1));
		if(decision[0]== 'A'){
			binaryTree= binaryTree->insertChild(binaryTree, value);
		}else{
			binaryTree = binaryTree->deleteNode(binaryTree, value);
		}
	}


	//take order to print
	order = v[v.size()-1];
		if(order=="IN")
			binaryTree->printInOrder(binaryTree);
		else if(order == "PRE")
			binaryTree->printPreOrder(binaryTree);
		else if(order == "POST")
			binaryTree->printPostOrder(binaryTree);
		if(isEmpty == 0) 
			cout << "EMPTY" << endl;
		else
			cout << endl;
}
 


