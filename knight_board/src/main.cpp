#include "board.h"

int main() {
    unsigned x, y;
    cin >> x >> y;
    Board board(x, y);
    board.readInput();
    board.printBoard();
    board.findNeighbors();

    Move m = {0, 0, 10, 10};

    vector<Move> mseq = board.generateMoveSeq(m);

    // cout << "valid move sequence? " << board.validateMoveSeq(mseq) << endl;

    return 0;
}
