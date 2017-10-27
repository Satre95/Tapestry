#pragma once

#include <unordered_map>
#include <list>
#include <sstream>
#include <cinder/GeomIo.h>

template <class T>
class SpatialHashTable
{
public:
	SpatialHashTable();
	SpatialHashTable(int m_binSize, int m_numBins);

	void Insert(glm::vec3 position, T & value);
	void Remove(glm::vec3 position);
	void Clear();

	void TestHash();
private:
	typedef long HashKey;
	HashKey HashPosition(glm::vec3 position);

	const int m_binSize;
	const int m_numBins;
	std::unordered_map<long, std::list<T>> bins;
	const std::array<float, 3> PRIMES{ 73856093.f, 19349663.f, 83492791.f };
};

template<class T>
SpatialHashTable<T>::SpatialHashTable() : m_binSize(5), m_numBins(500) {}

template<class T>
SpatialHashTable<T>::SpatialHashTable(int binSize, int numBins) :
	m_binSize(binSize), m_numBins(numBins) {}

template<class T>
void SpatialHashTable<T>::Insert(glm::vec3 position, T & value) {
	//Get the hash key for the given position
	HashKey key = HashPosition(position);

	//if the bin that this position hashes to has not been used before, need to create it first.
	if (bins.find(key) == bins.end())
		bins.insert(std::make_pair(key, std::list<T>()));

	//Insert into the list at the given key
	std::list<T> & list = bins.at(key);
	list.push_back(value);
}

template <class T>
void SpatialHashTable<T>::Remove(glm::vec3 position) {
	//Get the hash key for the given position
	HashKey key = HashPosition(position);

	//If the given position does not map to a slot in the map, return
	if (bins.find(key) == bins.end()) {
		std::stringstream ss;
		ss << "ERROR: Trying to remove item for position that is not stored in hash table"
			<< "Offending Position: " << position << std::endl;
		CI_LOG_E(ss.str());
		return;
	}

	std::list<T> & items = bins.at(key);
	items.Remove(position);
}

template<class T>
long SpatialHashTable<T>::HashPosition(glm::vec3 position) {
	HashKey part1 = std::floor(position.x / m_binSize) * PRIMES.at(0);
	HashKey part2 = std::floor(position.y / m_binSize) * PRIMES.at(1);
	HashKey part3 = std::floor(position.z / m_binSize) * PRIMES.at(2);

	return (part1 ^ part2 ^ part3) % m_numBins;
}

template<class T>
void SpatialHashTable<T>::TestHash() {
	for (size_t i = 0; i < 12; i++)
	{
		glm::vec3 randPos(ofRandom(100), ofRandom(100), ofRandom(100));
		ofLogNotice() << "Position: " << randpos << " hashed to key: " << HashPosition;
	}
}

template <class T>
void SpatialHashTable<T>::Clear() {
	bins.clear();
}