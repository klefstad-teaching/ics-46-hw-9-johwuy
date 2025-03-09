#include "dijkstras.h"

int main(int argc, char *argv[]) {
    std::string path = "src/";

    if (argc == 1) {
        path.append("small.txt");
    } else {
        path.append(argv[1]);
    }

    Graph g;
    file_to_graph(path, g);

    vector<int> previous(g.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(g, 0, previous);
    for (int i = 0; i < g.numVertices; ++i) {
        vector<int> the_path = extract_shortest_path(distances, previous, i);
        print_path(the_path, distances[i]);
    }
    return 0;
}