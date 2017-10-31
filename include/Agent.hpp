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

	ci::vec3 Advance(const SpatialHashTable<std::pair<size_t, size_t>> & trails);
	void Draw();
private:
	ci::vec3 m_position;
	Trail m_trail;
	/// The default advancement algo, which randomly samples one of the six cardinal directions.
	static std::function< ci::vec3(ci::vec3)> defaultAdvanceFn;
};