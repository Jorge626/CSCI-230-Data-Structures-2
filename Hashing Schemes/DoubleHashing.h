#pragma once
#include "Chaining.h"

template <typename K, typename V>
class DoubleHashing
{
public:						// public types
	typedef Entry<const K, V> Entry;			// a (key,value) pair
	class Iterator;					// a iterator/position
public:						// public functions
	DoubleHashing(int capacity) : n(0), B(capacity) { };			// constructor
	int size() const { return n; }					// number of entries
	bool empty() const { return size() == 0; }			// is the map empty?
	Iterator find(const K& k);				// find entry with key k
	Iterator put(const K& k, const V& v);		// insert/replace (k,v)
	void erase(const K& k);				// remove entry with key k
	Iterator begin();					// iterator to first entry
	Iterator end();					// iterator to end entry
	int getTotalProbes() { return totalProbes; }
	int getTableSize() { return B.size(); }
	int getWorstProbe() { return worstProbe; }
	int getCurrentProbe() { return currentProbe; }
	bool isPrime(int capacity)
	{
		int flag = 1;
		for (int i = 2; i <= sqrt(capacity); i++) {
			if (capacity % i == 0) {
				flag = 0;
				break;
			}
		}

		if (flag == 1) {
			return true;
		}
		else {
			return false;
		}
	}
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
	int hashCode(int k) { return k % B.size(); }
	int hashCodePrime(int k, int q) { return q - (k % q); }
private:
	int n, totalProbes, worstProbe, currentProbe;						// number of entries
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
		friend class DoubleHashing;				// give HashMap access
	};
};

template <typename K, typename V>		// find utility
typename DoubleHashing<K, V>::Iterator DoubleHashing<K, V>::finder(const K& k) {
	int i = hashCode(k), currentProbes = 1, j = 1, primeNumber;				// get hash index i
	bool foundPrime = false;
	for (int p = B.size() - 1; p > 0; p--)
	{
		if (isPrime(p) & foundPrime == false) {
			primeNumber = p;
			foundPrime = true;
		}
	}
	BItor bkt = B.begin() + i;				// the ith bucket
	Iterator p(B, bkt, bkt->begin());			// start of ith bucket
	totalProbes++;
	while (!endOfBkt(p) && (*p).key() != k)		// search for k
	{
		int funct = j * hashCodePrime(k, primeNumber);
		i = (i + funct) % B.size();
		bkt = B.begin() + i;				// the ith bucket
		if (bkt == B.end())
			bkt = B.begin();
		Iterator b(B, bkt, bkt->begin());
		p = b;
		totalProbes++;
		currentProbes++;
	}
	if (currentProbes > worstProbe)
		worstProbe = currentProbes;
	currentProbe = currentProbes;
	return p;					// return final position
}

template <typename K, typename V>		// find key
typename DoubleHashing<K, V>::Iterator DoubleHashing<K, V>::find(const K& k) {
	Iterator p = finder(k);				// look for k
	if (endOfBkt(p))					// didn't find it?
		return end();					// return end iterator
	else
		return p;						// return its position
}

template <typename K, typename V>		// insert utility
typename DoubleHashing<K, V>::Iterator DoubleHashing<K, V>::inserter(const Iterator& p, const Entry& e) {
	EItor ins = p.bkt->insert(p.ent, e);		// insert before p
	n++;						// one more entry
	return Iterator(B, p.bkt, ins);			// return this position
}

template <typename K, typename V>		// insert/replace (v,k)
typename DoubleHashing<K, V>::Iterator DoubleHashing<K, V>::put(const K& k, const V& v) {
	Iterator p = finder(k);				// search for k
	if (endOfBkt(p)) {					// k not found?
		return inserter(p, Entry(k, v));			// insert at end of bucket
	}
	else {						// found it?
		p.ent->setValue(v);				// replace value with v
		return p;						// return this position
	}
}

template <typename K, typename V>		// remove utility
void DoubleHashing<K, V>::eraser(const Iterator& p) {
	p.bkt->erase(p.ent);				// remove entry from bucket
	n--;						// one fewer entry
}

template <typename K, typename V>		// remove entry with key k
void DoubleHashing<K, V>::erase(const K& k) {
	Iterator p = finder(k);				// find k
	if (endOfBkt(p))					// not found?
		throw NonexistentElement("Erase of nonexistent");	// ...error
	eraser(p);						// remove it
}

template <typename K, typename V>		// iterator to end
typename DoubleHashing<K, V>::Iterator DoubleHashing<K, V>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V>		// iterator to front
typename DoubleHashing<K, V>::Iterator DoubleHashing<K, V>::begin() {
	if (empty()) return end();				// emtpty - return end
	BItor bkt = B.begin();				// else search for an entry
	while (bkt->empty()) ++bkt;				// find nonempty bucket
	return Iterator(B, bkt, bkt->begin());		// return first of bucket
}

template <typename K, typename V>		// are iterators equal?
bool DoubleHashing<K, V>::Iterator::operator==(const Iterator& p) const {
	if (ba != p.ba || bkt != p.bkt) return false;	// ba or bkt differ?
	else if (bkt == ba->end()) return true;		// both at the end?
	else return (ent == p.ent);				// else use entry to decide
}

template <typename K, typename V>		// advance to next entry
typename DoubleHashing<K, V>::Iterator& DoubleHashing<K, V>::Iterator::operator++() {
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
typename DoubleHashing<K, V>::Entry&
DoubleHashing<K, V>::Iterator::operator*() const
{
	return *ent;
}
