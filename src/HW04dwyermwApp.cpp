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
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void drawPoint(Node* r);
	void clearSurface();
	void censusDataReader();
	void drawCensusPoint(double x, double y, Color c);
	void findCensusDifference();
	void zoom();

	int zoomFactor, xOffset, yOffset;

private:
	// A dwyermwStarbucks object, which allows for the data to be loaded,
	// the structure to be built, and the nearest locaiton to be found.
	dwyermwStarbucks* star;
	Surface* mySurface_;
	Surface* zoomSurface_;
	uint8_t* pixels;
	uint8_t* zoomPixels;
	
	vector<CensusEntry> storage2000;
	vector<CensusEntry> storage2010;

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
	zoomSurface_ = new Surface(surfaceSize, surfaceSize, true);
	zoomPixels = (*zoomSurface_).getData();
	zoomFactor = 1;
	xOffset = 0;
	yOffset = 0;
	
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

	int blocks2000[10];
	int blocks2010[10];

	for(int r = 0; r <= 9; r++)
	{
		blocks2000[r] = 0;
		blocks2010[r] = 0;
	}

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
			c->g += (127 * (difference / 1000000)) / 4;
		else
			c->g += (127 * (difference/ -1000000)) / 4;

		drawCensusPoint(ce->x, ce->y, *c);
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
		{
			c->g += (127 * (difference / 1000000)) / 4;
			c->r -= (127 * (difference / 1000000)) / 4;
		}
		else
		{
			c->g -= (127 * (difference/ -1000000)) / 4;
			c->r += (127 * (difference / 1000000)) / 4;
		}
		drawCensusPoint(ce->x, ce->y, *c);
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
	int yConverted = floor((1 - y) * appHeight * 0.8) + 50;

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

void HW04dwyermwApp::zoom()
{
	for(int y = 0; y < surfaceSize; y++)
	{
		for(int x = 0; x < surfaceSize; x++)
		{
			int index = 4 * (y * surfaceSize + x);
			int zoomIndex = 4* (((surfaceSize * (y/zoomFactor) + yOffset) + ((x/zoomFactor) + xOffset)));

			zoomPixels[index] = pixels[zoomIndex];
			zoomPixels[index + 1] = pixels[zoomIndex + 1];
			zoomPixels[index + 2] = pixels[zoomIndex + 2];
		}
	}
}

void HW04dwyermwApp::mouseDown( MouseEvent event )
{
	Color8u c = Color8u(255, 255, 255);

	int xPos = event.getX();
	int yPos = event.getY();

	// Convert to the 0 to 1 scale
	double xConverted = (((double)xPos) - 10) / appWidth;
	double yConverted = 1 - ((((double)yPos) - 50) / (appHeight * 0.8));

	/*
	int index = 4 * (yPos * surfaceSize + xPos);
	pixels[index] = c.r;
	pixels[index + 1] = c.g;
	pixels[index + 2] = c.b;
	*/
	//gl::drawSolidCircle(Vec2f(xPos, yPos), 5);

	Entry* nearest = star->getNearest(xConverted, yConverted);
	// Go from converted scale to pixels
	xPos = floor(appWidth * nearest->x) + 10;
	yPos = (floor(appHeight * (1 - nearest->y) * 0.8) + 50);

	// Nearest Starbucks is a white pixel.  Sorry I couldn't get it bigger
	int index = 4 * (yPos * surfaceSize + xPos);
	pixels[index] = c.r;
	pixels[index + 1] = c.g;
	pixels[index + 2] = c.b; 
}

void HW04dwyermwApp::keyDown( KeyEvent event)
{
	if(event.getCode() == KeyEvent::KEY_KP_PLUS)
		zoomFactor *= 2;
	if(event.getCode() == KeyEvent::KEY_KP_MINUS)
	{
		if(zoomFactor != 1)
		{
			zoomFactor /= 2;
			if(xOffset > surfaceSize - (surfaceSize/zoomFactor))
				xOffset = surfaceSize - (surfaceSize/zoomFactor);
			if(yOffset > surfaceSize - (surfaceSize/zoomFactor))
				yOffset = surfaceSize - (surfaceSize/zoomFactor);
		}
	}

	if(event.getCode() == KeyEvent::KEY_UP)
		if(yOffset > 0)
			yOffset -= 20;

	if(event.getCode() == KeyEvent::KEY_DOWN)
		if(yOffset < (surfaceSize - (surfaceSize/zoomFactor)))
			yOffset += 20;

	if(event.getCode() == KeyEvent::KEY_LEFT)
		if(xOffset > 0)
			xOffset -= 20;

	if(event.getCode() == KeyEvent::KEY_RIGHT)
		if(xOffset < (surfaceSize - (surfaceSize/zoomFactor)))
			xOffset += 20;
}


void HW04dwyermwApp::update()
{
	zoom();

}

void HW04dwyermwApp::draw()
{
	
	//gl::draw(*myTexture_);
	//gl::Texture picture( loadImage( loadResource( RES_IMG) ) );
	//gl::draw(picture);
	//gl::drawSolidRect(Rectf(100, 100, 120, 120), 0.2F);
	gl::draw(*zoomSurface_);
	//gl::draw(*mySurface_);
	//gl::clear(Color(0, 0, 0));
}

CINDER_APP_BASIC( HW04dwyermwApp, RendererGl )
