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

bool validInput(int v) {
    if(v < 0 || v > 2) {
        cout << "Invalid position " << v << ", should be one of [0, 1, 2]" << endl;
        return false;
    }

    return true;
}

void askInput(string game[3][3], string player[]) {
    int x, y;

    // asks for x
    cout << player[0] << ", please input your next horizontal position:" << endl;
    cin >> x;

    if(!validInput(x)) {
        return askInput(game, player);
    }

    // asks for y
    cout << player[0] << ", please input your next vertical position:" << endl;
    cin >> y;

    if(!validInput(y)) {
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
    int currentPlayer = 1;

    // the game board
    string game[3][3] = {
        {"_", "_", "_"},
        {"_", "_", "_"},
        {"_", "_", "_"}
    };

    // players data
    string players[2][2] = {{"Player 1", "X"}, {"Player 2", "O"}};

    while(!gameFinished(game)) {
        // switch players
        currentPlayer = currentPlayer == 0 ? 1 : 0;

        askInput(game, players[currentPlayer]);
        printBoard(game);
    }

    cout << players[currentPlayer][0] << " wins the game!" << endl;

    return 0;
}
