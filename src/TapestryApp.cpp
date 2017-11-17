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
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseWheel(MouseEvent event) override;

	void update() override;
	void draw() override;
	void resize() override;

	void SetupKochCurve();

	//std::shared_ptr<World> m_world;
	std::vector<FractalAgent> m_fAgents;

	size_t m_numIterations = 5;

	CameraPersp m_camera;
	CameraUi m_cameraUI;
};

void TapestryApp::setup()
{
	SetupKochCurve();
	// F is step forward
	// B is step backward.
	// Q -> QFX
	// R -> BRY
	// S -> UY
	// T -> Tz
	// U -> SZU
	// X is rotate +90 deg on X Axis.
	// x is rotate -90 deg on X Axis.
	// Y is rotate +90 deg on Y Axis.
	// ... and so on

	/*
	function<pair<glm::vec3, glm::vec3>(glm::vec3, glm::vec3) > action = [](glm::vec3 pos, glm::vec3 heading) { // Move Forward
		pos += (heading * FractalAgent::stepSize);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('F', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { // Move Backward
		pos -= (heading * FractalAgent::stepSize);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('B', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { //Rotate +X
		heading = glm::rotateX(heading, 45.f);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('X', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { //Rotate -X
		heading = glm::rotateX(heading, -45.f);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('x', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { //Rotate +Y
		heading = glm::rotateY(heading, 45.f);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('Y', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { //Rotate -X
		heading = glm::rotateY(heading, -45.f);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('y', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { //Rotate +Z
		heading = glm::rotateZ(heading, 45.f);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('Z', action);

	action = [](glm::vec3 pos, glm::vec3 heading) { //Rotate -Z
		heading = glm::rotateZ(heading, -45.f);
		return make_pair(pos, heading);
	};
	fAgent.AddAction('z', action);
	*/

	for (size_t i = 0; i < m_numIterations; i++)
		for (auto & anAgent : m_fAgents) {
			anAgent.Iterate();
			CI_LOG_I("Prodction: " + anAgent.GetProduction());
		}

	m_camera.setPerspective(45.0f, getWindowAspectRatio(), 0.1f, 10000.0f);
	m_camera.lookAt(vec3(0, 0, 60), vec3(0));
	m_cameraUI = CameraUi(&m_camera);
	gl::lineWidth(2.f);

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void TapestryApp::resize() {
	m_camera.setAspectRatio(getWindowAspectRatio());
}

void TapestryApp::mouseDown(MouseEvent event) {
	m_cameraUI.mouseDown(event);
}

void TapestryApp::mouseWheel(MouseEvent event) {
	m_cameraUI.mouseWheel(event);
}

void TapestryApp::mouseDrag(cinder::app::MouseEvent event) {
	m_cameraUI.mouseDrag(event);
}

void TapestryApp::update()
{
	for (auto & anAgent : m_fAgents)
		anAgent.Advance();
}

void TapestryApp::draw()
{
	gl::clear(Color(0.1f, 0.25f, 0.25f));

	gl::setMatrices(m_camera);
	for (auto & anAgent : m_fAgents)
		anAgent.Draw();
}

void TapestryApp::SetupKochCurve() {
	std::string axiom = "F";
	m_fAgents.emplace_back(axiom);
	FractalAgent & fAgent = m_fAgents.back();
	fAgent.SetHeading(glm::vec3(1.f, 0, 0));
	// Add expansion rules
	fAgent.AddRule('F', "F+F-F-F+F");

	// Add advancement fns.
	fAgent.AddAction('F', [](glm::vec3 pos, glm::vec3 heading) {
		pos += (heading * FractalAgent::stepSize);
		return make_pair(pos, heading);
	});
	fAgent.AddAction('+', [](glm::vec3 pos, glm::vec3 heading) {
		heading = glm::rotateZ(heading, glm::radians(90.f));
		return make_pair(pos, heading);
	});
	fAgent.AddAction('-', [](glm::vec3 pos, glm::vec3 heading) {
		heading = glm::rotateZ(heading, glm::radians(-90.f));
		return make_pair(pos, heading);
	});
	//fAgent.AddAction('[', [](glm::vec3 pos, glm::vec3 heading) {
	//	heading = glm::rotateY(heading, glm::radians(90.f));
	//	return make_pair(pos, heading);
	//});
	//fAgent.AddAction(']', [](glm::vec3 pos, glm::vec3 heading) {
	//	heading = glm::rotateY(heading, glm::radians(-90.f));
	//	return make_pair(pos, heading);
	//});
	//fAgent.AddAction('>', [](glm::vec3 pos, glm::vec3 heading) {
	//	heading = glm::rotateX(heading, glm::radians(90.f));
	//	return make_pair(pos, heading);
	//});
	//fAgent.AddAction('<', [](glm::vec3 pos, glm::vec3 heading) {
	//	heading = glm::rotateX(heading, glm::radians(-90.f));
	//	return make_pair(pos, heading);
	//});
}

void prepareSettings(TapestryApp::Settings *settings)
{
	//Bsettings->setHighDensityDisplayEnabled();
}

CINDER_APP(TapestryApp, RendererGl, prepareSettings)