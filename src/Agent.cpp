#include "Agent.hpp"
#include "cinder/Rand.h"
using namespace ci;

std::function< ci::vec3(ci::vec3)> Agent::defaultAdvanceFn = [](ci::vec3 oldPos) {
	return oldPos;
};

Agent::Agent(ci::vec3 pos, std::function<ci::vec3(ci::vec3&)>  advanceFn) {
	m_position = pos;
}

Agent::~Agent() {
}

vec3 Agent::Advance(const SpatialHashTable<std::pair<size_t, size_t>> & trails) {
	m_trail.AddPoint(m_position);

	return m_position;
}

void Agent::Draw() {
}