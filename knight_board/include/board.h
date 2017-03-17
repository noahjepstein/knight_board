#ifndef BOARD_H
#define BOARD_H

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
#include <sstream>
#include <iostream>
#include <algorithm>

#include <unistd.h>

using namespace std;

enum Nodetype {
    PLAIN, WATER, ROCK, BARRIER, LAVA, TELEPORT
};

typedef int NodeID;

struct Coord {
    int x, y;
};

struct Move {
    int x1, y1, x2, y2;
};

struct Node {
    int id, x, y;
    Nodetype type;
    int weight;
    bool marked;
    vector<NodeID> neighbors;
};

class Board {

public:
    Board        (int x_dim, int y_dim);
    ~Board       ();
    void         readInput();
    void         printBoard();
    void         findNeighbors();
    bool         validateMoveSeq(std::vector<Move> moveSeq);
    vector<Move> generateMoveSeq(Move start_end_positions);
    vector<Move> generateOptimalMoveSeq(Move start_end_positions);
    vector<Move> generateLongestSeq(Move start_end_positions);

private:
    int x_dim, y_dim, n_nodes;
    vector<Node> nodes;
    Coord knight_pos;
    Move tele;


    int          c2ID(int x, int y);
    bool         validMove(int x1, int y1, int x2, int y2);
    bool         validMove(Move m);
    Move         makeMove(Node n1, Node n2);
    bool         onBoard(int x1, int y1);
    bool         crossesBarriers(Move m);
    bool         areNeighbors(NodeID nid1, NodeID nid2);
    void         makeNeighbors(NodeID nid1, NodeID nid2);
    bool         validKnightMovePattern(Move m);

    vector<Move> DFSgenerateMoveSeq(Move start_end_positions);
    vector<Move> DijkstraGenerateMoveSeq(Move start_end_positions);

 };

#endif
