#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include "Entry.h"
#include "RuntimeException.h"
#include "CountyData.h"
//#include "LinearProbing.h"
//#include "DoubleHashing.h"

template <typename K, typename V>
class Chaining {
public:						// public types
	typedef Entry<const K, V> Entry;			// a (key,value) pair
	class Iterator;					// a iterator/position
public:						// public functions
	Chaining(int capacity );			// constructor
	int size() const;					// number of entries
	bool empty() const;					// is the map empty?
	Iterator find(const K& k);				// find entry with key k
	Iterator put(const K& k, const V& v);		// insert/replace (k,v)
	bool hasEntry(const K& k)
	{
		Iterator p = finder(k);
		if (endOfBkt(p)) {
			return false;
		}
		else {
			return true;
		}
	}
	int hashCode(int k)
	{
		return k % B.size();
	};
	void erase(const K& k);				// remove entry with key k
	void erase(const Iterator& p);			// erase entry at p
	Iterator begin();					// iterator to first entry
	Iterator end();					// iterator to end entry
	int collisionCount()
	{
		return totalCollisions;
	}
	/*void checkLoadFactor()
	{
		float entries = (float)n, totalBckts = (float)B.size();
		float loadTime = entries / totalBckts;
		if (loadTime > loadFactor) {
			BktArray NewB(B.size() * 2));
			Iterator p = B.begin();
			for (int i = 0; i < B.size(); i++)
			{
				int countyCode = (*p).key();
				int countyPopulation = (*p).value().getCountyPopulation();
				std::string countyName = (*p).value().getCountyName();
			}
		}
	}
	*/
	int getTotalProbes() { return totalProbes; }
	int getTableSize() { return B.size(); }
	int getWorstProbe() { return worstProbe; }
	int getCurrentProbe() { return currentProbe; }
protected:						// protected types
	typedef std::list<Entry> Bucket;			// a bucket of entries
	typedef std::vector<Bucket> BktArray;		// a bucket array
	Iterator finder(const K& k);			    // find utility
	Iterator inserter(const Iterator& p, const Entry& e);   // insert utility
	void eraser(const Iterator& p);			    // remove utility
	typedef typename BktArray::iterator BItor;		    // bucket iterator
	typedef typename Bucket::iterator EItor;		    // entry iterator
	static void nextEntry(Iterator& p)			    // bucket's next entry
	{
		++p.ent;
	}
	static bool endOfBkt(const Iterator& p)		    // end of bucket?
	{
		return p.ent == p.bkt->end();
	}
private:
	int n, totalCollisions, totalProbes, worstProbe, currentProbe;						// number of entries
	BktArray B;						// bucket array
public:						// public types
	class Iterator {	                      		// an iterator (& position)
	private:
		EItor ent;					// which entry
		BItor bkt;					// which bucket
		const BktArray* ba;				// which bucket array
	public:
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) { }
		Entry& operator*() const;				// get entry
		bool operator==(const Iterator& p) const;		// are iterators equal?
		Iterator& operator++();				// advance to next entry
		int bucketCount()
		{
			int count = 0;
			while (bkt != ba->end() && bkt->empty())		// find nonempty bucket
				count++;
			return count;
		}
		friend class Chaining;				// give Chaining access
	};
};

template <typename K, typename V>		// constructor
Chaining<K, V>::Chaining(int capacity) : n(0), B(capacity) { }

template <typename K, typename V>		// number of entries
int Chaining<K, V>::size() const { return n; }

template <typename K, typename V>		// is the map empty?
bool Chaining<K, V>::empty() const { return size() == 0; }

template <typename K, typename V>		// iterator to end
typename Chaining<K, V>::Iterator Chaining<K, V>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V>		// iterator to front
typename Chaining<K, V>::Iterator Chaining<K, V>::begin() {
	if (empty()) return end();				// emtpty - return end
	BItor bkt = B.begin();				// else search for an entry
	while (bkt->empty()) ++bkt;				// find nonempty bucket
	return Iterator(B, bkt, bkt->begin());		// return first of bucket
}

template <typename K, typename V>		// are iterators equal?
bool Chaining<K, V>::Iterator::operator==(const Iterator& p) const {
	if (ba != p.ba || bkt != p.bkt) return false;	// ba or bkt differ?
	else if (bkt == ba->end()) return true;		// both at the end?
	else return (ent == p.ent);				// else use entry to decide
}

template <typename K, typename V>		// advance to next entry
typename Chaining<K, V>::Iterator& Chaining<K, V>::Iterator::operator++() {
	++ent;						// next entry in bucket
	if (endOfBkt(*this)) {				// at end of bucket?
		++bkt;						// go to next bucket
		while (bkt != ba->end() && bkt->empty())		// find nonempty bucket
			++bkt;
		if (bkt == ba->end()) return *this;		// end of bucket array?
		ent = bkt->begin();				// first nonempty entry
	}
	return *this;					// return self
}

template <typename K, typename V>		// get entry
typename Chaining<K, V>::Entry& Chaining<K, V>::Iterator::operator*() const
{
	return *ent;
}

template <typename K, typename V>		// insert utility
typename Chaining<K, V>::Iterator Chaining<K, V>::inserter(const Iterator& p, const Entry& e) {
	EItor ins = p.bkt->insert(p.ent, e);		// insert before p
	n++;						// one more entry
	return Iterator(B, p.bkt, ins);			// return this position
}

template <typename K, typename V>		// insert/replace (v,k)
typename Chaining<K, V>::Iterator Chaining<K, V>::put(const K& k, const V& v) {
	Iterator p = finder(k);				// search for k
	if (endOfBkt(p)) {					// k not found?
		//checkLoadFactor();
		return inserter(p, Entry(k, v));			// insert at end of bucket
	}
	else {						// found it?
		totalCollisions++;
		//checkLoadFactor();
		p.ent->setValue(v);				// replace value with v
		return p;						// return this position
	}
}


template <typename K, typename V>		// find utility
typename Chaining<K, V>::Iterator Chaining<K, V>::finder(const K& k) {
	int i = hashCode(k), currentProbes = 1;				// get hash index i
	BItor bkt = B.begin() + i;				// the ith bucket
	Iterator p(B, bkt, bkt->begin());			// start of ith bucket
	totalProbes++;
	while (!endOfBkt(p) && (*p).key() != k)		// search for k
	{
		totalProbes++;
		currentProbes++;
		nextEntry(p);
	}
	if (currentProbes > worstProbe)
		worstProbe = currentProbes;
	currentProbe = currentProbes;
	return p;						// return final position
}

template <typename K, typename V>		// find key
typename Chaining<K, V>::Iterator Chaining<K, V>::find(const K& k) {
	Iterator p = finder(k);				// look for k
	if (endOfBkt(p))					// didn't find it?
		return end();					// return end iterator
	else
		return p;						// return its position
}

template <typename K, typename V>		// remove utility
void Chaining<K, V>::eraser(const Iterator& p) {
	p.bkt->erase(p.ent);				// remove entry from bucket
	n--;						// one fewer entry
}

template <typename K, typename V>		// remove entry at p
void Chaining<K, V>::erase(const Iterator& p)
{
	eraser(p);
}

template <typename K, typename V>		// remove entry with key k
void Chaining<K, V>::erase(const K& k) {
	Iterator p = finder(k);				// find k
	if (endOfBkt(p))					// not found?
		throw NonexistentElement("Erase of nonexistent");	// ...error
	eraser(p);						// remove it
}

