#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MAX_INT = 200;

struct Point {
	int id;
	string name;
	double distance = 0;
};

struct User {
	int id;
	string name;
	string contact;
	bool isUrgent = false;
};

User user;

struct Vehicle {
	string type;
	double litrePerKm;
	double minsPerKm;
};

struct Route {
	Vehicle vehicle;
	User user;
	Point start;
	Point end;
	double totalDistance;
	double totalPetrol;
	double totalTime;
};

struct Node {
	int id;
	Route route;
	Node* next;
};

string nodes[MAX_INT] = {
	"DHA Phase-2",
	"DHA Phase-4",
	"DHA Phase-5",
	"Beach",
	"Teen Talwar",
	"Clifton",
	"Defence",
	"Do Darya",
	"Boat Basin",
	"Port Grand",
	"REX Center",
	"Techno City Mall",
	"Bolton Market",
	"Jodia Bazaar",
	"Ranchore Line",
	"Nanak Wara",
	"Garden",
	"Abidabad"
};

vector<Point> adjList[MAX_INT];

void addEdge(Point u, Point v);
void initMap();
void findShortestRoute(string src, string dest, Route route);
void displayRoutes();
int menu();
void printAdjList();

int main() {
	int exit = 0;
	initMap();
	cout << "--------------Welcome to the Shortest Route Finder desktop app!---------------" << endl;
	while (true) {
		exit = menu();
		if (exit == -1) {
			break;
		}
	}
	return 0;
}

void addEdge(Point u, Point v) {
	adjList[u.id].push_back(v);
	adjList[v.id].push_back(u);
}

void initMap() {
	// Initialize points
	Point dha2 = { 0, "DHA Phase-2" };
	Point dha4 = { 1, "DHA Phase-4" };
	Point dha5 = { 2, "DHA Phase-5" };
	Point beach = { 3, "Beach" };
	Point teenTalwar = { 4, "Teen Talwar" };
	Point clifton = { 5, "Clifton" };
	Point defence = { 6, "Defence" };
	Point doDarya = { 7, "Do Darya" };
	Point boatBasin = { 8, "Boat Basin" };
	Point portGrand = { 9, "Port Grand" };
	Point rexCenter = { 10, "REX Center" };
	Point technoCityMall = { 11, "Techno City Mall" };
	Point boltonMarket = { 12, "Bolton Market" };
	Point jodiaBazaar = { 13, "Jodia Bazaar" };
	Point ranchoreLine = { 14, "Ranchore Line" };
	Point nanakWara = { 15, "Nanak Wara" };
	Point garden = { 16, "Garden" };
	Point abidabad = { 17, "Abidabad" };

	// Add edges
	dha2.distance = 2.7; dha4.distance = 2.7;
	addEdge(dha2, dha4);
	dha4.distance = 1.5; dha5.distance = 1.5;
	addEdge(dha4, dha5);
	dha2.distance = 5.7; dha5.distance = 5.7;
	addEdge(dha2, dha5);
	dha5.distance = 3.0; beach.distance = 3.0;
	addEdge(dha5, beach);
	beach.distance = 2.0; teenTalwar.distance = 2.0;
	addEdge(beach, teenTalwar);
	teenTalwar.distance = 1.0; clifton.distance = 1.0;
	addEdge(teenTalwar, clifton);
	clifton.distance = 2.5; defence.distance = 2.5;
	addEdge(clifton, defence);
	defence.distance = 4.0; doDarya.distance = 4.0;
	addEdge(defence, doDarya);
	doDarya.distance = 3.5; boatBasin.distance = 3.5;
	addEdge(doDarya, boatBasin);
	boatBasin.distance = 5.0; portGrand.distance = 5.0;
	addEdge(boatBasin, portGrand);
	portGrand.distance = 2.0; rexCenter.distance = 2.0;
	addEdge(portGrand, rexCenter);
	rexCenter.distance = 1.5; technoCityMall.distance = 1.5;
	addEdge(rexCenter, technoCityMall);
	technoCityMall.distance = 1.0; boltonMarket.distance = 1.0;
	addEdge(technoCityMall, boltonMarket);
	boltonMarket.distance = 0.5; jodiaBazaar.distance = 0.5;
	addEdge(boltonMarket, jodiaBazaar);
	jodiaBazaar.distance = 1.0; ranchoreLine.distance = 1.0;
	addEdge(jodiaBazaar, ranchoreLine);
	ranchoreLine.distance = 1.5; nanakWara.distance = 1.5;
	addEdge(ranchoreLine, nanakWara);
	nanakWara.distance = 2.0; garden.distance = 2.0;
	addEdge(nanakWara, garden);
	garden.distance = 3.0; abidabad.distance = 3.0;
	addEdge(garden, abidabad);
	garden.distance = 1.0; ranchoreLine.distance = 1.0;
	addEdge(garden, ranchoreLine);
}


int findPointIndex(string name) {
	for (int i = 0; i < MAX_INT; i++) {
		if (nodes[i] == name) {
			return i;
		}
	}
	return -1;
}



void findShortestRoute(string src, string dest, Route route) {


	vector<double> dist(MAX_INT, MAX_INT);
	vector<int> prev(MAX_INT, -1);
	vector<bool> known(MAX_INT, false);
	int srcIndex = findPointIndex(src);
	int destIndex = findPointIndex(dest);

	if (srcIndex == -1 || destIndex == -1) {
		cout << "Invalid source or destination." << endl;
		return;
	}

	dist[srcIndex] = 0;
	for (int i = 0; i < MAX_INT; ++i) {
		int u = -1;
		for (int j = 0; j < MAX_INT; ++j) {
			if (!known[j] && (u == -1 || dist[j] < dist[u])) {
				u = j;
			}
		}

		if (dist[u] == MAX_INT) {
			break;
		}

		known[u] = true;

		for (const Point& neighbor : adjList[u]) {
			double alt = dist[u] + neighbor.distance;
			if (alt < dist[neighbor.id]) {
				dist[neighbor.id] = alt;
				prev[neighbor.id] = u;
			}
		}
	}

	if (dist[destIndex] == numeric_limits<double>::infinity()) {
		cout << "No route found from " << src << " to " << dest << "." << endl;
		return;
	}

	vector<int> path;
	for (int at = destIndex; at != -1; at = prev[at]) {
		path.push_back(at);
	}
	reverse(path.begin(), path.end());

	cout << "\nShortest route from " << src << " to " << dest << ":" << endl;
	for (int i = 0; i < path.size(); ++i) {
		cout << nodes[path[i]];
		if (i < path.size() - 1) {
			cout << " -> ";
		}
	}
	cout << endl;

	route.user = user;
	route.vehicle = Vehicle{ "Car", 0.3, 6.0 };
	route.totalDistance = dist[destIndex];

	route.totalPetrol = route.totalDistance * route.vehicle.litrePerKm;
	route.totalTime = route.totalDistance * route.vehicle.minsPerKm;

	cout << "Distance: " << route.totalDistance << " km\nTotal Time and petrol consumed:\n";
	cout << "By Car (" << route.totalTime << " minutes) (" << route.totalPetrol << ")\n";

	route.vehicle = Vehicle{ "Motorbike", 0.14, 7.1 };
	route.totalPetrol = route.totalDistance * route.vehicle.litrePerKm;
	route.totalTime = route.totalDistance * route.vehicle.minsPerKm;

	cout << "By motorbike (" << route.totalTime << " minutes) (" << route.totalPetrol << ")\n";

	route.vehicle = Vehicle{ "Bicycle", 0, 10.0 };
	route.totalPetrol = route.totalDistance * route.vehicle.litrePerKm;
	route.totalTime = route.totalDistance * route.vehicle.minsPerKm;

	cout << "By bicycle (" << route.totalTime << " minutes) (" << route.totalPetrol << ")\n";

	route.vehicle = Vehicle{ "Foot", 0, 20.0 };
	route.totalPetrol = route.totalDistance * route.vehicle.litrePerKm;
	route.totalTime = route.totalDistance * route.vehicle.minsPerKm;

	cout << "By foot (" << route.totalTime << " minutes) (" << route.totalPetrol << ")\n";
	cout << "-------------------------------------\n";
	return;
}


int menu() {
	int option = 0;
	Route route;
	string src, dest;
	cout << "Please select an option:" << endl;
	cout << "[1] Find a route" << endl;
	cout << "[2] See all routes" << endl;
	cout << "[3] Exit application" << endl;
	cin >> option;
	if (option == 1) {
	again:
		cout << "Source: Search for a place\n";
		cin.ignore();
		getline(cin, src);
		if (findPointIndex(src) == -1) {
			cout << "Place not found.\n";
			goto again;
		}
		route.start = { findPointIndex(src), src };
	again2:
		cout << "Destination: Search for a place\n";
		getline(cin, dest);
		if (findPointIndex(dest) == -1) {
			cout << "Place not found.\n";
			goto again2;
		}
		route.end = { findPointIndex(dest), dest };
		cout << "Finding the shortest route from " << src << " to " << dest << "..." << endl;
		findShortestRoute(src, dest, route);
	}
	else if (option == 2) {
		displayRoutes();
	}
	else if (option == 3) {
		cout << "Exiting application..." << endl;
		return -1;
	}
	else {
		cout << "Invalid option." << endl;
	}
}

void displayRoutes() {
	// Display all routes
	for (int i = 0; i < MAX_INT; i++) {
		if (nodes[i] != "") {
			cout << (i + 1) << " " << nodes[i] << endl;
		}
	}
}

void printAdjList() {
	for (int i = 0; i < 20; i++) {
		cout << nodes[i] << " is connected to : ";
		for (Point p : adjList[i]) {
			cout << "-> " << p.id << " " << p.name << " (" << p.distance << "km) ";
		}
		cout << endl;
	}
}
