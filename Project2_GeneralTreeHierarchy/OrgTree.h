#pragma once
#include <string>	

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

using namespace std;

class OrgTree
{
public:
	class TreeNode 
	{
	public:
		TreeNode *leftmostChild;
		TreeNode *rightSibling;

		TreeNode() // Default Constructor
		{
			title = "Invalid Title";
			name = "Invalid Name";

			leftmostChild = TREENULLPTR;
			rightSibling = TREENULLPTR;
		}

		TreeNode(string newTitle, string newName)
		{
			title = newTitle;
			name = newName;

			leftmostChild = TREENULLPTR;
			rightSibling = TREENULLPTR;
		}

		string getTitle();
		string getName();

	private:
		string title;
		string name;
	};

	OrgTree(); // Default constructor

	void addRoot(string, string); // Adds a root if the tree is empty, continues to stack them if not empty
	unsigned int getSize(); // Return size of tree

	TreeNode* getRoot(); // Returns the root of the whole tree
	TREENODEPTR leftmostChild(TREENODEPTR); // Given a node, provides a pointer to the leftmost child
	TREENODEPTR rightSibling(TREENODEPTR); // Given a node, provides a pointer to the nodes right sibling

	void printSubTree(TREENODEPTR); // Provides the complete subtree for the specified node 
	void printSubTreeHelper(TREENODEPTR, int); // This method gets called in the printSubTree method and is used to print the right side of a subtree

	TREENODEPTR find(string); // Returns a TreeNode pointer if the specified Title is in the tree.
	TREENODEPTR findHelper(string, TREENODEPTR);

	bool read(string);
	void write(string);
	string writeHelper(TREENODEPTR);

	void hire(TREENODEPTR, string, string);
	bool fire(string);

	TREENODEPTR findBoss(string);
	TREENODEPTR findBossHelper(string, TREENODEPTR, TREENODEPTR);

	~OrgTree(); // Destructor needs to go through the tree and delete each node. Probably be best to start deleting from the bottom.
	void selfDestruct(TREENODEPTR);

private:
	int treeSize;
	TreeNode* root;
};

