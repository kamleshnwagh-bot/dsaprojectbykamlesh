#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <limits>
#include <algorithm>
#include <sstream>
using namespace std;

const int INF = numeric_limits<int>::max();

class RailwayNetwork {
private:
    int n;                                        // number of stations
    vector<string> names;                         // index -> station name
    map<string, int> idOf;                        // station name -> index
    vector<vector<pair<int, int>>> adj;           // adj[u] = {(v, weight), ...}
    vector<int> dist;                             // shortest distances of last run
    vector<int> parent;                           // previous station on shortest path

    static string trim(const string& s) {
        size_t b = s.find_first_not_of(" \t\r\n");
        if (b == string::npos) return "";
        size_t e = s.find_last_not_of(" \t\r\n");
        return s.substr(b, e - b + 1);
    }

    static string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    RailwayNetwork() : n(0) {}

    int addStation(const string& rawName) {
        string name = trim(rawName);
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

    int findStation(const string& rawName) {
        string key = toLower(trim(rawName));
        return idOf.count(key) ? idOf[key] : -1;
    }

    string stationName(int i) { return names[i]; }

    // Modification C: update the weight of an existing track
    bool updateTrack(const string& a, const string& b, int w, int& oldW) {
        int u = findStation(a);
        int v = findStation(b);
        if (u == -1 || v == -1 || u == v) return false;
        bool found = false;
        for (auto& e : adj[u])
            if (e.first == v) { oldW = e.second; e.second = w; found = true; }
        for (auto& e : adj[v])
            if (e.first == u) e.second = w;
        return found;
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

    // Dijkstra's algorithm from the selected source station
    void dijkstra(int src) {
        dist.assign(n, INF);
        parent.assign(n, -1);
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
    }

    // Modification B: complete station sequence from source to station v
    string pathTo(int v) {
        vector<int> path;
        for (int x = v; x != -1; x = parent[x]) path.push_back(x);
        reverse(path.begin(), path.end());
        string s;
        for (size_t i = 0; i < path.size(); i++) {
            s += names[path[i]];
            if (i + 1 < path.size()) s += " -> ";
        }
        return s;
    }

    // Run Dijkstra from src and display the result for dest
    void showResult(int src, int dest) {
        dijkstra(src);

        cout << "\n--------------------------------------------\n";
        if (dist[dest] == INF) {
            cout << "No route exists from " << names[src] << " to " << names[dest] << ".\n";
        } else {
            cout << "Source        : " << names[src] << "\n";
            cout << "Destination   : " << names[dest] << "\n";
            cout << "Shortest Dist : " << dist[dest] << " km\n";
            cout << "Route         : " << pathTo(dest) << "\n";
        }
        cout << "--------------------------------------------\n";

        cout << "\nShortest distance and path from " << names[src] << " to all stations:\n";
        for (int i = 0; i < n; i++) {
            cout << "  " << names[i] << " : ";
            if (dist[i] == INF) cout << "Unreachable\n";
            else cout << dist[i] << " km  [" << pathTo(i) << "]\n";
        }
    }
};

// Read a whole line as an integer (re-asks until valid)
int readInt(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) return 0;
        stringstream ss(line);
        int x;
        char extra;
        if (ss >> x && !(ss >> extra)) return x;
        cout << "Invalid number. Try again.\n";
    }
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int main() {
    RailwayNetwork rn;
    int choice;
    string curSrc = "", curDest = "";             // last selected source / destination

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
        cout << "4. Find shortest path (select source and destination)\n";
        cout << "5. Change source station and recalculate\n";
        cout << "6. Update edge weight and recalculate\n";
        cout << "7. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
        case 1: {
            string a = readLine("Enter first station : ");
            string b = readLine("Enter second station: ");
            int w = readInt("Enter distance (km) : ");
            if (rn.findStation(a) != -1 && rn.findStation(a) == rn.findStation(b)) {
                cout << "A track needs two different stations.\n";
                break;
            }
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
            rn.displayStations();
            string s = readLine("\nEnter source station     : ");
            string d = readLine("Enter destination station: ");
            int src = rn.findStation(s), dest = rn.findStation(d);
            if (src == -1 || dest == -1) {
                cout << "\nError: Invalid source or destination station.\n";
                break;
            }
            curSrc = rn.stationName(src);
            curDest = rn.stationName(dest);
            rn.showResult(src, dest);
            break;
        }
        case 5: {
            rn.displayStations();
            string s = readLine("\nEnter new source station : ");
            int src = rn.findStation(s);
            if (src == -1) {
                cout << "\nError: Invalid source station.\n";
                break;
            }
            int dest = rn.findStation(curDest);
            if (dest == -1) {
                string d = readLine("Enter destination station: ");
                dest = rn.findStation(d);
                if (dest == -1) {
                    cout << "\nError: Invalid destination station.\n";
                    break;
                }
            }
            curSrc = rn.stationName(src);
            curDest = rn.stationName(dest);
            cout << "\nSource changed to " << curSrc << ". Recalculating...\n";
            rn.showResult(src, dest);
            break;
        }
        case 6: {
            rn.displayNetwork();
            string a = readLine("\nEnter first station of the track : ");
            string b = readLine("Enter second station of the track: ");
            int w = readInt("Enter new distance (km)           : ");
            if (w < 0) {
                cout << "Distance cannot be negative.\n";
                break;
            }
            int oldW = 0;
            if (!rn.updateTrack(a, b, w, oldW)) {
                cout << "\nError: No track exists between these stations.\n";
                break;
            }
            cout << "\nTrack updated: " << rn.stationName(rn.findStation(a)) << " - "
                 << rn.stationName(rn.findStation(b)) << " changed from "
                 << oldW << " km to " << w << " km.\n";
            int src = rn.findStation(curSrc), dest = rn.findStation(curDest);
            if (src == -1 || dest == -1) {
                cout << "Use option 4 to find the shortest path with the new weight.\n";
            } else {
                cout << "Recalculating shortest paths...\n";
                rn.showResult(src, dest);
            }
            break;
        }
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
