class Edge {
public:
	Edge(const std::string source, const std::string destination, int sourceIndex, int destinationIndex, float costOfFlight, std::string flightNum)
		: sourcePort(source), destinationPort(destination), indexSource(sourceIndex), indexDestination(destinationIndex),
		cost(costOfFlight), flightNumber(flightNum), hasVisited(false) { }
	const std::string getSourcePort() { return sourcePort; }
	const std::string getDestinationPort() { return destinationPort; }
	const int sourceIndex() { return indexSource; }
	const int destinationIndex() { return indexDestination; }
	const std::string getFlightNumber() { return flightNumber; }
	const float costOfFlight() { return cost; }
	void setFlightPath(const std::string source, const std::string destination) { sourcePort = source; destinationPort = destination; }
	void setCostOfFlight(float costOf) { cost = costOf; }
	void setSourceIndex(int i) { indexSource = i; }
	void setDestinationIndex(int i) { indexDestination = i; }
	void setFlightNumber(std::string flightNum) { flightNumber = flightNum; }
	void visit() { hasVisited = true; }
	void unvisit() { hasVisited = false; }
	bool getVisit() { return hasVisited; }
private:
	std::string sourcePort, destinationPort, flightNumber;
	int indexSource, indexDestination;
	float cost;
	bool hasVisited;
};