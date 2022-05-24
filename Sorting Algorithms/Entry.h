#pragma once
template <typename K, typename V>
class Entry { // a (key, value) pair
public: // public functions
	Entry(const K& k = K(), const V& v = V()) // constructor
		: _key(k), _value(v) { }
	const K& key() { return _key; } // get key
	const V& value() { return _value; } // get value
	void setKey(const K& k) { _key = k; } // set key
	void setValue(const V& v) { _value = v; } // set value
private: // private data
	K _key; // key
	V _value; // value
};