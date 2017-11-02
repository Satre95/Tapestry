#pragma once

#include <functional>
#include "cinder/GeomIo.h"
#include "Trail.hpp"
#include "SpatialHashTable.hpp"
#include "cinder/gl/gl.h"
class Agent
{
public:
	Agent(ci::vec3 pos, std::function<ci::vec3(ci::vec3&)>  advanceFn = defaultAdvanceFn);

	ci::vec3 Advance(const SpatialHashTable<size_t> & history);
    void Draw() { m_trail.Draw(m_color); }
	size_t Id() const { return m_id; }
	size_t TrailIndex() const { return m_trail.Size() - 1; }
    ci::vec3 GetPosition() const { return m_position; }
    void SetColor(ci::Color color) { m_color = color; }
    
    static void SetStepSize(int size) { stepSize = size;}

private:
	/// This agent's current position in the World.
	ci::vec3 m_position;
	/// The history of points this agent has visited.
	Trail m_trail;
	/// The advancement fn used by this agent.
	std::function<ci::vec3(ci::vec3&)> m_advanceFn;
	const size_t m_id;
    /// The draw color of this agent and it's path
    ci::Color m_color;
    
	/// The default advancement algo, which randomly samples one of the six cardinal directions.
	static std::function< ci::vec3(ci::vec3 )> defaultAdvanceFn;
	/// Counter for number of agents created
	static size_t agentsCount;
    /// The length of each step
    static int stepSize;
    
    
};
