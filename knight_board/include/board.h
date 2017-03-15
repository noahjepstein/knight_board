#ifndef BOARD_H
#define BOARD_H

using namespace std;

struct Move {
    unsigned x1, y1, x2, y2;
};

struct Node {
    unsigned id, x, y, cost;
    bool marked;
};

struct Edge {
    unsigned weight;
    bool marked;
    vector<Node> neighbors;
};

class Board {

public:
    Board        (unsigned x_dim, unsigned y_dim);
    void         readInput();
    void         buildAdjacencyMatrix();
    bool         validateMoveSeq(std::vector<Move> moveSeq);
    vector<Move> generateMoveSeq(Move start_end_positions);
    vector<Move> generateOptimalMoveSeq(Move start_end_positions);

private:
    unsigned x_dim, y_dim;
    vector< vector<Node> > nodes;
    vector<Edge> adjList;
};

#endif
