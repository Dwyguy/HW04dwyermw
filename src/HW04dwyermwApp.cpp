#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <fstream>
#include <iostream>
#include "Starbucks.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class HW04dwyermwApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04dwyermwApp::setup()
{
	ifstream in("Starbucks_2006.csv");
	vector <Entry> storage;
	string line;
	double d;
	int x = 0;
	
	while(in.good())
	{
		Entry* e = new Entry;
		storage.push_back(*e);
		getline(in, line, ',');
		storage[x].identifier = line;
		in >> d;
		storage[x].x = d;
		in >> d;
		storage[x].y = d;
		//console() << line;
	}

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
