#pragma once

#include <vector>
#include "cinder/GeomIo.h"
#include "cinder/PolyLine.h"

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
    ci::PolyLine3 m_path;
};
