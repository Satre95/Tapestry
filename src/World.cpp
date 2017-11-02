#include <tuple>
#include <vector>
#include "glm/ext.hpp"
#include "World.hpp"
#include "cinder/Rand.h"
#include "cinder/Log.h"

using namespace ci;
using namespace cinder;

World::World(float dims, float binSize, size_t numAgents ) : m_worldDimensions(dims), m_history(binSize, int(dims) / int(std::round(binSize))) {
	m_agents.reserve(numAgents);
	for (size_t i = 0; i < numAgents; i++) {
		vec3 pos(
                 randFloat(-dims / 2.f, dims / 2.f),
                 randFloat(-dims / 2.f, dims / 2.f),
                 randFloat(-dims / 2.f, dims / 2.f)
		);
        pos = glm::round(pos) + 0.5f; //Points are always in middle of cells
		m_agents.emplace_back(pos);
        m_agents.back().SetColor(Color(randFloat(), randFloat(), randFloat()));
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
