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
	void drawCensusPoint(double x, double y, Color c);
	void findCensusDifference();

private:
	// A dwyermwStarbucks object, which allows for the data to be loaded,
	// the structure to be built, and the nearest locaiton to be found.
	dwyermwStarbucks* star;
	Surface* mySurface_;
	uint8_t* pixels;
	vector<CensusEntry> storage2000;
	vector<CensusEntry> storage2010;

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
	censusDataReader();
	drawPoint(star->root);
}

void HW04dwyermwApp::censusDataReader()
{
	// Read in Census 2000 data
	ifstream in("Census_2000.csv");

	int blocks2000[9];
	int blocks2010[9];

	char separator;
	int d;
	int pop = 0; // Population
	double xPop = 0; // X coordinate of population
	double yPop = 0; // Y coordinate of population
	int count = 0;

	while(in.good())
	{
		in >> d;
		in >> separator;
		in >> d;
		in >> separator;
		in >> d;
		in >> separator;

		CensusEntry* e = new CensusEntry();
		storage2000.push_back(*e);

		in >> d;
		storage2000[count].blockID = d;
		in >> separator;
		in >> pop;
		storage2000[count].population = pop;
		in >> separator;
		in >> xPop;
		storage2000[count].x = xPop;
		in >> separator;
		in >> yPop;
		storage2000[count].y = yPop;

		blocks2000[d] += pop;

		count++;
	}
	in.close();

	ifstream in2("Census_2010.csv");
	count = 0;

	while(in2.good())
	{
		in2 >> d;
		in2 >> separator;
		in2 >> d;
		in2 >> separator;
		in2 >> d;
		in2 >> separator;
		

		CensusEntry* e = new CensusEntry();
		storage2010.push_back(*e);

		in2 >> d;
		storage2010[count].blockID = d;
		in2 >> separator;
		in2 >> pop;
		storage2010[count].population = pop;
		in2 >> separator;
		in2 >> xPop;
		storage2010[count].x = xPop;
		in2 >> separator;
		in2 >> yPop;
		storage2010[count].y = yPop;

		if(storage2010[count].blockID != 0)
			blocks2010[d] += pop;

		count++;
	}
	in2.close();

	// Draw all census points from 2000 on map
	for(int j = 0; j < storage2000.size(); j++)
	{
		CensusEntry* ce = &storage2000[j];
		Entry* e = star->getNearest(ce->x, ce->y);
		int difference = blocks2010[ce->blockID] - blocks2000[ce->blockID];
		Color* c = new Color(0, 0, 0);
		c->g = 127;
		if(difference >= 0)
			c->g += (127 * (difference / 100000)) / 4;
		else
			c->g += (127 * (difference/ -100000)) / 4;

		drawCensusPoint(e->x, e->y, *c);
	}
	
	// Draw all census points from 2010 on map
	for(int k = 0; k < storage2010.size(); k++)
	{
		CensusEntry* ce = &storage2010[k];
		Entry* e = star->getNearest(ce->x, ce->y);
		int difference = blocks2010[ce->blockID] - blocks2000[ce->blockID];
		Color* c = new Color(0, 0, 0);
		c->g = 127;
		if(difference >= 0)
			c->g += (127 * (difference / 100000)) / 4;
		else
			c->g += (127 * (difference/ -100000)) / 4;
		drawCensusPoint(e->x, e->y, *c);
	}
	


}

void HW04dwyermwApp::findCensusDifference()
{
	int pop2000[9];
	int pop2010[9];

	// Initialize each array to 0
	for(int g = 0; g < 9; g++)
	{
		pop2000[g] = 0;
		pop2010[g] = 0;
	}

	// Sort all population values from the 2000 census based on BlockID
	for(int p = 0; p < storage2000.size(); p++)
	{
		switch(storage2000[p].blockID)
		{
			case 1 : pop2000[1] += storage2000[1].population;
				break;
			case 2 : pop2000[2] += storage2000[2].population;
				break;
			case 3 : pop2000[3] += storage2000[3].population;
				break;
			case 4 : pop2000[4] += storage2000[4].population;
				break;
			case 5 : pop2000[5] += storage2000[5].population;
				break;
			case 6 : pop2000[6] += storage2000[6].population;
				break;
			case 7 : pop2000[7] += storage2000[7].population;
				break;
			case 8 : pop2000[8] += storage2000[8].population;
				break;
			case 9 : pop2000[9] += storage2000[9].population;
				break;
		}
	}

	// Sort all population values from the 2010 census based on BlockID
	for(int p = 0; p < storage2010.size(); p++)
	{
		switch(storage2010[p].blockID)
		{
			case 1 : pop2010[1] += storage2010[1].population;
				break;
			case 2 : pop2010[2] += storage2010[2].population;
				break;
			case 3 : pop2010[3] += storage2010[3].population;
				break;
			case 4 : pop2010[4] += storage2010[4].population;
				break;
			case 5 : pop2010[5] += storage2010[5].population;
				break;
			case 6 : pop2010[6] += storage2010[6].population;
				break;
			case 7 : pop2010[7] += storage2010[7].population;
				break;
			case 8 : pop2010[8] += storage2010[8].population;
				break;
			case 9 : pop2010[9] += storage2010[9].population;
				break;
		}
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

	int index = 4 * (yPos * surfaceSize + xPos);

	pixels[index] = c.r;
	pixels[index + 1] = c.g;
	pixels[index + 2] = c.b;

	drawPoint(r->right);
	
	draw();
}

void HW04dwyermwApp::drawCensusPoint(double x, double y, Color c)
{
	//Color8u c = Color8u(255, 0, 0);

	int xConverted = floor(x * appWidth) + 10;
	int yConverted = floor((1 - y) * appHeight * 0.8) + 35;

	int index = 4 * (yConverted * surfaceSize + xConverted);

	pixels[index] = c.r;
	pixels[index + 1] = c.g;
	pixels[index + 2] = c.b;
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
