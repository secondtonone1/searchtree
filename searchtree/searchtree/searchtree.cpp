// searchtree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include "treeclass.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//int array[6]={7,4,9,8,3,5};
	int array[6]={7,4,2,5,3,8};
	list<int> mylist;
	mylist.insert(mylist.end() , array ,array+6);

	TreeClass treeClass;
	treeClass.initial(mylist);
	treeClass.visitTree();
	cout << endl;
	treeClass.eraseNode(7);
	treeClass.visitTree();
	cout << endl;
	treeClass.eraseNode(4);
	treeClass.visitTree();
	cout << endl;
	
	int array2[5]={7,4,2,5,8};
	list<int> mylist2;
	mylist2.insert(mylist2.end() , array2 ,array2+5);
	TreeClass treeClass2;
	treeClass2.initial(mylist2);
	treeClass2.visitTree();
	cout << endl;
	treeClass2.eraseNode(4);
	treeClass2.visitTree();
	cout << endl;

	/////////////////////
	int array3[6]={7,4,2,6,5,8};
	list<int> mylist3;
	mylist3.insert(mylist3.end() , array3 ,array3+6);
	TreeClass treeClass3;
	treeClass3.initial(mylist3);
	treeClass3.visitTree();
	cout << endl;
	treeClass3.eraseNode(7);
	treeClass3.visitTree();
	cout << endl;

	//////////////////////

	getchar();
	return 0;

}

