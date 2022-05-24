/* Program: Airport Graph
Author: Jorge Aranda
Class: CSCI 230
Date: 6/1/20
Description: Reads in two files. One containing a list of airport codes and names, another containg
flight information between airports. Creates a graph of this information and allows various operations, 
such as displaying airport information, finding cheapest flights, finding cheapest roundtrips, adding flights, 
and deleting flights. Also implements extra credit options 7 and 9, which finds all flights from one airport
to another as well as deletes an airport, respectively. At the end of the program, creates a new text file
with updated flight information as well as updated airports for option 9.
I certify that the code below is my own work.
Exception(s): 
*/
#include "Graph.h"

char menu()
{
	char choice = NULL;
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Menu~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "1. Display airport information\n";
	std::cout << "2. Find a cheapest flight from one airport to another airport\n";
	std::cout << "3. Find a cheapest roundtrip from one airport to another airport\n";
	std::cout << "4. Add a flight from one airport to another airport\n";
	std::cout << "5. Delete a flight from one airport to another airport\n";
	std::cout << "6. Find a flight with fewest stops from one airport to another airport\n";
	std::cout << "7. Find all flights from one airport to another airport\n";
	std::cout << "8. Find an order to visit all airports starting from an airport\n";
	std::cout << "9. Delete an existing airport\n";
	std::cout << "Q. Exit\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Please enter any choice: ";
	std::cin >> choice;
	return choice;
}

int main()
{
	std::string ports = "P4Airports.txt", flights = "P4Flights.txt";
	Graph airportGraph(ports, flights);

	char choice;
	do {
		choice = menu();
		switch (choice)
		{
		case '0':
		{
			airportGraph.printVertAdjacencies();
			airportGraph.printAdjList();
			break;
		}
		case '1':
		{
			std::cin.ignore();
			std::string code;
			std::cout << "Please enter the aiport code: ";
			std::cin >> code;
			bool isAirport = airportGraph.isAirport(code);
			if (!isAirport)
				std::cout << "Error: No airport found with the given code\n";
			else
				airportGraph.printAirportInfo(code);
			break;
		}
		case '2':
		{
			std::cin.ignore();
			std::string depart, arrive;
			std::cout << "Please enter the airport's code to depart from: ";
			std::cin >> depart;
			bool isAirport = airportGraph.isAirport(depart);
			if (!isAirport)
				std::cout << "Error: No airport found with the given code\n";
			else {
				std::cout << "Please enter the aiport's code you would like to arrive to: ";
				std::cin >> arrive;
				isAirport = airportGraph.isAirport(arrive);
				if (!isAirport)
					std::cout << "Error: No airport found with the given code\n";
				else
				{
					try
					{
						float total = 0;
						airportGraph.dijkstra(depart, arrive, total, false);
					}
					catch (...)
					{
						std::cout << "Error: No flights found from " << depart << " airport to " << arrive << " airport\n";
					}
				}
			}
			break;
		}
		case '3':
		{
			std::cin.ignore();
			std::string depart, arrive;
			std::cout << "Please enter the airport's code to depart from: ";
			std::cin >> depart;
			bool isAirport = airportGraph.isAirport(depart);
			if (!isAirport)
				std::cout << "Error: No airport found with the given code\n";
			else {
				std::cout << "Please enter the aiport's code you would like to arrive to: ";
				std::cin >> arrive;
				isAirport = airportGraph.isAirport(arrive);
				if (!isAirport)
					std::cout << "Error: No airport found with the given code\n";
				else
				{
					int firstTotal = 0, secondTotal = 0;
					try
					{
						float firstTotal = 0, secondTotal = 0;
						airportGraph.dijkstra(depart, arrive, firstTotal, false);
						airportGraph.dijkstra(arrive, depart, secondTotal, false);
						std::cout << "Total for roundtrip: $" << std::fixed << std::setprecision(2) << firstTotal + secondTotal << "\n";
					}
					catch (...)
					{
						std::cout << "Error: No roundtrip found for " << depart << " airport and " << arrive << " airport\n";
					}
				}
			}
			break;
		}
		case '4':
		{
			std::cin.ignore();
			std::string depart, arrive;
			std::cout << "Please enter the departing airport's code to add a flight to: ";
			std::cin >> depart;
			bool isAirport = airportGraph.isAirport(depart);
			if (!isAirport)
				std::cout << "Error: No airport found with the given code\n";
			else {
				std::cout << "Please enter the arriving airport's code to add a flight from " << depart << ": ";
				std::cin >> arrive;
				if (!isAirport)
					std::cout << "Error: No airport found with the given code\n";
				else
					airportGraph.addFlight(depart, arrive);
			}
			break;
		}
		case '5':
		{
			std::string depart, arrive;
			std::cout << "Please enter the departing airport's code to delete its flight: ";
			std::cin >> depart;
			bool isAirport = airportGraph.isAirport(depart);
			if (!isAirport)
				std::cout << "Error: No airport found with the given code\n";
			else {
				std::cout << "Please enter the arriving airport's code to delete flight from " << depart << ": ";
				std::cin >> arrive;
				if (!isAirport)
					std::cout << "Error: No airport found with the given code\n";
				else
					airportGraph.deleteFlight(depart, arrive);
			}
			std::cin.ignore();
			break;
		}
		case '6':
		{
			std::cin.ignore();
			std::cout << "Option Unavailable\n";
			break;
		}
		case '7':
		{
			std::cin.ignore();		
			std::string depart, arrive;
			std::cout << "Please enter the departing airport's code: ";
			std::cin >> depart;
			bool isAirport = airportGraph.isAirport(depart);
			if (!isAirport)
				std::cout << "Error: No airport found with the given code\n";
			else {
				std::cout << "Please enter the arriving airport's code to find all flight from " << depart << ": ";
				std::cin >> arrive;
				if (!isAirport)
					std::cout << "Error: No airport found with the given code\n";
				else
				{
					float total = 0;
					try {
						airportGraph.dijkstra(depart, arrive, total, true);
					}
					catch (...)
					{
						std::cout << "Error: No flight(s) found from " << depart << " to " << arrive << "\n";
					}
				}
			}
			break;
		}
		case '8':
		{
			std::cin.ignore();
			std::cout << "Option Unavailable\n";
			break;
		}
		case '9':
		{
			std::cin.ignore();
			std::string code;
			std::cout << "Please enter the airport code to remove: ";
			std::cin >> code;
			airportGraph.removeAirport(code);
			break;
		}
		case 'I':
		{
			std::cin.ignore();
			airportGraph.printAllAirports();
			break;
		}
		case 'Q': {
			std::cout << "Thank you for using my program!\n";
			break;
		}
		default:
		{
			std::cout << "\nError: Please enter a valid option\n";
			break;
		}
		}

	} while (choice != 'Q');

	std::cout << "Creating a new file, P4FlightsRev1.txt, with updated flights...\n";
	std::ofstream P4RevisedFile;
	P4RevisedFile.open("P4FlightsRev1.txt");
	for (int i = 0; i < airportGraph.edges.size(); i++)
	{
		P4RevisedFile << airportGraph.edges[i].getSourcePort() << "   " << airportGraph.edges[i].getDestinationPort() << "    " << std::fixed << std::setprecision(2) << airportGraph.edges[i].costOfFlight() << "  " << airportGraph.edges[i].getFlightNumber() << "\n";
	}
	std::cout << "P4FlightsRev1.txt file created...\nClosing file...\n";
	P4RevisedFile.close();
	std::cout << "Creating a new file, P4AirportsRev1.txt, with updated airports...\n";
	P4RevisedFile.open("P4AirportsRev1.txt");
	for (int i = 0; i < airportGraph.vertices.size(); i++)
	{
		P4RevisedFile << airportGraph.vertices[i].vert() << "    " << airportGraph.vertices[i].getCityName() << "\n";
	}
	std::cout << "P4AirportsRev1.txt file created...\nClosing file...\n";
	P4RevisedFile.close();

	std::cin.ignore();
	std::cout << "Press enter key to exit...\n";
	std::getchar();
}
