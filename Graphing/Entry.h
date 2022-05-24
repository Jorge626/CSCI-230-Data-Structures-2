class Entry {
public:
	Entry(const std::string v, unsigned int dist, const std::string source)
		: _vert(v), distance(dist), prevVertex(source), totalFlights(0) { }
	std::string prevVertex;
	const std::string vert() { return _vert; }
	const unsigned int totalDistance() { return distance; }
	const unsigned int getTotalFlight() { return totalFlights; }
	void setFlightsOne() { totalFlights = 1; }
	void updateDistance(int i) { distance = i; }
	void addTotalFlights() { totalFlights++; }
private:
	std::string _vert;
	unsigned int distance, totalFlights;
};