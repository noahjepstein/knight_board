#include "board.h"

bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.id == rhs.id;
}

Board::Board(int x, int y) {
    x_dim = x;
    y_dim = y;
    n_nodes = x * y;
    Node placeholder_node;
    nodes.resize(n_nodes, placeholder_node);
}

Board::~Board() {

}

void Board::readInput() {

    char node;

    int n_teleports_found = 0;

    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim; ++j) {
            cin >> node;
            Node new_node;
            new_node.id = i * x_dim + j;
            new_node.x = j;
            new_node.y = i;
            new_node.marked = false;
            switch (node){
                case '.' :
                    new_node.type = PLAIN;
                    new_node.weight = 1;
                    break;

                case 'W' :
                    new_node.type = WATER;
                    new_node.weight = 2;
                    break;

                case 'B' :
                    new_node.type = BARRIER;
                    break;

                case 'R' :
                    new_node.type = ROCK;
                    break;

                case 'T' :
                    new_node.type = TELEPORT;
                    new_node.weight = 1;
                    if (n_teleports_found == 0) {
                        tele.x1 = i;
                        tele.y1 = j;
                        n_teleports_found++;
                    } else if (n_teleports_found == 1){
                        tele.x2 = i;
                        tele.y2 = j;
                    } else {
                        cerr << "INVALID INPUT." << endl;
                        exit(1);
                    }
                    break;

                case 'L' :
                    new_node.type = LAVA;
                    new_node.weight = 5;
                    break;

                default:
                    exit(1);
            }
            nodes[new_node.id] = new_node;
        }
    }
}

bool Board::onBoard(int x1, int y1){
    return ((x1 >= 0) && (x1 < x_dim) && (y1 >= 0) && (y1 < y_dim));
}

bool Board::areNeighbors(int nid1, int nid2) {
    Node n1, n2;
    if ((nid1 >= 0) && (nid1 < n_nodes) && (nid2 >= 0) && (nid2 < n_nodes)) {
        n1 = nodes[nid1];
        n2 = nodes[nid2];
        auto neigh = find(begin(n1.neighbors), end(n1.neighbors), n2);
        return (neigh != end(n1.neighbors));
    } else {
        return false;
    }
}

void Board::makeNeighbors(Node n1, Node n2) {
    n1.neighbors.push_back(n2);
    n2.neighbors.push_back(n1);
}

bool Board::validKnightMovePattern(Move m) {

    return ((((m.x2 - m.x1) == -1) && ((m.y2 - m.y1) == -2)) ||
            (((m.x2 - m.x1) == -1) && ((m.y2 - m.y1) ==  2)) ||
            (((m.x2 - m.x1) == -2) && ((m.y2 - m.y1) == -1)) ||
            (((m.x2 - m.x1) == -2) && ((m.y2 - m.y1) ==  1)) ||
            (((m.x2 - m.x1) ==  1) && ((m.y2 - m.y1) == -2)) ||
            (((m.x2 - m.x1) ==  1) && ((m.y2 - m.y1) ==  2)) ||
            (((m.x2 - m.x1) ==  2) && ((m.y2 - m.y1) == -1)) ||
            (((m.x2 - m.x1) ==  2) && ((m.y2 - m.y1) ==  1)));
}

int Board::c2ID(int x, int y) {
    return y * x_dim + x;
}

bool Board::moveEquality(Move m1, Move m2) {

    return (((m1.x1 == m2.x1) && (m1.x2 == m2.x2) && (m1.y1 == m2.y1) && (m1.y2 == m2.y2)) ||
            ((m1.x1 == m2.x2) && (m1.x2 == m2.x1) && (m1.y1 == m2.y2) && (m1.y2 == m2.y1)));
}

bool Board::validMove(int x1, int y1, int x2, int y2) {

    Move m;
    m.x1 = x1;
    m.y1 = y1;
    m.x2 = x2;
    m.y1 = y2;
    Node n1, n2;

    if ((onBoard(x1, y1)) && (onBoard(x2, y2))) {
        n1 = nodes[c2ID(x1, y1)];
        n2 = nodes[c2ID(x2, y2)];
        if (areNeighbors(c2ID(x1, y1), c2ID(x2, y2))) {
            return true;
        } else if   (((n1.type != ROCK)
                   && (n2.type != ROCK)
                   && validKnightMovePattern(m)
                   && !crossesBarriers(m))
                   || moveEquality(m, tele)) {
            makeNeighbors(n1, n2);
            return true;
        }
    }
    return false;
}

bool Board::crossesBarriers(Move m) {
    m.x1 = 0;
    return false;
}

void Board::findNeighbors() {
/*
    void Board::findNeighbors()
    args: none
    returns: none
    Used to call validMove for each node/move combo.
    Also initializes the edge for the teleport move.
*/

    Node n;

    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim; ++j) {

            validMove(j, i, j - 1, i - 2);
            validMove(j, i, j + 1, i - 2);
            validMove(j, i, j - 2, i - 1);
            validMove(j, i, j + 2, i - 1);
            validMove(j, i, j - 2, i + 1);
            validMove(j, i, j + 2, i + 1);
            validMove(j, i, j - 1, i + 2);
            validMove(j, i, j + 1, i + 2);
        }
    }
    validMove(tele.x1, tele.y1, tele.x2, tele.y2);
}

bool Board::validateMoveSeq(vector<Move> moveSeq) {
    Move m;
    moveSeq.push_back(m);
    return true;
}


vector<Move> Board::generateMoveSeq(Move start_end_positions) {
    vector<Move> seq;
    seq.push_back(start_end_positions);
    return seq;
}

vector<Move> Board::generateOptimalMoveSeq(Move start_end_positions) {
    vector<Move> seq;
    seq.push_back(start_end_positions);
    return seq;
}

vector<Move> Board::generateLongestSeq(Move start_end_positions) {
    vector<Move> seq;
    seq.push_back(start_end_positions);
    return seq;
}
