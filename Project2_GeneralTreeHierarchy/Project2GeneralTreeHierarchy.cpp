#include "stdafx.h"
#include "Orgtree.h"

#include <string>
#include <iostream>
using namespace std;

// This is not the complete test harness/driver for project 2, but
// is a good starting point.  You should test your project completely
// by adding additional tests for each item in the grading rubric!

int main() {
	OrgTree o1, o2;

	// Adding roots should make a linear tree
	o1.addRoot("R1", "R1");
	o1.addRoot("R2", "R2");
	o1.addRoot("R3", "R3");
	o1.getRoot(); // Should return R3

	o1.printSubTree(o1.getRoot()); //printSubTree from root
	o1.find("R3");
	
	//add two children to root
	o1.hire(o1.getRoot(), "R3C1", "R3C1");
	//o1.printSubTree(o1.getRoot());
	o1.hire(o1.getRoot(), "R3C2", "R3C2");
	//o1.printSubTree(o1.getRoot());
	o1.hire(o1.getRoot(), "R3C3", "R3C3");
	o1.printSubTree(o1.getRoot());

	//cout << o1.find("R3C1") << endl;
	//cout << o1.find("R3C2") << endl;

	//OrgTree::TreeNode *test = new OrgTree::TreeNode("test1", "test1");
	//OrgTree::TreeNode *test2 = new OrgTree::TreeNode("Test2", "Test2");
	//test->rightSibling = test2;
	//cout << o1.find("Test2") << endl;
	//cout << o1.rightSibling(test)<<endl;

	o1.hire(o1.find("R3C1"), "R3C1C1", "R3C1C1"); //test find on leaf node and hire to it

	o1.printSubTree(o1.getRoot());


	cout << o1.getSize() << endl;
	o1.printSubTree(o1.getRoot()); //printSubTree from root


	o1.fire("R2");
	o1.fire("R3C1"); //fire an internal node
	o1.fire("R3C1C1");
	cout << o1.getSize() << endl; 
	o1.printSubTree(o1.getRoot());

	// Write out a tree and read it back in to a new tree, then print
	o1.write("output.txt");
	//o2.read("output.txt");
	//o2.printSubTree(o2.getRoot()); //printSubTree from root

	system("PAUSE");
	return 0;

}
