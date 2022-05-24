class Vertex {
public:
	Vertex(const std::string airportCode, const std::string cityName)
		: airportCode(airportCode), cityName(cityName), hasVisited(false) { }
	const std::string vert() { return airportCode; }
	const std::string getCityName() { return cityName; }
	void setVertValue(const std::string code) { airportCode = code; }
	void setVertName(const std::string name) { cityName = name; }
	void visit() { hasVisited = true; }
	void unvisit() { hasVisited = false; }
	bool getVisit() { return hasVisited; }
private:
	std::string airportCode, cityName;
	bool hasVisited;
};