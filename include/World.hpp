#pragma once

#include <cinder/GeomIo.h>
#include "SpatialHashTable.hpp"
#include "Agent.hpp"

class World
{
public:
	World(ci::vec3 dimensions, size_t numAgents = 10);
	~World();

	size_t NumAgents() const { return m_agents.size(); }

private:
	SpatialHashTable<size_t> m_buckets;
	std::vector<Agent> m_agents;
	ci::vec3 m_worldDimensions;
};