/**
* @file HW04dwyermwApp.cpp
* CSE 274 - Fall 2012
* My solution for HW04
*
* @author Matthew Dwyer
* @date 10/29/12
*
* @note This file is (c) 2012. It is licensed under the
* CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
* which means you are free to use, share, and remix it as long as you
* give attribution. Commercial uses are allowed.
*
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <fstream>
#include <iostream>
#include "Starbucks.h"
#include "dwyermwStarbucks.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class HW04dwyermwApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	// A dwyermwStarbucks object, which allows for the data to be loaded,
	// the structure to be built, and the nearest locaiton to be found.
	dwyermwStarbucks* star;
};

void HW04dwyermwApp::setup()
{
	star = new dwyermwStarbucks();
	Entry* e = star->getNearest(0.0, 0.0);
	console() << "Identifier = " << e->identifier << ", X = " << e->x << ", Y = " << e->y;
	Entry* e1 = star->getNearest(0.1, 0.1);
	console() << "Identifier = " << e1->identifier << ", X = " << e1->x << ", Y = " << e1->y;
	Entry* e2 = star->getNearest(0.2, 0.2);
	console() << "Identifier = " << e2->identifier << ", X = " << e2->x << ", Y = " << e2->y;
	Entry* e3 = star->getNearest(0.3, 0.3);
	console() << "Identifier = " << e3->identifier << ", X = " << e3->x << ", Y = " << e3->y;
	Entry* e4 = star->getNearest(0.4, 0.4);
	console() << "Identifier = " << e4->identifier << ", X = " << e4->x << ", Y = " << e4->y;
	Entry* e5 = star->getNearest(0.5, 0.5);
	console() << "Identifier = " << e5->identifier << ", X = " << e5->x << ", Y = " << e5->y;
	Entry* e6 = star->getNearest(0.6, 0.6);
	console() << "Identifier = " << e6->identifier << ", X = " << e6->x << ", Y = " << e6->y;
	Entry* e7 = star->getNearest(0.7, 0.7);
	console() << "Identifier = " << e7->identifier << ", X = " << e7->x << ", Y = " << e7->y;
	Entry* e8 = star->getNearest(0.8, 0.8);
	console() << "Identifier = " << e8->identifier << ", X = " << e8->x << ", Y = " << e8->y;
	Entry* e9 = star->getNearest(0.9, 0.9);
	console() << "Identifier = " << e9->identifier << ", X = " << e9->x << ", Y = " << e9->y;
	Entry* e10 = star->getNearest(1.0, 1.0);
	console() << "Identifier = " << e10->identifier << ", X = " << e10->x << ", Y = " << e10->y;
	system("PAUSE");
	//cout << cin << endl;
}

void HW04dwyermwApp::mouseDown( MouseEvent event )
{
}

void HW04dwyermwApp::update()
{
}

void HW04dwyermwApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04dwyermwApp, RendererGl )
