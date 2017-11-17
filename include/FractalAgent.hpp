#pragma once

#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include "cinder/GeomIo.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Trail.hpp"

class FractalAgent
{
public:
	FractalAgent(std::string axiom, ci::Color col = ci::Color::gray);
	~FractalAgent();

	/// Run 1 recursion step of the sequence. Restarts the draw sequence.
	void Iterate();
	/// Parse the next character in the sequence and perform it's action. Stores the history of points.
	void Advance();
	/// Runs through the entire sequence and stores the results.
	void AdvanceAll();
	/// Draws the Agent turtle and the generated path.
	void Draw();
	void AddRule(char c, std::string rule);
	void AddAction(char c, const std::function < std::pair<glm::vec3, glm::vec3>(glm::vec3, glm::vec3)> &);

private:

	glm::vec3 m_position;
	glm::vec3 m_heading;
	/// Location of the next symbol that needs to be processed.
	size_t m_nextSymbolIndex = 0;
	/// The history of this point
	Trail m_trail;
	/// The color to draw with.
	ci::Color m_color;

	/// Starting state.
	const std::string m_axiom;
	/// The string representing the L-System state at the current time point.
	std::string m_production;
	/// The expansion rule set. If a char is not in here, then it is constant.
	std::unordered_map<char, std::string> m_ruleSet;
	/// Set of functors that take in current pos and heading and return new pos and heading for a given rule.
	std::unordered_map <char, std::function < std::pair<glm::vec3, glm::vec3>(glm::vec3, glm::vec3)>> m_actions;
};