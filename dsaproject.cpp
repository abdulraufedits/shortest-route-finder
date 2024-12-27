#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MAX_INT = 20;

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

struct Vehicle {
    string type;
    string model;
    string numPlate;
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
    bool isCompleted = false;
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
void findShortestRoute(string src, string dest, const Vehicle& vehicle, const User& user);
void displayRoute();
void displayRoutes();
void menu();
void printAdjList();

int main() {

    initMap();
	printAdjList();
    cout << "-------------------------------------\n";
    Vehicle vehicle = { "Car", "Toyota", "XYZ123", 0.1, 2.0 }; // Example vehicle
    User user = { 1, "John Doe", "1234567890", false }; // Example user
	findShortestRoute("DHA Phase-2", "Beach", vehicle, user);
    //int srcId = 1; // Example source point ID
    //int destId = 7; // Example destination point ID
    //Route route = findShortestRoute(srcId, destId, vehicle, user);

    //cout << "Shortest route from " << srcId << " to " << destId << ":" << endl;
    //cout << "From " << route.start.name << " to " << route.end.name << endl;
    //cout << "Distance: " << route.totalDistance << " km, Petrol: " << route.totalPetrol << " liters, Time: " << route.totalTime << " mins" << endl;

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


//void findShortestRoute(string src, string dest, Vehicle& vehicle, User& user) {
//    vector<double> dist(MAX_INT, MAX_INT);
//    vector<int> prev(MAX_INT, -1);
//    vector<bool> known(MAX_INT, false);
//
//    int srcIndex = findPointIndex(src);
//    int destIndex = findPointIndex(dest);
//
//    if (srcIndex == -1 || destIndex == -1) {
//        cout << "Invalid source or destination." << endl;
//        return;
//    }
//
//    dist[srcIndex] = 0;
//


    //    while (!known[findPointIndex(dest)]) {
    //        cout << "Entered while loop\n";
    //        if (!known[current]) {
    //            cout << "Entered if statement\n";
    //            for (auto &neighbor : adjList[current]) {
    //                cout << "Entered in neighbor id " << neighbor.id << endl;
    //                if (!known[neighbor.id]) {
    //                    cout << "Entered neighbor not known\n";
    //                    if (dist[neighbor.id] > neighbor.distance + dist[current]) {
    //                        cout << "Neighbour distance changed\n";
    //                        dist[neighbor.id] = neighbor.distance + dist[current];
    //                        prev[neighbor.id] = current;
    //                    }
    //                    if (min > dist[neighbor.id]) {
    //                        cout << "Entered min condition\n";
    //                        min = dist[neighbor.id];
    //                    }
    //                }
    //            }
    //            for (int j = 0; j < MAX_INT; j++) {
    //                cout << "Entered for loop\n";
    //                if (dist[j] == min) {
    //                    cout << "Updated current to " << j << endl;
    //                    current = j;
    //                    known[j] = true;
    //                    break;
    //                }
    //            }
    //        }
    //    }
    //}

void findShortestRoute(string src, string dest, const Vehicle & vehicle, const User & user) {
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

    cout << "Shortest route from " << src << " to " << dest << ":" << endl;
    for (int i = 0; i < path.size(); ++i) {
        cout << nodes[path[i]];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    double totalDistance = dist[destIndex];
    double totalPetrol = totalDistance * vehicle.litrePerKm;
    double totalTime = totalDistance * vehicle.minsPerKm;

    cout << "Distance: " << totalDistance << " km, Petrol: " << totalPetrol << " liters, Time: " << totalTime << " mins" << endl;
}


void displayRoute() {
    // Display ride details
}

void displayRoutes() {
    // Display all rides
}

void menu() {
    // Implement the command-line interface here
    cout << "Welcome to the Google Maps alternate desktop app!" << endl;
    // Add options to find routes, display rides, etc.
}

void printAdjList() {
    for (int i = 0; i < 18; i++) {
		cout << nodes[i] << " is connected to : ";
        for(Point p: adjList[i]) {
            cout << "-> " << p.id << " " << p.name <<" (" << p.distance << "km) ";
        }
        cout << endl;
    }
}
