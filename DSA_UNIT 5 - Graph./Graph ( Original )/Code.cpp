#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

class RailwayNetwork {
private:
    int n;                                        // number of stations
    vector<string> names;                         // index -> station name
    map<string, int> idOf;                        // station name -> index
    vector<vector<pair<int, int>>> adj;           // adj[u] = {(v, weight), ...}

    string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    RailwayNetwork() : n(0) {}

    int addStation(const string& name) {
        string key = toLower(name);
        if (idOf.count(key)) return idOf[key];
        idOf[key] = n;
        names.push_back(name);
        adj.push_back({});
        return n++;
    }

    void addTrack(const string& a, const string& b, int w) {
        int u = addStation(a);
        int v = addStation(b);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});                 // undirected track
    }

    int findStation(const string& name) {
        string key = toLower(name);
        return idOf.count(key) ? idOf[key] : -1;
    }

    void displayStations() {
        cout << "\nStations:\n";
        for (int i = 0; i < n; i++)
            cout << "  " << i + 1 << ". " << names[i] << "\n";
    }

    void displayNetwork() {
        cout << "\nRailway Network (Station -> Neighbour [distance]):\n";
        for (int u = 0; u < n; u++) {
            cout << "  " << names[u] << " -> ";
            for (size_t i = 0; i < adj[u].size(); i++) {
                cout << names[adj[u][i].first] << " [" << adj[u][i].second << " km]";
                if (i + 1 < adj[u].size()) cout << ", ";
            }
            cout << "\n";
        }
    }

    void dijkstra(const string& srcName, const string& destName) {
        int src = findStation(srcName);
        int dest = findStation(destName);

        if (src == -1 || dest == -1) {
            cout << "\nError: Invalid source or destination station.\n";
            return;
        }

        vector<int> dist(n, INF);
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);

        // min-heap: (distance, station)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!visited[v] && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\n--------------------------------------------\n";
        if (dist[dest] == INF) {
            cout << "No route exists from " << names[src] << " to " << names[dest] << ".\n";
            return;
        }

        // Rebuild path from destination back to source
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());

        cout << "Source        : " << names[src] << "\n";
        cout << "Destination   : " << names[dest] << "\n";
        cout << "Shortest Dist : " << dist[dest] << " km\n";
        cout << "Route         : ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << names[path[i]];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << "\n--------------------------------------------\n";

        cout << "\nShortest distance from " << names[src] << " to all stations:\n";
        for (int i = 0; i < n; i++) {
            cout << "  " << names[i] << " : ";
            if (dist[i] == INF) cout << "Unreachable\n";
            else cout << dist[i] << " km\n";
        }
    }
};

int main() {
    RailwayNetwork rn;
    int choice;

    // Preloaded sample network
    rn.addTrack("Mumbai", "Pune", 150);
    rn.addTrack("Mumbai", "Nashik", 170);
    rn.addTrack("Pune", "Sangamner", 140);
    rn.addTrack("Nashik", "Sangamner", 90);
    rn.addTrack("Pune", "Solapur", 250);
    rn.addTrack("Sangamner", "Ahmednagar", 70);
    rn.addTrack("Ahmednagar", "Pune", 120);
    rn.addTrack("Ahmednagar", "Aurangabad", 115);
    rn.addTrack("Nashik", "Aurangabad", 190);
    rn.addTrack("Solapur", "Ahmednagar", 200);

    do {
        cout << "\n===== RAILWAY NETWORK - DIJKSTRA =====\n";
        cout << "1. Add station / track\n";
        cout << "2. Display all stations\n";
        cout << "3. Display network\n";
        cout << "4. Find shortest path\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string a, b;
            int w;
            cout << "Enter first station : ";
            getline(cin, a);
            cout << "Enter second station: ";
            getline(cin, b);
            cout << "Enter distance (km) : ";
            cin >> w;
            if (w < 0) {
                cout << "Distance cannot be negative.\n";
                break;
            }
            rn.addTrack(a, b, w);
            cout << "Track added successfully.\n";
            break;
        }
        case 2:
            rn.displayStations();
            break;
        case 3:
            rn.displayNetwork();
            break;
        case 4: {
            string s, d;
            rn.displayStations();
            cout << "\nEnter source station     : ";
            getline(cin, s);
            cout << "Enter destination station: ";
            getline(cin, d);
            rn.dijkstra(s, d);
            break;
        }
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
