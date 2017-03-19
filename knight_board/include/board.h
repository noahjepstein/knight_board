/*  board.h
    Header for board class.
    Represents the solution for the knight board challenge.
    Author: Noah J Epstein
            noahjepstein@gmail.com
*/


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
#include <unordered_map>

#include <unistd.h>

#define INF 0x3f3f3f3f
#define SLEEP_INTERVAL 600000

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
    int id, x, y, weight;
    Nodetype type;
    bool marked;
    vector<NodeID> neighbors;
};

typedef pair<int, int> dPair;

class Board {

public:
    Board        (int x_dim, int y_dim);
    ~Board       ();
    void         readInput();
    void         printBoard();
    void         findNeighbors();
    bool         validateMoveSeq(vector<Move> moveSeq);
    vector<Move> generateMoveSeq(Move start_end_positions);
    vector<Move> generateOptimalMoveSeq(Move start_end_positions);
    vector<Move> generateLongestSeq(Move start_end_positions);

private:
    int x_dim, y_dim, n_nodes;
    vector<Node> nodes;
    Coord knight_pos;
    Move tele;

    int          signMult(int x);
    int          c2ID(int x, int y);
    bool         validMove(int x1, int y1, int x2, int y2);
    bool         validMove(Move m);
    Move         makeMove(Node n1, Node n2);
    Move         makeMove(NodeID nid1, NodeID nid2);
    bool         onBoard(int x1, int y1);
    bool         crossesBarriers(Move m);
    bool         areNeighbors(NodeID nid1, NodeID nid2);
    void         makeNeighbors(NodeID nid1, NodeID nid2);
    bool         validKnightMovePattern(Move m);

    vector<Move> backTrackMoveSeq(unordered_map<NodeID, NodeID> &prev, NodeID src, NodeID end);
    vector<Move> DFSgenerateMoveSeq(Move start_end_positions);
    vector<Move> DijkstraGenerateShortestMoveSeq(Move start_end_positions);
    vector<Move> dijkstraGenerateLongestMoveSeq(Move start_end_positions);

 };

#endif
