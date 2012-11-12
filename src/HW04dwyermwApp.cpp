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

private:
	// A dwyermwStarbucks object, which allows for the data to be loaded,
	// the structure to be built, and the nearest locaiton to be found.
	dwyermwStarbucks* star;
	Surface* mySurface_;
	uint8_t* pixels;

	//gl::Texture* picture_;

	static const int appHeight = 600;
	static const int appWidth = 800;
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

	drawPoint(star->root);
	
	// Create loop in here that reads in all data from the tree, and puts it into a list of locations to
	// draw on the picture.  Preferably a 2-d array.
}

void HW04dwyermwApp::drawPoint(Node* r)
{
	Color8u c = Color8u(0, 0, 255);

	if(r == NULL)
		return;

	drawPoint(r->left);

	int xPos = r->key->x * appWidth;
	int yPos = r->key->y * appHeight;

	pixels[4 * (yPos * surfaceSize + xPos)] = c.r;
	pixels[4 * (yPos * surfaceSize + xPos)] = c.g;
	pixels[4 * (yPos * surfaceSize + xPos)] = c.b;

	drawPoint(r->right);

	draw();
}

void HW04dwyermwApp::mouseDown( MouseEvent event )
{
}

void HW04dwyermwApp::update()
{
	

}

void HW04dwyermwApp::draw()
{
	
	//gl::draw(*myTexture_);
	gl::Texture picture( loadImage( loadResource( RES_IMG) ) );
	gl::draw(picture);
	gl::drawSolidRect(Rectf(100, 100, 120, 120), 0.2F);
	gl::draw(*mySurface_);
	
}

CINDER_APP_BASIC( HW04dwyermwApp, RendererGl )
