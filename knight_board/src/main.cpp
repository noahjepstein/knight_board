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

#include "board.h"

int main() {
    unsigned x, y;
    cin >> x >> y;
    Board board(x, y);
    board.readInput();
    board.buildAdjacencyMatrix();
    return 0;
}
