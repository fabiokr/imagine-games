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
            cout << "Vitoria horizontal!" << endl;
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
            cout << "Vitoria vertical!" << endl;
            return true;
        }
    }

    return false;
}

bool diagonalWin(string game[3][3]) {
    if(((game[0][0] != "_" && game[0][0] == game[1][1]) && game[1][1] == game[2][2]) ||
        ((game[0][2] != "_" && game[0][2] == game[1][1]) && game[1][1] == game[2][0])) {
        cout << "Vitoria diagonal!" << endl;
        return true;
    }

    return false;
}

bool winner(string game[3][3]) {
    return horizontalWin(game) || verticalWin(game) || diagonalWin(game);
}

bool completed(string game[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int k = 0; k < 2; k++) {
            if(game[i][k] == "_") {
                return false;
            }
        }
    }

    return true;
}

int readInput() {
    int v;
    cin >> v;

    if(cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Valor nao eh um numero" << endl;
        return readInput();
    } else if(v < 0 || v > 2) {
        cout << "Posicao invalida " << v << ", deve ser um dentre [0, 1, 2]" << endl;
        return readInput();
    }

    return v;
}

void askInput(string game[3][3], string player[]) {
    int x, y;

    // asks for x
    cout << player[0] << ", por favor entre com sua posicao horizontal:" << endl;
    x = readInput();

    // asks for y
    cout << player[0] << ", por favor entre com sua posicao vertical:" << endl;
    y = readInput();

    // valid play?
    if(game[x][y] != "_") {
        cout << "Posicao[" << x << ", " << y << "] ja possui um valor (" << game[x][y] << ")." << endl;
        return askInput(game, player);
    }

    // sets value
    game[x][y] = player[1];
}

void printBoard(string game[3][3]) {
    cout << endl << "Status do jogo: " << endl << endl;

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
    string players[2][2] = {{"Jogador 1", "X"}, {"Jogador 2", "O"}};

    while(true) {
        // switch players
        currentPlayer = currentPlayer == 0 ? 1 : 0;

        askInput(game, players[currentPlayer]);
        printBoard(game);

        if(winner(game)) {
            cout << players[currentPlayer][0] << " venceu o jogo!" << endl;
            break;
        } else if(completed(game)) {
            cout << "O jogo terminou em empate." << endl;
            break;
        }
    }

    return 0;
}
