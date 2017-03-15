#include "board.h"
#include <iostream>

using namespace std;

Board::Board(unsigned x, unsigned y) {
    x_dim = x;
    y_dim = y;
}

Board::~Board() {

}

void Board::readInput() {
    char node;
    for (unsigned i = 0; i < y_dim; ++i) {
        for (unsigned j = 0; j < x_dim; ++j) {
            cin >> node;

            switch (node){
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
