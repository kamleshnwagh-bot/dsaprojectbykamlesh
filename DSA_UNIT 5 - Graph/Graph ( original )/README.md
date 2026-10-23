# Railway Network: Shortest Route using Dijkstra's Algorithm

A C++ program that represents **railway stations as vertices** and **track links as weighted edges**, then applies **Dijkstra's algorithm** to find the shortest distance and station sequence between a selected source and destination.

---

## 📌 Problem Statement

Develop a C++ program to represent railway stations as vertices and track links as weighted edges, where weights represent distance or travel cost. Apply Dijkstra's algorithm from a selected station and display the shortest distance and station sequence to a selected destination.

---

## 🎯 Objective

- Represent a railway network as a weighted graph using an adjacency list.
- Implement Dijkstra's algorithm using a min-priority queue.
- Display the shortest distance and the complete station sequence.
- Handle edge cases such as invalid stations and unreachable destinations.

---

## ✨ Features

- Menu-driven program
- Add new stations and tracks at runtime (station names are case-insensitive)
- Preloaded sample railway network
- Display all stations and the full network
- Shortest distance and route from a source to a destination
- Shortest distance from the source to all other stations
- Clear messages for "Invalid station" and "No route exists"
- Input validation (negative distances are rejected)

---

## 🧠 Concept Used

The railway network is modelled as an **undirected weighted graph**:

| Railway Term | Graph Term |
|--------------|------------|
| Station | Vertex |
| Track link | Edge |
| Distance / travel cost | Edge weight |

Dijkstra's algorithm works on graphs with non-negative weights. It always finalizes the unvisited station with the smallest known distance, then updates (relaxes) the distances of its neighbours. A `parent[]` array stores the previous station on the best path, so the route can be rebuilt after the search.

---

## ⚙️ Algorithm (Summary)

1. Build the graph using an adjacency list (station = vertex, track = edge with distance as weight).
2. Read the source and destination stations; display an error if either is invalid.
3. Initialize `dist[] = INFINITY`, `parent[] = -1`, `visited[] = false`.
4. Set `dist[source] = 0` and push `(0, source)` into a min-priority queue.
5. Remove the station `u` with the smallest distance and mark it visited.
6. For each neighbour `v` of `u` with weight `w`, if `dist[u] + w < dist[v]`, update `dist[v]` and `parent[v] = u`, then push `(dist[v], v)` into the queue.
7. Repeat until the queue is empty.
8. If `dist[destination] = INFINITY`, display "No route exists".
9. Otherwise, trace `parent[]` from the destination back to the source and reverse it to get the route.
10. Display the shortest distance and the route.

---

## ⏱️ Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Add station / track | O(log n) | O(1) |
| Dijkstra's algorithm | O((V + E) log V) | O(V + E) |
| Path reconstruction | O(V) | O(V) |

*V = number of stations, E = number of tracks, n = number of stations stored.*

---

## 📁 Project Structure

```
Railway-Dijkstra/
│── railway_dijkstra.cpp  # Source code
│── Algorithm.pdf         # Step-wise algorithm
│── Flowchart.pdf         # Flowchart of the program
│── Output.png            # Program output screenshots
│── Output_Analysis.md    # Analysis of the output
│── Report.pdf            # Project report
│── README.md             # Project documentation
```

---

## 🚀 How to Compile and Run

**Requirements:** a C++ compiler (g++ recommended)

```bash
g++ railway_dijkstra.cpp -o railway_dijkstra
./railway_dijkstra
```

On Windows:

```bash
g++ railway_dijkstra.cpp -o railway_dijkstra.exe
railway_dijkstra.exe
```

---

## 🧪 Sample Input and Output

**Preloaded tracks (distance in km):**

| Station A | Station B | Distance |
|-----------|-----------|----------|
| Mumbai | Pune | 150 |
| Mumbai | Nashik | 170 |
| Pune | Sangamner | 140 |
| Nashik | Sangamner | 90 |
| Pune | Solapur | 250 |
| Sangamner | Ahmednagar | 70 |
| Ahmednagar | Pune | 120 |
| Ahmednagar | Aurangabad | 115 |
| Nashik | Aurangabad | 190 |
| Solapur | Ahmednagar | 200 |

**Source: Mumbai**

| Destination | Shortest Distance | Route |
|-------------|-------------------|-------|
| Ahmednagar | 270 km | Mumbai -> Pune -> Ahmednagar |
| Sangamner | 260 km | Mumbai -> Nashik -> Sangamner |
| Aurangabad | 360 km | Mumbai -> Nashik -> Aurangabad |
| Solapur | 400 km | Mumbai -> Pune -> Solapur |
| Delhi | Invalid station | Error message displayed |

**Example run (Mumbai to Ahmednagar):**

```
Source        : Mumbai
Destination   : Ahmednagar
Shortest Dist : 270 km
Route         : Mumbai -> Pune -> Ahmednagar
```

---

## ⚠️ Edge Cases Handled

- Source or destination station not present in the network
- Source and destination are the same station (distance 0)
- Destination not reachable from the source
- Duplicate station names (reused, case-insensitive)
- Negative distance input
- Invalid menu choice

---

## 💡 Applications

- Route planning in railway and metro networks
- GPS and road navigation systems
- Network routing protocols (e.g., OSPF)
- Logistics and delivery path optimization

---

## 🔮 Future Scope

- Add track or station deletion
- Support directed (one-way) tracks
- Use travel time or ticket cost as alternate weights
- Load the railway network from a file

---

## 👤 Author

**Name:** Your Name
**Roll No:** Your Roll Number
**Course:** Data Structures and Algorithms
**Institute:** Your College / University

---

⭐ If you found this project helpful, consider giving it a star!
