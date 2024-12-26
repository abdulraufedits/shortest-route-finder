#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MAX_INT = 100;

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
//Point findPoint(vector<Point> src, string name);
void findShortestRoute(string src, string dest, const Vehicle& vehicle, const User& user);
void displayRoute();
void displayRoutes();
void menu();
void printAdjList();

//class Queue {
//private:
//    struct QNode {
//        int data;
//        QNode* next;
//        QNode(int d) : data(d), next(nullptr) {}
//    };
//
//    QNode* front, * rear;
//
//public:
//    Queue() : front(nullptr), rear(nullptr) {}
//
//    bool isEmpty() {
//        return (front == nullptr);
//    }
//
//    void enqueue(int item) {
//        QNode* temp = new QNode(item);
//        if (rear == nullptr) {
//            front = rear = temp;
//            return;
//        }
//        rear->next = temp;
//        rear = temp;
//    }
//
//    int dequeue() {
//        if (isEmpty())
//            return -1;
//        QNode* temp = front;
//        front = front->next;
//        if (front == nullptr)
//            rear = nullptr;
//        int item = temp->data;
//        delete temp;
//        return item;
//    }
//
//    int frontItem() {
//        if (isEmpty())
//            return -1;
//        return front->data;
//    }
//
//    int rearItem() {
//        if (isEmpty())
//            return -1;
//        return rear->data;
//    }
////};

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

//for (int i = 0; i < MAX_INT; ++i) {
//    int u = -1;
//    for (int j = 0; j < MAX_INT; ++j) {
//        if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
//            u = j;
//        }
//    }
//
//    if (dist[u] == MAX_INT) {
//        break;
//    }
//
//    visited[u] = true;
//
//    for (const auto& neighbor : adjList[u]) {
//        int v = neighbor.id;
//        double weight = neighbor.distance;
//
//        if (dist[u] + weight < dist[v]) {
//            dist[v] = dist[u] + weight;
//            prev[v] = u;
//        }
//    }
//}

//vector<int> path;
//for (int at = destId; at != -1; at = prev[at]) {
//    path.push_back(at);
//}
//reverse(path.begin(), path.end());
//
//if (path.size() == 1 && path[0] != srcId) {
//    return {}; // No path found
//}
//
//vector<Route> routes;
//for (size_t i = 0; i < path.size() - 1; ++i) {
//    Point start = adjList[path[i]][0];
//    Point end = adjList[path[i + 1]][0];
//    double totalDistance = start.distance;
//    double totalPetrol = totalDistance * vehicle.litrePerKm;
//    double totalTime = totalDistance * vehicle.minsPerKm;
//
//    Route route = { vehicle, user, start, end, totalDistance, totalPetrol, totalTime, false };
//    routes.push_back(route);
//}

void findShortestRoute(string src, string dest, const Vehicle& vehicle, const User& user) {
    vector<double> dist(MAX_INT, MAX_INT);
    vector<int> prev(MAX_INT, -1);
    vector<bool> known(MAX_INT, false);
    dist[findPointIndex(src)] = 0;
	known[findPointIndex(src)] = true;

    cout << findPointIndex(src) << endl;

    for (int i = 0; i < MAX_INT; i++) {
        if (!known[i]) {
            for (auto &neighbor : adjList[i]) {
				dist[neighbor.id] = neighbor.distance;
				prev[neighbor.id] = i;
				known[neighbor.id] = true;
            }
        }
    }
	for (int i = 0; i < MAX_INT; i++) {
        if (known[findPointIndex(dest)]) {
            cout << dist[i] << endl;
            cout << prev[i] << endl;
        }
	}
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
