#include "World.hpp"
#include <cinder/Rand.h>
using namespace ci;

World::World(vec3 dims, size_t numAgents) : m_worldDimensions(dims)
{
	m_agents.reserve(numAgents);
	Rand rand;
	for (size_t i = 0; i < numAgents; i++) {
		vec3 pos(
			rand.nextFloat(-dims.x / 2.f, dims.x / 2.f),
			rand.nextFloat(-dims.y / 2.f, dims.y / 2.f),
			rand.nextFloat(-dims.z / 2.f, dims.z / 2.f)
		);
		m_agents.emplace_back(pos);
	}
}

World::~World()
{
	m_buckets.Clear(); m_agents.clear();
}