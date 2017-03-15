#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

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

Board::Board(unsigned x, unsigned y) {
    x_dim = x;
    y_dim = y;
}

void Board::readInput() {
    char node;
    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim; ++j) {
            cin >> node;
            switch (node) {
                case '.' :
                    // add plain node
                    break;
                case 'W' :
                    // add water node, counts as two moves
                    break;
                case 'B' :
                    // add barrier node, no edges can cross the barrier
                    break;
                case 'R' :
                    // add rock node, can't land on the rock
                    break;
                case 'T' :
                    // teleport node, instantly transports you from T to T
                    break;
                case 'L' :
                    // add lava node, counts as five moves
                    break;
                default:
                    exit(1);
            }
        }
    }
}

void Board::buildAdjacencyMatrix() {
    return;
}

bool Board::validateMoveSeq(vector<Move> moveSeq) {
    return true;
}


vector<Move> Board::generateMoveSeq(Move start_end_positions) {
    vector<Move> seq;
    return seq;
}

vector<Move> Board::generateOptimalMoveSeq(Move start_end_positions) {
    vector<Move> seq;
    return seq;
}


int main() {
    unsigned x, y;
    cin >> x >> y;
    Board board(x, y);
    board.readInput();
    board.buildAdjacencyMatrix();
    return 0;
}
