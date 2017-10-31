#pragma once

#include <vector>
#include <cinder/GeomIo.h>

class Trail
{
public:
	Trail() {}
	~Trail() { m_points.clear(); }

	void AddPoint(const ci::vec3 & point);
	ci::vec3 GetPoint(size_t i) const;
	size_t Size() const { return m_points.size(); }

private:
	std::vector <ci::vec3> m_points;
};

inline void Trail::AddPoint(const ci::vec3 & point) {
	m_points.push_back(point);
}

inline ci::vec3 Trail::GetPoint(size_t i) const {
	if (i >= m_points.size()) return ci::vec3(0);
	return m_points.at(i);
}