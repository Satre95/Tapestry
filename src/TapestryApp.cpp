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
    CameraUi m_cameraUI;
};

TapestryApp::TapestryApp() : App(), m_world(500) {
}

void TapestryApp::setup()
{
    m_camera.setPerspective( 60.0f, getWindowAspectRatio(), 0.1f, 1000.0f );
    m_camera.lookAt( vec3( 0, 0, 3 ), vec3( 0 ) );
    m_cameraUI = CameraUi(&m_camera);

    gl::enableDepthRead();
    gl::enableDepthWrite();
    
}

void TapestryApp::resize() {
    m_camera.setAspectRatio( getWindowAspectRatio() );
}

void TapestryApp::mouseDown(MouseEvent event)
{
    m_cameraUI.mouseDown(event);
}

void TapestryApp::mouseDrag(cinder::app::MouseEvent event) {
    Rectf r    = Rectf( getWindowWidth() / 2, 0, getWindowWidth(), getWindowHeight() );
    if ( r.contains( event.getPos() )) {
        m_cameraUI.mouseDrag( event );
    }
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
    m_world.Draw();
}

void prepareSettings( TapestryApp::Settings *settings )
{
    settings->setHighDensityDisplayEnabled();
}

CINDER_APP(TapestryApp, RendererGl, prepareSettings)
