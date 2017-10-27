#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TapestryApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void TapestryApp::setup()
{
}

void TapestryApp::mouseDown( MouseEvent event )
{
}

void TapestryApp::update()
{
}

void TapestryApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( TapestryApp, RendererGl )
