/*START OF SPECIFICATIONS***************************************************
*
* Projec Name:  radOOdsamp            - Sample code showing some c++ object oriented design.  The objective of this project is to 
*                                       remind me of the most useful things available when using classes.  After creating the classes
*                                       it seemed like I should do something with them.  I have not done anything with binary trees
*                                       lately so that seemed like a worthwhile effort.
*
* File Name: radOOdsamp.cpp
*
*
* DESCRIPTION: This file contains code to to create some classes and put the created objects into a binary tree
*
* Copyright (C) <2017> <Robert A. Davis>
* All rights reserved.
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE.TXT file for details.
*
* FUNCTIONS/ACTIONS IN
* THIS FILE:
*
* Person::Print                       - function to output to the screen the person attributes
* CreateRandomPerson                  - function to create a new instance of a person with random data
* BtreePrintPerson                    - function passed to binary tree implementation to print a person object
* AddBtreeNode                        - function to add a binary tree node to the tree
* AddElementToTree                    - function to allocate a new node and add to the tree
* DeleteBtreeElement                  - function to recursively delete the binary tree nodes and free memory
* DeleteTree                          - function to delete the binary tree
* ReverseTree                         - function to use recursion to reverse sort the tree
* PrintTree                           - function to use recursion to output the data in the tree as sorted
*
* CHANGE LOG:
*
* DATE       FLAG	       Ref. No.	    CHANGE DESCRIPTION
* ----       ----------    --------	    -------------------------------------
* 02/17/17   V10RAD00 	                Initial coding
*
*END OF SPECIFICATIONS*******************************************************/
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

/* a few physical human attributes for this sample */
enum HairColor {BLONDE, BRUNETTE, RED};
char *HairColorStrings[] = { "Blonde", "Brunette", "Red" };
enum EyeColor {BLUE, GREEN, BROWN};
char *EyeColorStrings[] = { "Blue", "Green", "Brown" };
enum Gender {FEMALE, MALE, TRANSGENDER};

/* some names to use when creating instances of person class */
#define MAX_NAMES 10
char *FemaleNames[] = { "Abigail", "Barbara", "Cathy", "Debbie", "Elaine", "Faith", "Gail", "Haley", "Ida", "Jade" };
char *MaleNames[] = { "Asron", "Bill", "Carson", "David", "Evan", "Frank", "Gerald", "Hal", "Ike", "Keith" };
char *GenderNeutralNames[] = { "Alex", "Brook", "Cameron", "Dana", "Eli", "Finley", "Grabriel", "Hudson", "Jamie", "Kelly" };

/*
* The following classes provide examples of using inheritance, and polymorphism with abstract classes and virtual functions.
*/

/* abstract class to define some basic human attributes */
class Human {
private:
	std::string Name;
	int Height;  // in inches
	int Weight;  // in pounds
	HairColor HairColor;
	EyeColor EyeColor;
public:
	/* constructor, not needed for an abstract class provided for completeness */
	Human(std::string n = "noname", int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN) {
	Name = n, Height = h, Weight = w, HairColor = hc, EyeColor = ec; };  
	/* functions to get and set private attribute variables */
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec) { Name = n, Height = h, Weight = w, HairColor = hc, EyeColor = ec; };
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec) { n = Name, h = Height, w = Weight, hc = HairColor, ec = EyeColor; };
	/* virtual funtion to be replaced in the various classes that inherit the human object */
	virtual void WhatAmI() { std::cout << "I am human" << std::endl; }  
	virtual Human::~Human() = 0; // make an abstract class out of human
};

inline Human::~Human() {}  // needed for abstract class to resolve link issues

/* make female, male and transgender classes inherit from human */
class Female: private Human {
private:
	int ShoeSize;
	int DressSize;
public:
	/* female object constructor */
	Female(std::string &n, int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, int ss = 7, int ds = 6)
	{ 
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, DressSize = ds; // update attributes in human class and those specific to female
	};
	/* funtions to set and get the attributes of this object */
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &ds)
	{ 
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, DressSize = ds;  // allow change of attributes 
	};
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &ds)
	{	
		Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, ds = DressSize;  // retrieve current attributes
	};
	/* override of human virtual funtion for this class */
	void WhatAmI() { std::cout << "I am a female" ; }// replacement function for human virtual WhatAmI function
};

class Male : private Human {
private:
	int ShoeSize;
	int CoatSize;
public:
	/* male object constructor */
	Male(std::string &n, int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, int ss = 9, int cs = 42)
	{
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatSize = cs;  // update attributes in human class and those specific to male
	};
	/* funtions to set and get the attributes of this object */
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &cs)
	{	
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatSize = cs;  // allow change of attributes 
	};
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &cs)
	{	
		Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, cs = CoatSize;  // retrieve current attributes
	};
	/* override of human virtual funtion for this class */
	void WhatAmI() { std::cout << "I am a male" ; }  // replacement function for human virtual WhatAmI function
};

class TransGender : private Human {
private:
	int ShoeSize;
	int CoatDressSize;
public:
	/* transgender object constructor */
	TransGender(std::string &n, int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, int ss = 0, int d_cs = 0)
	{ 
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatDressSize = d_cs;  // update attributes in human class and those specific to transgender
	};
	/* funtions to set and get the attributes of this object */
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs)
	{
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatDressSize = d_cs;  // allow change of attributes 
	};
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs)
	{
		Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, d_cs = CoatDressSize;  // retrieve current attributes
	};
	/* override of human virtual funtion for this class */
	void WhatAmI() { std::cout << "I am a transgender" ; }  // replacement function for human virtual WhatAmI function
};

/* the person object doesn't inherit anything, but creates instances of the female, male and transgender objects as needed */
class Person {
private:
	/* create a single pointer to the gender determined object accessed through the union for the different classes */
	union {
		Female      *f;
		Male        *m;
		TransGender *t;
	};
	int  NumKids;
	bool Employed;
	enum Gender Gender;
	long IdNum;  // sort key
	static long NextIdNum;  // give every person object a unique number for sorting
public:
	/* construct a person object */
	Person(enum Gender g, std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs, int &nk, bool emp) {
		/* set the specific attributes of the person object */
		Gender = g;
		NumKids = nk;
		Employed = emp;
		IdNum = NextIdNum++;  // assign an id number to this person and increment the static variable
		/* create gender specific object */
		switch (g)
		{
		case FEMALE:
			f = new Female(n, h, w, hc, ec, ss, d_cs);  // create a female object
			break;
		case MALE:
			m = new Male(n, h, w, hc, ec, ss, d_cs);  // create a male object
			break;
		default:
			Gender = TRANSGENDER;  // gender parameter invalid, set gender to transgender and fall through to the transgender case to finish creation
		case TRANSGENDER:
			t = new TransGender(n, h, w, hc, ec, ss, d_cs);  // create an transgender object
			break;
		}
	}

	/* funtions to set and get the attributes of this object */
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs, int &nk, bool emp) {
		/* set the specific attributes of the person object */
		NumKids = nk;
		Employed = emp;
		/* set the gender specific attributes */
		switch (Gender)
		{
		case FEMALE:
			f->SetAttributes(n, h, w, hc, ec, ss, d_cs);  // fill in the attributes of the female object
			break;
		case MALE:
			m->SetAttributes(n, h, w, hc, ec, ss, d_cs);  // fill in the attributes of the male object
			break;
		case TRANSGENDER:
			t->SetAttributes(n, h, w, hc, ec, ss, d_cs);  // fill in the attributes of the transgender object
		}
	}
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs, int &nk, bool emp) {
		/* get the specific attributes of the person object */
		nk = NumKids;
		emp = Employed;
		/* get the gender specific attributes */
		switch (Gender)
		{
		case FEMALE:
			f->GetAttributes(n, h, w, hc, ec, ss, d_cs);  // get the attributes of the female object
			break;
		case MALE:
			m->GetAttributes(n, h, w, hc, ec, ss, d_cs);  // get the attributes of the male object
			break;
		case TRANSGENDER:
			t->GetAttributes(n, h, w, hc, ec, ss, d_cs);  // get the attributes of the transgender object
		}
	}

	long GetIdNum() { return IdNum; } // get the sort key
	void Print();  // print out the person object 
	/*
	* Because WhatAmI is a virtual function it gets replaced by the object specific one whenever a class
	* is instantiated.  The gender based class pointers are in a union meaning they all occupy the same 
	* place in storage.  The following function call could therefore use any of the pointers in the union
	* and it will still call the proper funtion based on the object type 
	*/
	void WhatAmI() { f->WhatAmI(), std::cout << " person" << std::endl; }
	~Person() { delete f; }  // pointers are in a union so can call delete on any one of them
};

long Person::NextIdNum = 1;  // give every person object a unique number for sorting

/*
** Person::Print - function to output to the screen the person attributes
**
**   Parameters:
**     none
**
** - Return value: none.
*/
void Person::Print() {
	std::string Name, ClotheSizeDesc;
	int Height;  // in inches
	int Weight;  // in pounds
	enum HairColor HairColor;
	enum EyeColor EyeColor;
	int ShoeSize;
	int CoatDressSize;
	int NumKids = (rand() % 6);
	bool Employed = (rand() % 2) ? true : false;

	WhatAmI(); // call the virtual function that will print a object specific message
	std::cout << "Id number " << GetIdNum() << ", ";
	/* format the output based on the gender of the person */
	switch (this->Gender) {
	case FEMALE:
		this->f->GetAttributes(Name, Height, Weight, HairColor, EyeColor, ShoeSize, CoatDressSize);
		std::cout << "female named ";
		ClotheSizeDesc = ", dress size ";
		break;
	case MALE:
		this->m->GetAttributes(Name, Height, Weight, HairColor, EyeColor, ShoeSize, CoatDressSize);
		ClotheSizeDesc = ", coat size ";
		std::cout << "male named ";
		break;
	case TRANSGENDER:
		this->t->GetAttributes(Name, Height, Weight, HairColor, EyeColor, ShoeSize, CoatDressSize);
		std::cout << "transgender named ";
		ClotheSizeDesc = ", clothing size ";
		break;
	}
	std::cout << Name << ", height " << Height << ", weight " << Weight << ", hair color " << HairColorStrings[HairColor]
		<< ", eye color " << EyeColorStrings[EyeColor] << ", shoe Size " << ShoeSize << ClotheSizeDesc << CoatDressSize <<
		", number of kids " << this->NumKids << ", employed " << (this->Employed ? "Yes" : "No") << std::endl << std::endl;
}

/*
** CreateRandomPerson - function to create a new instance of a person with random data
**
**   Parameters:
**     none
**
** - Return value: new person instance.
*/
Person *CreateRandomPerson() {
	std::string Name;
	int Height;  // in inches
	int Weight;  // in pounds
	enum HairColor HairColor = (enum HairColor)(rand() % 3);
	enum EyeColor EyeColor = (enum EyeColor)(rand() % 3);
	int ShoeSize;
	int CoatDressSize;
	enum Gender Gender = (enum Gender)(rand() % 3);
	int NumKids = (rand() % 6);
	bool Employed = (rand() % 2) ? true : false;
	Person *p;

	/* create the gender specific attributes in a random fashion */
	switch (Gender)
	{
	case FEMALE:
		Name = FemaleNames[rand() % MAX_NAMES];
		ShoeSize = 5 + (rand() % 4);  
		CoatDressSize = 2 + (rand() % 10);
		Height = 60 + (rand() % 20);
		Weight = 80 + (rand() % 150);
		break;
	case MALE:
		Name = MaleNames[rand() % MAX_NAMES];
		Height = 65 + (rand() % 24);
		Weight = 140 + (rand() % 150);
		CoatDressSize = 40 + (rand() % 8);
		ShoeSize = 8 + (rand() % 4);
		break;
	case TRANSGENDER:
		Name = GenderNeutralNames[rand() % MAX_NAMES];
		Height = 60 + (rand() % 24);
		Weight = 80 + (rand() % 150);
		ShoeSize = 5 + (rand() % 7);
		CoatDressSize = (rand() % 2) ? 2 + (rand() % 10) : CoatDressSize = 40 + (rand() % 8); // randomly make size for either a dress or a coat
	}
	/* allocate a new person object and return the pointer */
	p = new Person(Gender, Name, Height, Weight, HairColor, EyeColor, ShoeSize, CoatDressSize, NumKids, Employed);
	return(p);
}

/*
** BtreePrintPerson - function passed to binary tree implementation to print a person object
**
**   Parameters:
**     Data  - pointer to a person object which was stored as a void pointer in binary tree element
**
** - Return value: none.
*/
void BtreePrintPerson(void *Data) {
	Person *p = (Person *)Data;
	p->Print();
}

/* 
*  generic binary tree implementation using plain C code
*/
/* Structure to create a binary tree for person objects */
struct BtreeNode {
	long Key;        // search key
	void(*Print)(void *);  // pointer to the objects print function used when printing the tree can be null if no printing is required	Person *p;
	void *Data;
	BtreeNode *llink;
	BtreeNode *rlink;
};

/*
** AddBtreeNode - function to add a binary tree node to the tree
**
**   Parameters:
**     Head  - node pointer to head of the tree (during recursive calls this could be a branch not the actual tree head
**     Node  - pointer to btree node to add to the tree
**
** - Return value: none.
*/
void AddBtreeNode(BtreeNode **Head, BtreeNode *Node) {
	/* if the head is empty put the new node into head to start the tree */
	if (*Head == NULL) { *Head = Node; return; }
	else /* does the node go to the left of the head */
		if (Node->Key < (*Head)->Key) { AddBtreeNode(&(*Head)->llink, Node); return; } // use recursion to add the node on the left branch
		else { AddBtreeNode(&(*Head)->rlink, Node); return; } // use recursion to add the node on the right branch
}

/*
** AddElementToTree - function to allocate a new node and add to the tree
**
**   Parameters:
**     Head  - node pointer to head of the tree
**     Key   - search key value
**     Data  - data pointer to be stored in a new node 
**     Print - pointer to a function to handle printing tree elements
**
** - Return value: true if node successfully added.
*/
bool AddElementToTree(BtreeNode **Head, long Key, void *Data, void (*Print)(void *)) {
	BtreeNode *Node = new BtreeNode;  // get a new node

	if (Node != NULL) {
		/* get the node ready to add to the tree */
		Node->llink = Node->rlink = NULL;
		Node->Data = Data;
		Node->Key = Key;
		Node->Print = Print;
		AddBtreeNode(Head, Node);  // add the node
		return true;
	}
	else { return false; } // could not get memory for the node
}

/*
** DeleteBtreeElement - function to recursively delete the binary tree nodes and free memory
**
**   Parameters:
**     Head  - node pointer to head of the tree
**
** - Return value: none.
*/
void DeleteBtreeElement(BtreeNode *Head) {
	/* if head is null then return thus ending the recursion */
	if (Head == NULL) { return; }
	/* delete data on the left branch */
	DeleteBtreeElement(Head->llink);
	/* delete data on the right branch */
	DeleteBtreeElement(Head->rlink);
	std::cout << "deleting element with key " << Head->Key << std::endl;
	/* now free up the data pointer and node memory */
	delete Head->Data;
	delete Head;
}

/*
** DeleteTree - function to delete the binary tree 
**
**   Parameters:
**     Head  - node pointer to head of the tree
**
** - Return value: none.
*/
void DeleteTree(BtreeNode **Head) {
	DeleteBtreeElement(*Head); // delete the tree 
	*Head = NULL;              // set the head to NULL
}

/*
** ReverseTree - function to use recursion to reverse sort the tree
**
**   Parameters:
**     Head  - node pointer to head of the tree
**
** - Return value: none.
*/
void ReverseTree(BtreeNode **Head) {
	BtreeNode *Temp;

	/* if head is null then return thus ending the recursion */
	if (*Head == NULL) { return; }
	/* reverse data on the left branch */
	ReverseTree(&(*Head)->llink);
	/* reverse data on the right branch */
	ReverseTree(&(*Head)->rlink);
	/* reversee the links on the current node */
	Temp = (*Head)->rlink;
	(*Head)->rlink = (*Head)->llink;
	(*Head)->llink = Temp;
}

/*
** PrintTree - function to use recursion to output the data in the tree as sorted
**
**   Parameters:
**     Head  - node pointer to head of the tree
**
** - Return value: none
*/
void PrintTree(BtreeNode *Head) {
	/* if head is null then return thus ending the recursion */
	if (Head == NULL) { return; }
	/* print data on the left branch */
	if (Head->llink != NULL) { PrintTree(Head->llink); }
	/* print the data on this node */
	if (Head->Print != NULL) { (*Head->Print)(Head->Data); }
	/* print data on the right branch */
	PrintTree(Head->rlink);
}

int main()
{
	Person * p;
	BtreeNode *Head = NULL;

	srand((unsigned int)time(NULL)); // seed the random number generator
	/* create some person objects and add them to a binary tree */
	for (int i = 0; i < 5; i++) {
		p = CreateRandomPerson();
		if (AddElementToTree(&Head, p->GetIdNum(), p, &BtreePrintPerson) == false) { std::cout << "adding to tree failed" << std::endl; }
	}
	/* tree was built in ascending order */
	std::cout << "printing tree sort ascending " << std::endl;
	PrintTree(Head);
	/* reverse the tree to descending order */
	ReverseTree(&Head);
	std::cout << "printing tree sort descending " << std::endl;
	PrintTree(Head);
	DeleteTree(&Head);   // delete the tree
    return 0;
}

