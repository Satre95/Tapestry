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

	void Update();
	void Draw();

private:
	/**
	 * Stores the points that have been added to the world so far.
	 * First number is agent index, second is the index of the point in that agent's trail.
	 */
	SpatialHashTable<size_t> m_history;
	std::vector<Agent> m_agents;
	ci::vec3 m_worldDimensions;
};