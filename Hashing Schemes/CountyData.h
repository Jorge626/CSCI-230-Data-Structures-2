#include <string>

struct countyData{
	countyData() { countyName = ""; countyPopulation = 0; }
	countyData(int population, std::string name) { countyPopulation = population; countyName = name; }
	std::string countyName;
	int countyPopulation;
	int getCountyPopulation() const { return countyPopulation; }
	std::string getCountyName() const { return countyName; }
	void setCountyPopulation(int population) { countyPopulation = population; }
	void setCountyName(std::string name) { countyName = name; }
	void insertRecord(int population, std::string name) { countyPopulation = population; countyName = name; }
};