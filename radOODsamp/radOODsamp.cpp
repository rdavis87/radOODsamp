/*START OF SPECIFICATIONS***************************************************
*
* Projec Name:  radOOdsamp            - Sample code showing some c++ object oriented design
*
* File Name: radOOdsamp.cpp
*
*
* DESCRIPTION: This file contains code to to create some classes
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
* Person::Print                       - Function to output to the screen the person attributes.
* CreateRandomPerson                  - Function to create a new instance of a person with random data.
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
enum Gender {FEMALE, MALE, UNKNOWN};

/* some names to use when creating instances of person class */
#define MAX_NAMES 10
char *FemaleNames[] = { "Abigail", "Barbara", "Cathy", "Debbie", "Elaine", "Faith", "Gail", "Haley", "Ida", "Jade" };
char *MaleNames[] = { "Asron", "Bill", "Carson", "David", "Evan", "Frank", "Gerald", "Hal", "Ike", "Keith" };
char *GenderNeutralNames[] = { "Alex", "Brook", "Cameron", "Dana", "Eli", "Finley", "Grabriel", "Hudson", "Jamie", "Kelly" };

/* abstract class to define some basic human attributes */
class Human {
private:
	std::string Name;
	int Height;  // in inches
	int Weight;  // in pounds
	HairColor HairColor;
	EyeColor EyeColor;
public:
//	Human(std::string n = "noname", int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN) {
//		Name = n, Height = h, Weight = w, HairColor = hc, EyeColor = ec; };
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec) { Name = n, Height = h, Weight = w, HairColor = hc, EyeColor = ec; };
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec) { n = Name, h = Height, w = Weight, hc = HairColor, ec = EyeColor; };
	virtual Human::~Human() = 0;
};

inline Human::~Human() {}  // needed for abstract class to resolve link issues

/* make female, male and unknown gender classes inheriting from human */
class Female: private Human {
private:
	int ShoeSize;
	int DressSize;
public:
	Female(std::string &n, int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, int ss = 7, int ds = 6)
	{ 
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, DressSize = ds; // update attributes in human class and those specific to female
	};
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &ds)
	{ 
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, DressSize = ds;  // allow change of attributes 
	};
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &ds)
	{	
		Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, ds = DressSize;  // retrieve current attributes
	};
};

class Male : private Human {
private:
	int ShoeSize;
	int CoatSize;
public:
	Male(std::string &n, int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, int ss = 9, int cs = 42)
	{
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatSize = cs;  // update attributes in human class and those specific to male
	};
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &cs)
	{	
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatSize = cs;  // allow change of attributes 
	};
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &cs)
	{	
		Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, cs = CoatSize;  // retrieve current attributes
	};
};

class Unknown : private Human {
private:
	int ShoeSize;
	int CoatDressSize;
public:
	Unknown(std::string &n, int h = 68, int w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, int ss = 0, int d_cs = 0)
	{ 
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatDressSize = d_cs;  // update attributes in human class and those specific to unknown
	};
	void SetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs)
	{
		Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, CoatDressSize = d_cs;  // allow change of attributes 
	};
	void GetAttributes(std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs)
	{
		Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, d_cs = CoatDressSize;  // retrieve current attributes
	};
};

/* the person object doesn't inherit anything, but creates instances of the female, make and unknown classes */
class Person {
private:
	union {
		Female  *f;
		Male    *m;
		Unknown *u;
	};
	int  NumKids;
	bool Employed;
	enum Gender Gender;
public:
	/* construct a person object */
	Person(enum Gender g, std::string &n, int &h, int &w, enum HairColor &hc, enum EyeColor &ec, int &ss, int &d_cs, int &nk, bool emp) {
		/* set the specific attributes of the person object */
		Gender = g;
		NumKids = nk;
		Employed = emp;
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
			Gender = UNKNOWN;  // gender parameter invalid, set gender to unknown and fall through to the unknown gender case to finish creation
		case UNKNOWN:
			u = new Unknown(n, h, w, hc, ec, ss, d_cs);  // create an unknown gender object
		}
	}
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
		case UNKNOWN:
			u->SetAttributes(n, h, w, hc, ec, ss, d_cs);  // fill in the attributes of the unknown gender object
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
		case UNKNOWN:
			u->GetAttributes(n, h, w, hc, ec, ss, d_cs);  // get the attributes of the unknown object
		}
	}
	void Print();
	~Person() { delete f; }  // pointers are in a union so can call delete on any one of them
};

/*
** Person::Print - Function to output to the screen the person attributes.
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
	case UNKNOWN:
		this->u->GetAttributes(Name, Height, Weight, HairColor, EyeColor, ShoeSize, CoatDressSize);
		std::cout << "unknown gender, named ";
		ClotheSizeDesc = ", clothing size ";
		break;
	}
	std::cout << Name << ", height " << Height << ", weight " << Weight << ", hair color " << HairColorStrings[HairColor]
		<< ", eye color " << EyeColorStrings[EyeColor] << ", shoe Size " << ShoeSize << ClotheSizeDesc << CoatDressSize <<
		", number of kids " << this->NumKids << ", employed " << (this->Employed ? "Yes" : "No") << std::endl;
}

/*
** CreateRandomPerson - Function to create a new instance of a person with random data.
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

	/* set the gender specific attributes */
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
	case UNKNOWN:
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

int main()
{
	Person * p;
	srand((unsigned int)time(NULL)); // seed the random number generator

	for (int i = 0; i < 5; i++) {
		p = CreateRandomPerson();
		p->Print();
		std::cout << std::endl;
		delete p;
	}
    return 0;
}

