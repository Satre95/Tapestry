#pragma once

#include <vector>
#include "cinder/GeomIo.h"
#include "cinder/PolyLine.h"
#include "cinder/gl/gl.h"

class Trail
{
public:
	Trail() {};
	~Trail() {}

	void AddPoint(const ci::vec3 & point);
	ci::vec3 GetPoint(size_t i) const;
	size_t Size() const { return m_path.size(); }
	void Draw(ci::Color color);
private:
	/// The line to draw
	cinder::PolyLineT < glm::vec3> m_path;
	//ci::PolyLine3 m_path;
};