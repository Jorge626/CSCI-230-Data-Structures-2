#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Vertex.h"
#include "Edge.h"
#include "Entry.h"


class Graph {
public:
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
	int adjacencyList[100][100];

	Graph(std::string portsInfoFile, std::string flightsInfoFile) 
	{
		std::ifstream airportInfo;
		std::ifstream flightInfo;
		airportInfo.open("C:\\Users\\jorge\\Desktop\\" + portsInfoFile);
		if (airportInfo.fail())
		{
			std::cin.ignore();
			std::cout << "Error: File not found!\nPress enter key to exit...\n";
			std::getchar();
			exit(1);
		}
		else
		{
			std::cout << "Reading file and inserting airport information onto vertices...\n";
			std::string airportCode, cityName, info;
			while (std::getline(airportInfo, info))
			{
				std::stringstream line(info);
				std::getline(line, airportCode, ' ');
				std::getline(line, cityName, '\n');
				cityName.erase(0, 3);
				vertices.push_back(Vertex(airportCode, cityName));
			}
			airportInfo.close();
		}
		flightInfo.open("C:\\Users\\jorge\\Desktop\\" + flightsInfoFile);
		if (flightInfo.fail())
		{
			std::cin.ignore();
			std::cout << "Error: File not found!\nPress enter key to exit...\n";
			std::getchar();
			exit(1);
		}
		else
		{
			std::cout << "Reading file and inserting flight information onto edges...\n";
			std::string sourceFlight, destinationFlight, flightNumber;
			float costOfFlight;
			while (flightInfo >> sourceFlight >> destinationFlight >> costOfFlight >> flightNumber)
			{
				edges.push_back(Edge(sourceFlight, destinationFlight, getVertIndex(sourceFlight), getVertIndex(destinationFlight), costOfFlight, flightNumber));
			}
			airportInfo.close();
		}
		for (int i = 0; i < edges.size(); i++)
		{
			adjacencyList[edges[i].sourceIndex()][edges[i].destinationIndex()] = 1;
		}
		for (int i = 0; i < vertices.size(); i++)
		{
			for (int j = 0; j < vertices.size(); j++)
			{
				if (adjacencyList[i][j] != 1)
					adjacencyList[i][j] = 0;
			}
		}
	}

	void printVertAdjacencies() {
		for (int i = 0; i < vertices.size(); i++)
		{
			std::cout << "Airport: " << vertices[i].vert() << "\n";
			std::vector<int> adjIndex;
			for (int j = 0; j < vertices.size(); j++) {
				if (adjacencyList[i][j] == 1) {
					adjIndex.push_back(j);
				}
			}
			std::cout << adjIndex.size() << " Total flight(s):\n";
			for (int k = 0; k < adjIndex.size(); k++) {
				std::cout << "Flight to " << vertices[adjIndex[k]].getCityName() << " (" << vertices[adjIndex[k]].vert() << ") for $"
					<< std::fixed << std::setprecision(2) << edges[findEdge(vertices[i].vert(), vertices[adjIndex[k]].vert())].costOfFlight();
				std::cout << ", " << edges[findEdge(vertices[i].vert(), vertices[adjIndex[k]].vert())].getFlightNumber() << "\n";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void printAdjList() {
		for (int i = 0; i < vertices.size(); i++)
		{
			for (int j = 0; j < vertices.size(); j++)
			{
				std::cout << adjacencyList[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void printAllAirports() {
		for (int i = 0; i < vertices.size(); i++)
			std::cout << vertices[i].vert() << " " << vertices[i].getCityName() << "\n";
	}

	bool isAirport(std::string code) {
		for (int i = 0; i < vertices.size(); i++)
			if (code == vertices[i].vert())
				return true;
		return false;
	}

	void removeAirport(std::string code)
	{
		int sourceIndex = getVertIndex(code);
		for (int i = 0; i < edges.size(); i++)
		{
			if (adjacencyList[i][sourceIndex] == 1)
			{
				adjacencyList[i][sourceIndex] = 0;
				edges.erase(edges.begin() + findEdge(i, sourceIndex));
			}
			else if (adjacencyList[sourceIndex][i] == 1)
			{
				adjacencyList[sourceIndex][i] = 0;
				edges.erase(edges.begin() + findEdge(sourceIndex, i));
			}
		}

		for (int i = 0; i < vertices.size(); i++)
			for (int j = 0; j < vertices.size(); j++)
				adjacencyList[i][j] = 0;

		vertices.erase(vertices.begin() + sourceIndex);
		for (int i = 0; i < edges.size(); i++)
		{
			edges[i].setSourceIndex(getVertIndex(edges[i].getSourcePort()));
			edges[i].setDestinationIndex(getVertIndex(edges[i].getDestinationPort()));
		}

		for (int i = 0; i < edges.size(); i++)
		{
			adjacencyList[edges[i].sourceIndex()][edges[i].destinationIndex()] = 1;
		}
	
		for (int i = 0; i < vertices.size(); i++)
		{
			for (int j = 0; j < vertices.size(); j++)
			{
				if (adjacencyList[i][j] != 1)
					adjacencyList[i][j] = 0;
			}
		}
		std::cout << "Airport " << code << " has ben removed\n";
	}

	int findEdge(std::string a, std::string c)
	{
		for (int i = 0; i < edges.size(); i++)
			if (edges[i].getSourcePort() == a && edges[i].getDestinationPort() == c)
				return i;
			else if (edges[i].getSourcePort() == c && edges[i].getDestinationPort() == a)
				return i;
		return -1;
	}

	int findEdge(int a, int c)
	{
		for (int i = 0; i < edges.size(); i++)
			if (edges[i].sourceIndex() == a && edges[i].destinationIndex() == c)
				return i;
		return -1;
	}

	void printAirportInfo(std::string code) {
		std::cout << "Airport: " << vertices[getVertIndex(code)].vert() << " in " << vertices[getVertIndex(code)].getCityName() << "\n";
		std::vector<int> adjIndex;
		for (int j = 0; j < vertices.size(); j++) {
			if (adjacencyList[getVertIndex(code)][j] == 1) {
				adjIndex.push_back(j);
			}
		}
		std::cout << adjIndex.size() << " Total flight(s):\n";
		for (int k = 0; k < adjIndex.size(); k++) {
			std::cout << "Flight to " << vertices[adjIndex[k]].getCityName() << " (" << vertices[adjIndex[k]].vert() << ") for $"
				<< std::fixed << std::setprecision(2) << edges[findEdge(vertices[getVertIndex(code)].vert(), vertices[adjIndex[k]].vert())].costOfFlight();
			std::cout << ", " << edges[findEdge(vertices[getVertIndex(code)].vert(), vertices[adjIndex[k]].vert())].getFlightNumber() << "\n";
		}
		std::cout << "\n";
	}

	void addFlight(std::string source, std::string destination) {
		int sourceIndex = getVertIndex(source), destinationIndex = getVertIndex(destination);
		std::string flightNum;
		float cost;
		if (adjacencyList[sourceIndex][destinationIndex] == 1) {
			std::cout << "Flight from " << source << " to " << destination << " already exists\n";
			std::cout << "Updating information...\n";
			std::cout << "Please enter the new flight number: ";
			std::cin >> flightNum;
			edges[findEdge(source, destination)].setFlightNumber(flightNum);
			std::cout << "Please enter the new cost of this flight: $";
			std::cin >> cost;
			edges[findEdge(source, destination)].setCostOfFlight(cost);
			std::cout << "Flight from " << source << " to " << destination << " has been updated with:\n";
			std::cout << "Flight number: " << flightNum;
			std::cout << "\nCost: $" << cost << "\n";
		}
		else
		{
			adjacencyList[sourceIndex][destinationIndex] = 1;
			std::cout << "Please enter the flight number: ";
			std::cin >> flightNum;
			std::cout << "Please enter the cost of this flight: $";
			std::cin >> cost;
			edges.push_back(Edge(source, destination, getVertIndex(source), getVertIndex(destination), cost, flightNum));
			std::cout << "Flight from " << source << " to " << destination << " has been added with:\n";
			std::cout << "Flight number: " << flightNum;
			std::cout << "\nCost: $" << cost << "\n";
		}
	}

	void deleteFlight(std::string source, std::string destination) {
		int sourceIndex = getVertIndex(source), destinationIndex = getVertIndex(destination);
		if (adjacencyList[sourceIndex][destinationIndex] == 1)
		{
			edges.erase(edges.begin() + findEdge(source, destination));
			adjacencyList[sourceIndex][destinationIndex] = 0;
			std::cout << "Flight from " << source << " to " << destination << " has been deleted\n";
		}
		else
			std::cout << "Error: No flight from " << source << " to " << destination << " was found\n";
	}

	int edgeIndex(std::string a, std::string b)
	{
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i].getSourcePort() == a && edges[i].getFlightNumber() == b)
				return i;
			else if (edges[i].getDestinationPort() == a && edges[i].getSourcePort() == b)
				return i;
		}
		return -1;
	}

	int getVertIndex(std::string vert)
	{
		for (int i = 0; i < vertices.size(); i++)
			if (vertices[i].vert() == vert)
				return i;
		return -1;
	}

	void unvisitAll() {
		for (int i = 0; i < vertices.size(); i++)
			vertices[i].unvisit();
		for (int i = 0; i < edges.size(); i++)
			edges[i].unvisit();
	}

	bool allVertVisited() {
		bool yes = true;
		for (int i = 0; i < vertices.size(); i++)
			if (!vertices[i].getVisit())
				yes = false;
		return yes;
	}

	bool neighborsVisited()
	{
		std::stack<std::string> tempNeighbors = neighbors;
		bool yes = true;
		while (tempNeighbors.size() != 0)
		{
			if (!vertices[getVertIndex(tempNeighbors.top())].getVisit())
				yes = false;
			tempNeighbors.pop();
		}
		return yes;
	}

	void getNeighbors(std::string c) {
		for (int i = 0; i < edges.size(); i++)
			if (edges[i].getSourcePort() == c)
				neighbors.push(edges[i].getDestinationPort());
	}

	void dijkstra(std::string source, std::string destination, float& totalCost, bool allFlights)
	{
		std::list<Entry> dijkstraList;
		std::list<std::string> visited, unvisited;

		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices[i].vert() == source) {
				dijkstraList.push_front(Entry(vertices[i].vert(), 0, source));
				unvisited.push_front(vertices[i].vert());
			}
			else if (vertices[i].vert() == destination) {
				unvisited.push_back(vertices[i].vert());
			}
			else {
				dijkstraList.push_back(Entry(vertices[i].vert(), INT_MAX, source));
				unvisited.push_back(vertices[i].vert());
			}
		}
		dijkstraList.push_back(Entry(destination, INT_MAX, source));
		std::list<Entry>::iterator itDijkstra = dijkstraList.begin();
		for (std::list<std::string>::iterator itUnvisit = unvisited.begin(); itUnvisit != unvisited.end(); itUnvisit++)
		{
			getNeighbors(*itUnvisit);
			while ((*itDijkstra).vert() != (*itUnvisit))
				itDijkstra++;
			unsigned int currentDistance = (*itDijkstra).totalDistance();
			itDijkstra = dijkstraList.begin();
			while (neighbors.size() != 0)
			{
				bool isVisited = false;
				for (std::list<std::string>::iterator it = visited.begin(); it != visited.end(); it++) {
					if (neighbors.top() == *it)
						isVisited = true;
				}
				if (isVisited && neighbors.top() != destination) {
					neighbors.pop();
				}
				else {
					unsigned int index = findEdge(*itUnvisit, neighbors.top());
					while ((*itDijkstra).vert() != neighbors.top())
						itDijkstra++;
					unsigned int totalPath = currentDistance + edges[index].costOfFlight();
					if ((*itDijkstra).totalDistance() > totalPath) {
						(*itDijkstra).updateDistance(totalPath);
						(*itDijkstra).addTotalFlights();
						(*itDijkstra).prevVertex = *itUnvisit;
					}
					itDijkstra = dijkstraList.begin();
					neighbors.pop();
				}
			}
			visited.push_back(*(itUnvisit));
		}
		if (!allFlights) {
			itDijkstra = dijkstraList.end();
			itDijkstra--;
			std::vector<std::string> path;
			std::string prevVert = (*itDijkstra).prevVertex;
			for (itDijkstra; itDijkstra != dijkstraList.begin(); itDijkstra--) {
				if ((*itDijkstra).vert() == prevVert) {
					path.push_back(prevVert);
					prevVert = (*itDijkstra).prevVertex;
				}
			}
			std::string v1 = source, v2 = path.at(path.size() - 1);
			int index;
			std::cout << "Least expensive flight(s) to " << destination << " from " << source << ":\n" << source;
			for (int i = path.size() - 1; i >= 0; --i) {
				v2 = path[i];
				index = findEdge(v1, v2);
				std::cout << " -- " << edges[index].getFlightNumber() << " ($" << std::fixed << std::setprecision(2) << edges[index].costOfFlight() << ") --> " << path[i];
				totalCost = totalCost + edges[index].costOfFlight();
				v1 = path[i];
			}
			v2 = destination;
			index = findEdge(v1, v2);
			totalCost = totalCost + edges.at(index).costOfFlight();
			std::cout << " -- " << edges[index].getFlightNumber() << " ($" << std::fixed << std::setprecision(2) << edges[index].costOfFlight() << ") --> " << destination;
			std::cout << "\nTotal cost: $" << std::fixed << std::setprecision(2) << totalCost << "\n";
		}
		else
		{
			std::stack<std::list<Entry>::iterator> allPaths;
			for (itDijkstra = dijkstraList.begin(); itDijkstra != dijkstraList.end(); itDijkstra++)
			{
				if ((*itDijkstra).totalDistance() < INT_MAX)
					allPaths.push(itDijkstra);
			}
			std::cout << "All flight from " << source << " to " << destination << ":\n";
			while (!allPaths.empty())
			{
				std::vector<std::string> path;
				std::list<Entry>::iterator currentPathIt = allPaths.top();
				std::string prevVert = (*currentPathIt).prevVertex;
				for (currentPathIt; currentPathIt != dijkstraList.begin(); currentPathIt--) {
					if ((*currentPathIt).vert() == prevVert) {
						path.push_back(prevVert);
						prevVert = (*currentPathIt).prevVertex;
					}
				}
				std::string v1 = source, v2;
				int index;
				std::cout << source;
				for (int i = path.size() - 1; i >= 0; --i) {
					v2 = path[i];
					index = findEdge(v1, v2);
					if (index != -1)
					{
						std::cout << " -- " << edges[index].getFlightNumber() << " ($" << std::fixed << std::setprecision(2) << edges[index].costOfFlight() << ") --> " << path[i];
						totalCost = totalCost + edges[index].costOfFlight();
						v1 = path[i];
					}
				}
				v2 = destination;
				index = findEdge(v1, v2);
				if (index != -1) {
					totalCost = totalCost + edges[index].costOfFlight();
					std::cout << " -- " << edges[index].getFlightNumber() << " ($" << std::fixed << std::setprecision(2) << edges[index].costOfFlight() << ") --> " << destination;
					std::cout << "\nTotal cost: $" << std::fixed << std::setprecision(2) << totalCost << "\n";
				}
				allPaths.pop();
			}
		}
	}

private:
	std::stack<std::string> myStack;
	std::stack<std::string> neighbors;
	std::stack<std::string> prevVertices;
	std::queue<std::string> myQueue;
	int totalVisited;
};
