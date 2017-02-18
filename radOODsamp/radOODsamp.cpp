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
* RandomDataFill                    - Function to fill in a Data structure with random data.
*
* CHANGE LOG:
*
* DATE       FLAG	       Ref. No.	    CHANGE DESCRIPTION
* ----       ----------    --------	    -------------------------------------
* 02/17/17   V10RAD00 	                Initial coding
*
*END OF SPECIFICATIONS*******************************************************/
#include "stdafx.h"
#include <string>

/* a few physical human attributes for this sample */
enum HairColor {BLONDE, BRUNETTE, RED};
enum EyeColor {BLUE, GREEN, BROWN};

/* abstract class to define some basic human attributes */
class Human {
private:
	std::string Name;
	double Height;  // in inches
	double Weight;  // in pounds
	HairColor HairColor;
	EyeColor EyeColor;
public:
//	Human(double h = 68, double w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN) { Height = h, Weight = w, HairColor = hc, EyeColor = ec; };
	void SetAttributes(std::string &n, double &h, double &w, enum HairColor &hc, enum EyeColor &ec) { Name = n, Height = h, Weight = w, HairColor = hc, EyeColor = ec; };
	void GetAttributes(std::string &n, double &h, double &w, enum HairColor &hc, enum EyeColor &ec) { n = Name, h = Height, w = Weight, hc = HairColor, ec = EyeColor; };
	virtual ~Human() = 0; // makes human an abstract class that cannot be instantiated by itself
};

//inline Human::~Human() {}

/* make male and female classes inheriting from human */
class Female: private Human {
private:
	double ShoeSize;
	int DressSize;
public:
	Female(std::string &n, double h = 68, double w = 140, enum HairColor hc = BRUNETTE, enum EyeColor ec = BROWN, double ss = 8, int ds = 6)
	      { Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, DressSize = ds; };
	void SetAttributes(std::string &n, double &h, double &w, enum HairColor &hc, enum EyeColor &ec, double &ss, int &ds)
	                  { Human::SetAttributes(n, h, w, hc, ec), ShoeSize = ss, DressSize = ds;};
	void GetAttributes(std::string &n, double &h, double &w, enum HairColor &hc, enum EyeColor &ec, double &ss, int &ds)
	                  {	Human::GetAttributes(n, h, w, hc, ec), ss = ShoeSize, ds = DressSize;};
};

/*
** RandomDataFill - Function to fill in a Data structure with random data.
**
**   Parameters:
**      Data - reference to a data structure to fill in.
**
** - Return value: none.
*/
int main()
{
    return 0;
}

