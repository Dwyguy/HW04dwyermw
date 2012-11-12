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
#include "Resources.h"
#include "cinder/gl/Texture.h"
#include "cinder\ImageIo.h"
#include "Node.h"
#include "CensusEntry.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04dwyermwApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void drawPoint(Node* r);
	void clearSurface();
	void censusDataReader();

private:
	// A dwyermwStarbucks object, which allows for the data to be loaded,
	// the structure to be built, and the nearest locaiton to be found.
	dwyermwStarbucks* star;
	Surface* mySurface_;
	uint8_t* pixels;

	//gl::Texture* picture_;

	static const int appHeight = 640;
	static const int appWidth = 1024;
	static const int surfaceSize = 1024;

	
};

void HW04dwyermwApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void HW04dwyermwApp::setup()
{
	star = new dwyermwStarbucks();
	
	mySurface_ = new Surface(surfaceSize, surfaceSize, true);
	pixels = (*mySurface_).getData();
	clearSurface();
	drawPoint(star->root);
	
	// Create loop in here that reads in all data from the tree, and puts it into a list of locations to
	// draw on the picture.  Preferably a 2-d array.
}

void HW04dwyermwApp::censusDataReader()
{
	ifstream in("Census_2000.csv");

	vector<CensusEntry> storage;
	char seperator;
	int d;
	int pop = 0; // Population
	int xPop = 0; // X coordinate of population
	int yPop = 0; // Y coordinate of population
	int count = 0;

	while(in.good())
	{
		in >> d;
		in >> seperator;
		in >> d;
		in >> seperator;
		in >> d;
		in >> seperator;
		in >> d;
		in >> seperator; // Gets past the first four columns

		CensusEntry* e = new CensusEntry();
		storage.push_back(*e);
		in >> pop;
		storage[count].population = pop;


	}
}

void HW04dwyermwApp::drawPoint(Node* r)
{
	
	Color8u c = Color8u(0, 0, 255);

	if(r == NULL)
		return;

	drawPoint(r->left);

	int xPos = floor(r->key->x * appWidth) + 10;
	int yPos = floor((1 - r->key->y) * appHeight * 0.8) + 50;

	if(4 * (yPos * surfaceSize + xPos) < 0)
		return;
	if(4 * (yPos * surfaceSize + xPos) > surfaceSize * surfaceSize * 4)
		return ;

	pixels[4 * (yPos * surfaceSize + xPos)] = c.r;
	pixels[4 * (yPos * surfaceSize + xPos)] = c.g;
	pixels[4 * (yPos * surfaceSize + xPos)] = c.b;

	drawPoint(r->right);
	
	draw();
}

void HW04dwyermwApp::clearSurface()
{
	Color8u c = Color8u(0, 0, 0);
	for(int x = 0; x < surfaceSize; x++)
		for(int y = 0; y < surfaceSize; y++)
		{
			int index = 4 * (y * surfaceSize + x);
			pixels[index] = c.r;
			pixels[index + 1] = c.g;
			pixels[index + 2] = c.b;
		}
}

void HW04dwyermwApp::mouseDown( MouseEvent event )
{
	Color8u c = Color8u(0, 255, 0);

	int xPos = event.getX();
	int yPos = event.getY();

	// Convert to the 0 to 1 scale
	double xConverted = (((double)xPos) - 10) / appWidth;
	double yConverted = 1 - ((((double)yPos) - 50) / (appHeight * 0.8));

	int index = 4 * (yPos * surfaceSize + xPos);
	pixels[index] = c.r;
	pixels[index + 1] = c.g;
	pixels[index + 2] = c.b;

	Entry* nearest = star->getNearest(xConverted, yConverted);
	// Go from converted scale to pixels
	xPos = floor(appWidth * nearest->x) + 10;
	yPos = (floor(appHeight * (1 - nearest->y) * 0.8) + 50);

	index = 4 * (yPos * surfaceSize + xPos);
	pixels[index] = c.r;
	pixels[index + 1] = c.g;
	pixels[index + 2] = c.b; 
}

void HW04dwyermwApp::update()
{
	

}

void HW04dwyermwApp::draw()
{
	
	//gl::draw(*myTexture_);
	//gl::Texture picture( loadImage( loadResource( RES_IMG) ) );
	//gl::draw(picture);
	//gl::drawSolidRect(Rectf(100, 100, 120, 120), 0.2F);
	
	gl::draw(*mySurface_);
	//gl::clear(Color(0, 0, 0));
}

CINDER_APP_BASIC( HW04dwyermwApp, RendererGl )
