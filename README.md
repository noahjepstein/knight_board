### Knight Board

Does some chess style path planning...plus lava obstacles and teleportation.

#### Building
- `$ git clone https://github.com/noahjepstein/knight_board.git`
- `$ cd knight_board/knight_board`
- `$ mkdir build`
- `$ cd build`
- `$ cmake -G "Unix Makefiles" ..`
- `$ make`

#### Run an example:
- `$ ./build/knight_board < tests/complex_board_input.txt`

#### Test file format
~~~~
start_pos_x start_pos_y
end_pos_x end_pos_y
board_dim_x board_dim_y
[x_dim * y_dim WHITESPACE SEPARATED BOARD SQUARE VALUES]
~~~~


### Solutions:

__Level 1:__ See `Board::validateMoveSeq()`. Takes a vector of moves, where a move is defined as a start position.
- Checks that the move is valid in isolation with `Board::validMove()`:
    - is a knight-type move pattern
    - doesn't cross barriers or hit rocks
    - special case: teleport
- Check that each move in the sequence is contiguous -- end position of previous move is start position of next move.

__Level 2:__ See `Board::generateMoveSeq()`, which performs DFS to find a path for a given start and end position using `Board::DFSgenerateMoveSeq()`.

__Level 3:__ See `Board::generateOptimalMoveSeq()` which uses Dijkstra to find the shortest path from a start node to an end node. Uses `Board::DijkstraGenerateShortestMoveSeq()` and `Board::backTrackMoveSeq()` to help.

__Level 4:__ All functions used for 1-3 were written with the 32x32 board in mind, so work for both the complex and simple input versions. The board used can be given as an input text file, with format similar to `./knight_board/tests/complex_board_input.txt`

__Level 5:__ See `Board::generateLongestSeq()`. Have a brute force implementation using negated edge weights and Dijkstra. Since we can mark visited spaces and not visit them again, we don't have the issues with negative cycles that Dijkstra would normally run into.
