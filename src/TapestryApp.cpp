#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/Arcball.h"

#include "World.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class TapestryApp : public App {
public:
	TapestryApp();
	void setup() override;
	void mouseDown(MouseEvent event) override;
    void mouseDrag(MouseEvent event) override;

	void update() override;
	void draw() override;
    void resize() override;


	World m_world;
    CameraPersp m_camera;
    Arcball m_arcball;
    Sphere m_sphere;
};

TapestryApp::TapestryApp() : App(), m_world(500) {
}

void TapestryApp::setup()
{
    m_camera.setPerspective( 45.0f, getWindowAspectRatio(), 0.1f, 1000.0f );
    m_camera.lookAt( vec3( 0, 0, 3 ), vec3( 0 ) );
    m_sphere = Sphere( vec3( 0 ), 10.f );
    m_arcball = Arcball( &m_camera, m_sphere );

    gl::enableDepthRead();
    gl::enableDepthWrite();
    
}

void TapestryApp::resize() {
    m_camera.setAspectRatio( getWindowAspectRatio() );
}

void TapestryApp::mouseDown(MouseEvent event)
{
    m_arcball.mouseDown(event);
}

void TapestryApp::mouseDrag(cinder::app::MouseEvent event) {
    m_arcball.mouseDrag(event);
}

void TapestryApp::update()
{
	m_world.Update();
}

void TapestryApp::draw()
{
    gl::clear(Color(0.1f, 0.25f, 0.25f));
//    gl::clear(Color(0.f, 0.f, 0.f));

    gl::setMatrices( m_camera );
//    gl::rotate( m_arcball.getQuat() );
    gl::viewport( getWindowWidth() / 2, 0.0f, getWindowWidth() / 2, getWindowHeight() );
    m_world.Draw();
}

void prepareSettings( TapestryApp::Settings *settings )
{
    settings->setHighDensityDisplayEnabled();
}

CINDER_APP(TapestryApp, RendererGl, prepareSettings)
