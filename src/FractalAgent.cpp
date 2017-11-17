#include "FractalAgent.hpp"
#include "cinder/Log.h"
#include "cinder/gl/gl.h"
using namespace std;

float FractalAgent::stepSize = 5.f;

FractalAgent::FractalAgent(string axiom, ci::Color colorIn) :
	m_axiom(axiom), m_color(colorIn), m_heading(1.f, 0, 0) {
	m_production = m_axiom;
}

FractalAgent::~FractalAgent() {
}

void FractalAgent::Iterate() {
	stringstream next;

	for (size_t i = 0; i < m_production.size(); i++) {
		auto expansion = m_ruleSet.find(m_production.at(i));
		if (expansion == m_ruleSet.end())
			next << m_production.at(i);
		else
			next << expansion->second;
	}

	m_production = next.str();
}

void FractalAgent::Advance() {
	if (m_nextSymbolIndex >= m_production.size()) return;

	const char & symbol = m_production.at(m_nextSymbolIndex++);
	auto actionItr = m_actions.find(symbol);
	if (actionItr == m_actions.end()) return; // No advancement for this symbol
	auto newPosAndHeading = actionItr->second(m_position, m_heading);
	m_trail.AddPoint(m_position);
	m_position = newPosAndHeading.first;
	m_heading = newPosAndHeading.second;
}

void FractalAgent::AdvanceAll() {
	while (m_nextSymbolIndex < m_production.size())
		Advance();
}

void FractalAgent::Draw() {
	ci::gl::drawSphere(m_position, 1.f);
	m_trail.Draw(m_color);
}

void FractalAgent::AddRule(char c, string rule) {
	m_ruleSet.insert(make_pair(c, rule));
}

void FractalAgent::AddAction(char c, const std::function < std::pair<glm::vec3, glm::vec3>(glm::vec3, glm::vec3)> & action) {
	m_actions.insert(make_pair(c, action));
}