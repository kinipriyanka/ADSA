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


/*For input  A23 A59 D51 A32 A28 A40 A59 A6 A82 D91 A36 D84 A95 D57 A99 A32 D38 D29 D45 D45 A58 A71 A55 A39 D69 A64 D57 A90 A36 A6 A55 A20 A45 D41 A13 D76 A44 D26 A64 A12 D83 D19 D86 D88 A82 D23 A34 D69 D91 A56 A52 D23 A83 D92 A41 D45 A63 A87 A80 A17 A77 D75 A27 A3 D16 A97 A1 A21 A67 A31 A17 D97 A64 D9 D35 A53 D48 D78 D17 A82 D77 D85 A5 D66 A68 A31 A41 D23 D41 D9 A36 A45 A88 D16 A5 D70 A61 D79 A29 A50 POST
Output received  1 5 3 12 13 6 21 28 31 29 27 34 39 36 32 20 44 50 53 52 45 56 58 55 61 64 63 68 80 71 67 83 88 90 87 99 95 82 59 40 

Output shouldbe  1 5 3 12 13 6 21 28 31 29 27 34 39 36 32 20 44 50 45 53 52 56 58 55 61 64 63 68 80 71 67 83 88 87 99 95 90 82 59 40
incorrect	     1 5 3 12 13 6 21 28 31 29 27 34 39 36 32 20 44 50 45 53 52 56 58 55 61 64 63 68 80 71 67 83 88 87 99 95 90 82 59 40

For input  A32 A4 D24 D72 A22 A8 A47 D35 D62 D28 D54 A49 A52 A91 A37 A9 A22 D86 A7 D69 A61 A96 A71 D62 D4 D34 A90 D62 A31 D79 A61 A78 A44 A16 D42 D59 A60 D46 A57 A67 A99 D42 A18 A24 D96 A71 D84 A18 A92 A49 A70 D28 A36 A98 D30 D31 D3 D18 D2 A93 D88 A54 A34 D31 D36 D27 D59 D40 A13 D82 A59 D31 D23 A24 A75 A19 D80 A12 A87 A87 D71 D84 D52 D68 A56 A11 A8 D93 A83 D54 D73 D8 D11 A29 A13 D54 D92 D32 A5 D33 PRE
Output received  47 22 13 9 7 5 12 16 19 34 29 24 37 44 78 61 57 49 56 60 59 70 67 75 91 90 87 83 98 99 
				 47 22 13 9 7 5 12 16 19 34 29 24 37 44 78 61 57 49 56 60 59 70 67 75 91 90 87 83 98 99
Output shouldbe  47 22 13 9 7 5 12 16 19 34 29 24 37 44 61 57 49 56 60 59 90 78 70 67 75 87 83 98 91 99
incorrect

For input  D23 D87 D47 D36 A55 D39 A4 D26 A11 A93 D38 A44 A98 D1 A98 A95 D39 A24 A64 D22 A32 D51 A9 A63 A35 A74 D95 D51 A50 A56 D12 D4 D31 A74 D80 A8 D12 A81 A29 A91 A69 D80 A68 D100 D92 D25 D69 A75 D73 D29 D5 D25 A9 A30 A59 A66 D75 D95 D60 A26 D56 D69 D94 A21 D17 D25 A17 A77 D58 D13 A81 A1 A47 D94 A24 A50 D76 D1 A51 D83 A86 A5 D48 A57 A28 D15 D46 A14 D21 A53 D85 A15 D6 A29 D99 D43 D29 D47 D55 A86 IN
Output received  5 8 9 11 14 15 17 24 26 28 30 32 35 44 50 51 53 57 59 63 64 66 68 74 77 81 86 91 93 98 

Output shouldbe  5 8 9 11 14 15 17 24 26 28 30 32 35 44 50 51 53 57 59 63 64 66 68 74 77 81 86 91 93 98
correct*/		 


