//
//  Trail.cpp
//  Tapestry
//
//  Created by Siddharth Atre on 10/31/17.
//

#include "Trail.hpp"

using namespace ci;

void Trail::AddPoint(const ci::vec3 & point) {
	m_path.push_back(point);
}

ci::vec3 Trail::GetPoint(size_t i) const {
	if (i >= m_path.size()) return ci::vec3(0);
	return m_path.getPoints().at(i);
}

void Trail::Draw(Color color) {
	ci::gl::color(color);
	ci::gl::draw(m_path.getPoints());
	//ci::gl::draw(m_path);
}