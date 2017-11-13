#pragma once

#include <unordered_map>
#include <list>
#include <sstream>
#include "cinder/GeomIo.h"
#include "cinder/Log.h"

template <class T>
class SpatialHashTable
{
public:
	SpatialHashTable();
	SpatialHashTable(float m_binSize, int m_numBins);

	/// Copies the item with the given position into this container.
	void Insert(glm::vec3 position, T & value);
	///Removes the item with the given position from the table, if it exists.
	void Remove(glm::vec3 position);
	/// Resets and erases all data in this container.
	void Clear();
	/// Finds an element with the given position, if it exists.
	T * Find(glm::vec3 position) const;
	/// Returns the number of items in the same bin of the given position.
	size_t Probe(glm::vec3 position) const;

private:
	typedef long HashKey;
	HashKey HashPosition(glm::vec3 position) const;

	const float m_binSize;
	const int m_numBins;
	std::unordered_map<HashKey, std::list < std::pair<glm::vec3, T >>> bins;
	const std::array<long, 3> PRIMES{ 73856093, 19349663, 83492791 };
};

template<class T>
SpatialHashTable<T>::SpatialHashTable() : m_binSize(5), m_numBins(500) {}

template<class T>
SpatialHashTable<T>::SpatialHashTable(float binSize, int numBins) :
	m_binSize(binSize), m_numBins(numBins) {}

template<class T>
void SpatialHashTable<T>::Insert(glm::vec3 position, T & value) {
	//Get the hash key for the given position
	HashKey key = HashPosition(position);

	//if the bin that this position hashes to has not been used before, need to create it first.
	if (bins.find(key) == bins.end())
		bins.insert(std::make_pair(key, std::list < std::pair<glm::vec3, T>>()));

	//Insert into the list at the given key
	auto & list = bins.at(key);
	//Duplicate check
	for (auto & aPair : list)
        if (aPair.first == position) return;

	list.push_back(std::make_pair(position, value));
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

	auto & items = bins.at(key);
	items.remove_if([&position](std::pair<glm::vec3, T> & aPair) {
		return aPair.first == position;
	});
}

template<class T>
long SpatialHashTable<T>::HashPosition(glm::vec3 position) const {
	HashKey part1 = long(std::floor(position.x / m_binSize)) * PRIMES.at(0);
	HashKey part2 = long(std::floor(position.y / m_binSize)) * PRIMES.at(1);
	HashKey part3 = long(std::floor(position.z / m_binSize)) * PRIMES.at(2);

	return (part1 ^ part2 ^ part3) % m_numBins;
}

template <class T>
void SpatialHashTable<T>::Clear() {
	bins.clear();
}

template <class T>
T * SpatialHashTable<T>::Find(glm::vec3 position) const {
	//Get the hash key for the given position
	HashKey key = HashPosition(position);

	//if the bin that this position hashes to has not been created, then item doesn't exist.
	if (bins.find(key) == bins.end()) return nullptr;

	// Find list at the given key
	auto & list = bins.at(key);
	/// Find the item.
	for (auto & aPair : list) {
		if (aPair.first == position) {
			return &aPair.second;
		}
	}

	return nullptr;
}

template <class T>
size_t SpatialHashTable<T>::Probe(glm::vec3 position) const {
	//Get the hash key for the given position
	HashKey key = HashPosition(position);

	//if the bin that this position hashes to has not been created, then item doesn't exist.
	if (bins.find(key) == bins.end()) return 0;
	return bins.at(key).size();
}
