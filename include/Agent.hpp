#pragma once
#include <cinder/GeomIo.h>

class Agent
{
public:
	Agent(ci::vec3 pos);
	~Agent();

private:
	ci::vec3 m_position;
};