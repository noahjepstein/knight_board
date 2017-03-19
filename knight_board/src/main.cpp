/*  main.cpp
    Client of Board class.
    Represents the solution for the knight board challenge.
    Author: Noah J Epstein
            noahjepstein@gmail.com
*/


#include "board.h"

int main() {

    Move m;
    unsigned x, y;

    cout << "Start X Coord? " << endl;
    cin >> m.x1;
    cout << endl << "Start Y Coord? " << endl;
    cin >> m.y1;
    cout << "End X Coord? " << endl;
    cin >> m.x2;
    cout << endl << "End Y Coord? " << endl;
    cin >> m.y2;
    cin >> x >> y;

    Board board(x, y);
    board.readInput();
    board.printBoard();
    board.findNeighbors();

    /* level 2 */
    vector<Move> mseq = board.generateMoveSeq(m);
    board.validateMoveSeq(mseq);

    /* level 3 */
    vector<Move> mseq = board.generateOptimalMoveSeq(m);
    board.validateMoveSeq(mseq);

    /* level 5 */
    vector<Move> mseq = board.generateLongestSeq(m);
    board.validateMoveSeq(mseq);

    return 0;
}
