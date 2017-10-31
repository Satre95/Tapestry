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

size_t Agent::agentsCount = 0;

Agent::Agent(ci::vec3 pos, std::function<ci::vec3(ci::vec3&)>  advanceFn) : m_id(agentsCount++) {
	m_position = pos; m_advanceFn = advanceFn;
}

Agent::~Agent() {
}

vec3 Agent::Advance(const SpatialHashTable<size_t> & worldHistory) {
	vec3 newPos = m_advanceFn(m_position);
	///Only accept the new position if it is not near a point visited already by another (or same) agent.
	if (worldHistory.Probe(newPos) == 0)
		m_position = newPos;

	return m_position;
}

void Agent::Draw() {
}