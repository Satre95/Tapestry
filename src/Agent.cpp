#include "Agent.hpp"
#include "cinder/Rand.h"
using namespace ci;

std::function< ci::vec3(ci::vec3)> Agent::defaultAdvanceFn = [](ci::vec3 oldPos) {
	static vec3 cardinals[] = {
		vec3(1.f, 0.f, 0.f), vec3(-1.f, 0.f, 0.f),		//Right, Left
		vec3(0.f, 1.f, 0.f), vec3(0.f, -1.f, 0.f),		//Up, Down
		vec3(0.f, 0.f, 1.f), vec3(0.f, 0.f, -1.f)		//Front, Back
	};
	Rand rand;
	vec3 sampledCardinal = cardinals[rand.nextUint(6)];

	return oldPos + sampledCardinal;
};

Agent::Agent(ci::vec3 pos, std::function<ci::vec3(ci::vec3&)>  advanceFn) {
	m_position = pos; m_advanceFn = advanceFn;
}

Agent::~Agent() {
}

vec3 Agent::Advance(const SpatialHashTable<std::pair<size_t, size_t>> & trails) {
	m_trail.AddPoint(m_position);

	return m_position;
}

void Agent::Draw() {
}