#pragma once

#include <functional>
#include "cinder/GeomIo.h"
#include "Trail.hpp"
#include "SpatialHashTable.hpp"

class Agent
{
public:
	Agent(ci::vec3 pos, std::function<ci::vec3(ci::vec3&)>  advanceFn = defaultAdvanceFn);
	~Agent();

	ci::vec3 Advance(const SpatialHashTable<size_t> & history);
	void Draw();
	size_t Id() const { return m_id; }
	size_t TrailIndex() const { return m_trail.Size() - 1; }

private:
	/// This agent's current position in the World.
	ci::vec3 m_position;
	/// The history of points this agent has visited.
	Trail m_trail;
	/// The advancement fn used by this agent.
	std::function<ci::vec3(ci::vec3)> m_advanceFn;
	const size_t m_id;
	/// The default advancement algo, which randomly samples one of the six cardinal directions.
	static std::function< ci::vec3(ci::vec3)> defaultAdvanceFn;
	/// Counter for number of agents created
	static size_t agentsCount;
};