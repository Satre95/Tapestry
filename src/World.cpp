#include <tuple>
#include <vector>

#include "World.hpp"
#include "cinder/Rand.h"
#include "cinder/Log.h"

using namespace ci;

World::World(float dims, size_t numAgents) : m_worldDimensions(dims),
m_history(10.f, int(dims)/ 10){
	m_agents.reserve(numAgents);
	Rand rand;
	for (size_t i = 0; i < numAgents; i++) {
		vec3 pos(
			rand.nextFloat(-dims / 2.f, dims / 2.f),
			rand.nextFloat(-dims / 2.f, dims / 2.f),
			rand.nextFloat(-dims / 2.f, dims / 2.f)
		);
		m_agents.emplace_back(pos);
	}
    
    //Populate history with initial positions
    for(Agent & anAgent: m_agents) {
        auto id = anAgent.Id();
        m_history.Insert(anAgent.GetPosition(), id);
    }
}

World::~World() {
	m_history.Clear(); m_agents.clear();
}

void World::Update() {
	std::vector<std::pair<size_t, vec3>> newPositions;
	newPositions.reserve(NumAgents());

	for (Agent & anAgent : m_agents) {
		newPositions.push_back(
			std::make_pair(
				anAgent.Id(),
				anAgent.Advance(m_history)
			)
		);
	}

	//Now add the new positions to the world history
	for (auto & aPoint : newPositions) {
		m_history.Insert(
			aPoint.second,
			aPoint.first
		);
	}
}

void World::Draw() {
	for (Agent & anAgent : m_agents) anAgent.Draw();
}
