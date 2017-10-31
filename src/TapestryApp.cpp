#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "World.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class TapestryApp : public App {
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;

	World * world;
};

void TapestryApp::setup()
{
}

void TapestryApp::mouseDown(MouseEvent event)
{
}

void TapestryApp::update()
{
}

void TapestryApp::draw()
{
	gl::clear(Color(0.1f, 0.25f, 0.25f));
}

CINDER_APP(TapestryApp, RendererGl)