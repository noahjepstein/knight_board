#include "board.h"

Board::Board(unsigned x, unsigned y) {
    x_dim = x;
    y_dim = y;
}

void readInput() {
    char node;
    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim) {
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
                case default:
                    exit(1);
            }
        }
    }
}

void Board::buildAdjacencyMatrix() {
    return;
}

bool Board::validateMoveSeq(vector<Move> moveSeq) {
    return True;
}


vector<Move> Board::generateMoveSeq(Move start_end_positions) {
    vector<Move> seq (start_end_positions);
    return seq;
}

vector<Move> Board::generateOptimalMoveSeq(Move start_end_positions) {
    vector<Move> seq (start_end_positions);
    return seq;
}
