#include "stdafx.h"
#include "OrgTree.h"
#include <iostream>
#include <fstream>
#include "stack"

#define TREENODEPTR OrgTree::TreeNode*
#define TREENULLPTR NULL

using namespace std;

/*TreeNode functions*/
/*Time Complexity: Theta(1) for all treenode functions */
string OrgTree::TreeNode::getTitle()
{
	return title;
}

string OrgTree::TreeNode::getName()
{
	return name;
}

OrgTree::OrgTree() // Default constructor
{
	treeSize = 0;
	root = TREENULLPTR;
}

/*Adds a new node to the root position of the tree. If there is already an existing root, new node becomes new root 
and the existing node becomes a child of the new root*/
/*Time Complexity: Theta(1)*/
void OrgTree::addRoot(string title, string name)
{
	TreeNode *newRoot = new TreeNode(title, name); 
	if (!root) // Empty Tree
	{
		root = newRoot;
		treeSize++;
	}
	else // Non empty tree
	{
		newRoot->leftmostChild = root;
		root = newRoot;
		treeSize++;
	}
}
/* This will return the size of the tree.  
   Will grow and shrink based on who gets fired and hired.
   Time Complexity: Theta(1) */
unsigned int OrgTree::getSize()
{
	return treeSize;
}

/* Returns the root of the tree.
   Time complexity: Theta(1) */
TREENODEPTR OrgTree::getRoot()
{
	return root;
}

/* Returns the left most child of a given node.
   Time Complexity: Theta(1) */
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node)
{
	if (!node)
		return TREENULLPTR;
	else
		return node->leftmostChild;
}

/* Returns the right sibling of a given node.
   Time Complexity: Theta(1) */
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	if (!node)
		return TREENULLPTR;
	else
		return node->rightSibling;
}

/*Print out the subtree starting at the node the function is passed*/
/*Time complexity: Theta(n)*/
void OrgTree::printSubTree(TREENODEPTR node)
{
	// Print credentials of subtree root
	cout << node->getTitle() << ": " << node->getName() << "\n" << endl;
	if (leftmostChild(node)) 
	{
		// recurse on children and indent
		printSubTreeHelper(leftmostChild(node), 1);
	}
}
/* This function takes in a subtree root to be printed. The int value passed is used to indent the tree 
properly. */
void OrgTree::printSubTreeHelper(TREENODEPTR node, int indent)
{
	for (int i = 0; i < indent; i++)
		printf("\t");
	cout << node->getTitle() << ": " << node->getName() << "\n" << endl;
	if (leftmostChild(node))
		// recurse on children and right siblings
		printSubTreeHelper(leftmostChild(node), indent + 1); // Indents if there are more children
	if (rightSibling(node))
		printSubTreeHelper(rightSibling(node), indent); 
}

/* Determines if the specified node with a matching title is in the tree.*/
/*Time Complexity: Theta(n)*/
TREENODEPTR OrgTree::find(string title)
{
	if (title.compare(root->getTitle()) == 0)
	{
		return root;
	}
	if (leftmostChild(root)) // Check to see if the left child exists and recurse on children
	{
		return findHelper(title, leftmostChild(root));
	}
	else // Node is not in the tree 
	{
		return TREENULLPTR;
	}		
}

/*Used to help the find() method by recursing on the right siblings */
TREENODEPTR OrgTree::findHelper(string title, TREENODEPTR current)
{
	TreeNode *findMe = TREENULLPTR; // iterator node 
	if (title.compare(current->getTitle()) == 0) // Initial check 
	{
		return current;
	}
	if (leftmostChild(current))
	{
		findMe = findHelper(title, leftmostChild(current)); // recurse on children 
	}
	if (rightSibling(current) && !findMe) // Checks to make sure a right sibling exists and that the left subtree has been exhausted
	{
		findMe = findHelper(title, rightSibling(current)); //recurse on right sibling 
	}

	return findMe;
}

/*Reads nodes into an OrgTree via a file. This function should exit if the file could not be opened and/or does not exist, 
or if the file is improperly formatted*/
/*Time Complexity: Theta(n)*/
bool OrgTree::read(string filename)
{
	ifstream readMe(filename);

	if (!readMe.is_open()) // Checks to see if the file exists and exits if it does not 
	{
		cerr << "File cound not be opened." << endl;
		//system("cd");
		return false;
		//return 1;
	}
	else // File can be opened and is readable
	{
		stack<string> ss; // Declare a new stack so I can track who's hiring 
		string title;
		string name; 
		getline(readMe, title, ','); // Parsing the root 
		getline(readMe, name, '\n');
		addRoot(title, name); // adds the root 
		ss.push(title);

		while (readMe.peek() != EOF && !ss.empty()) // makes sure that everything in the file has been read 
		{
			if (readMe.peek() == ')') 
			{
				string notAString;
				getline(readMe, notAString); // consume a new line
				ss.pop();
			}
			else
			{
				getline(readMe, title, ',');
				getline(readMe, name, '\n');
				hire(find(ss.top()), title, name);
			}
		}
		readMe.close();
	}
	return true; // file was successfully read
}

/*This function writes an OrgTree to a file in the same format  */
/*Time Conplexity: Theta(n)*/
void OrgTree::write(string fileName)
{ 
	ofstream writeFile;
	writeFile.open(fileName);

	writeFile << writeHelper(root) << endl;

	writeFile.close();
}

string OrgTree::writeHelper(TREENODEPTR printMe)
{
	if (printMe)
	{
		string line = printMe->getTitle() + ", " + printMe->getName() + "\n";
		line += writeHelper(printMe->leftmostChild);
		line += ")\n";
		line += writeHelper(printMe->rightSibling);

		return line;
	}
	else
	{
		return "";
	}
}

/*Hire an employee. The employee should be added to the tree as the last child of the node pointed to by TREENODEPTR.*/
/*Time Complexity: Theta(n) */
void OrgTree::hire(TREENODEPTR parent, string newTitle, string newName)
{
	TreeNode *newHire = new TreeNode(newTitle, newName); // Node to be added 
	if (!leftmostChild(parent)) // if the TREENODEPTR is a leaf
	{
		parent->leftmostChild = newHire;
		treeSize++;
	}
	else if (leftmostChild(parent)) // If there are existing children in the subtree
	{
		TreeNode *current = parent->leftmostChild;
		while (rightSibling(current)) // while a right sibling exists
		{
			current = current->rightSibling; // iterate through the siblings
		}
		current->rightSibling = newHire; // once broken out of the loop, set the new hire as the last child of the parent 
		treeSize++;
	}	
}

/*Deletes the specified node from the tree. If the node has children, all of its children become children of the deleted nodes boss*/
/*Time Complexity: Theta(n)*/
bool OrgTree::fire(string formerTitle)
{
	TreeNode *fireMe = find(formerTitle);
	TreeNode *boss = findBoss(formerTitle);
	TreeNode *rightmostSibling = TREENULLPTR;
	TreeNode *leftSibling = TREENULLPTR;

	if (!fireMe || root->getTitle().compare(formerTitle) == 0) // If the node you are trying to fire DNE or if it is the root
	{
		return false;
	}
	if (leftmostChild(boss) == fireMe) // If the boss's left most child is the node we are looking for 
	{
		if (!rightSibling(fireMe))
		{
			boss->leftmostChild = fireMe->leftmostChild; // If the boss has only one child 
		}
		else
		{
			rightmostSibling = boss->leftmostChild;
			boss->leftmostChild = fireMe->rightSibling; // Bypass the lmc since its the node we want to get rid off 
			while (rightSibling(rightmostSibling))
			{
				rightmostSibling = rightmostSibling->rightSibling; // Iterate through siblings 
			}
			if (leftmostChild(fireMe))
			{
				rightmostSibling->rightSibling = fireMe->leftmostChild;
			}
		}
		treeSize--;
		delete fireMe;
		return true;
	}
	else // Now will delete fireMe when it is between siblings 
	{
		// Find the left sibling of fireMe
		leftSibling = boss->leftmostChild;
		while (fireMe != leftSibling->rightSibling)
		{
			leftSibling = leftSibling->rightSibling;
		}

		// Find the right most sibling of fireMe
		rightmostSibling = fireMe->rightSibling;
		if (rightmostSibling == TREENULLPTR) // If fireMe is the last of its siblings 
		{
			rightmostSibling = leftSibling; 
		}
		else
		{
			while (rightmostSibling->rightSibling != TREENULLPTR)
			{
				rightmostSibling = rightmostSibling->rightSibling;
			}
		}
		leftSibling->rightSibling = rightmostSibling;
		rightmostSibling->rightSibling = fireMe->leftmostChild;

		treeSize--;
		delete fireMe;
		return true;
	}
}

/*Finds the parent node of the title that the function is passed. */
/*Time Complexity: Theta(n) for same reasons as other functions that have recursion*/
TREENODEPTR OrgTree::findBoss(string title)
{
	if (title.compare(root->getTitle()) == 0)
	{
		return TREENULLPTR;
	}
	if (leftmostChild(root)) // Check to see if the left child exists and recurse on children
	{
		return findBossHelper(title, leftmostChild(root), root);
	}
	else // Node is not in the tree 
	{
		return TREENULLPTR;
	}
}

TREENODEPTR OrgTree::findBossHelper(string title, TREENODEPTR current, TREENODEPTR boss)
{
	TreeNode *findMe = TREENULLPTR; // iterator node 
	if (title.compare(current->getTitle()) == 0) // Initial check 
	{
		return boss;
	}
	if (leftmostChild(current))
	{
		findMe = findBossHelper(title, leftmostChild(current), current); // recurse on children 
	}
	if (rightSibling(current) && !findMe) // Checks to make sure a right sibling exists and that the left subtree has been exhausted
	{
		findMe = findBossHelper(title, rightSibling(current), boss); //recurse on right sibling 
	}
	return findMe;
}

/*Destructor for the org tree*/
/*Time Complexity: Theta(n) */
OrgTree::~OrgTree()
{
	selfDestruct(root);
}

/*This function will do a depth first search and delete the nodes from the bottom*/
/*Time Complexity: Theta(n)*/
void OrgTree::selfDestruct(TREENODEPTR node)
{
	if (leftmostChild(node))
		selfDestruct(node->leftmostChild);
	if (rightSibling(node))
		selfDestruct(node->rightSibling);
	delete node;
}