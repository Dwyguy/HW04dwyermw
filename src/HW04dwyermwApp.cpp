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
	dwyermwStarbucks* star;
};

void HW04dwyermwApp::setup()
{
	star = new dwyermwStarbucks();
	
	cout << "x";
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
