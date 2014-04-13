#include <iostream>

// TicTacToe - Fabio Kreusch
// fabiokr@gmail.com

using namespace std;

bool horizontalWin(string game[3][3]) {
    for(int i = 0; i < 3; i++) {
        bool win = true;

        for(int k = 0; k < 2; k++) {
            if(game[i][k] == "_" || game[i][k] != game[i][k+1]) {
                win = false;
            }
        }

        if(win) {
            cout << "Horizontal win!" << endl;
            return true;
        }
    }

    return false;
}

bool verticalWin(string game[3][3]) {
    for(int i = 0; i < 3; i++) {
        bool win = true;

        for(int k = 0; k < 2; k++) {
            if(game[k][i] == "_" || game[k][i] != game[k+1][i]) {
                win = false;
            }
        }

        if(win) {
            cout << "Vertical win!" << endl;
            return true;
        }
    }

    return false;
}

bool diagonalWin(string game[3][3]) {
    if(((game[0][0] != "_" && game[0][0] == game[1][1]) && game[1][1] == game[2][2]) ||
        ((game[0][2] != "_" && game[0][2] == game[1][1]) && game[1][1] == game[2][0])) {
        cout << "Diagonal win!" << endl;
        return true;
    }

    return false;
}

bool gameFinished(string game[3][3]) {
    return horizontalWin(game) || verticalWin(game) || diagonalWin(game);
}

void askInput(string game[3][3], string player[]) {
    int x, y;

    // asks for x
    cout << player[0] << ", please input your next X position:" << endl;
    cin >> x;

    if(x < 0 || x > 2) {
        cout << "Invalid position " << x << ", should be between 1 and 3." << endl;
        return askInput(game, player);
    }

    // asks for y
    cout << player[0] << ", please input your next Y position:" << endl;
    cin >> y;

    if(y < 0 || y > 2) {
        cout << "Invalid position " << y << ", should be between 1 and 3." << endl;
        return askInput(game, player);
    }

    // valid play?
    if(game[x][y] != "_") {
        cout << "Position [" << x << ", " << y << "] already has a value (" << game[x][y] << ")." << endl;
        return askInput(game, player);
    }

    // sets value
    game[x][y] = player[1];
}

void printBoard(string game[3][3]) {
    cout << endl << "Game status: " << endl << endl;

    for(int i = 0; i < 3; i++) {
        for(int k = 0; k < 3; k++) {
            cout << game[i][k] << " | ";
        }
        cout << endl;
    }

    cout << endl;
}

int main() {
    // the current player
    int currentPlayer = 0;

    // the game board
    string game[3][3] = {
        {"_", "_", "_"},
        {"_", "_", "_"},
        {"_", "_", "_"}
    };

    // players data
    string players[2][2] = {{"P1", "X"}, {"P2", "O"}};

    while(!gameFinished(game)) {
        askInput(game, players[currentPlayer]);
        printBoard(game);

        // switch players
        if(currentPlayer == 0) {
            currentPlayer = 1;
        } else {
            currentPlayer = 0;
        }
    }

    return 0;
}
