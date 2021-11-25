// Copyright 2021 Muhammad Fahad Farid fahadf@bu.edu
// Copyright 2021 Samir Farhat Dominguez safarhat@bu.edu
// Copyright 2021 Kevin Vogt-Lowell kjv@bu.edu

#include "movedef.h"
using std::string;
using std::cout;

// Rule violation: '
// 2+ unique wins(checked in main loop)
// Unbalanced Xs and Os
// This helps ignore illegitimate double wins
bool checkInvalid(string tttboard) {
    int xCount = 0;
    int oCount = 0;
    for(char c: tttboard) {
        if(c == 'x') xCount++;
        if(c == 'o') oCount++;
    }
    if(xCount - oCount >= 2 || xCount - oCount >= 2 ) return true;
    else return false;
}

// Bad shape and bad chars
bool checkErrorCondition(string tttboard) {
    if(tttboard.length() != 9) return true;
    for(char c: tttboard) {
        if(c != 'x' || c!= 'o' || c != '#') return true;
    }
    return false;
}

// Row columns must be unique
int checkRows(string tttboard, char player) {
    int winCount = 0;
    int index = 0;
    for(int i =0; i < 3; i++) {
        index = i*3;
        if(tttboard.at(index) == player && tttboard.at(index+1) == player && tttboard.at(index+2) == player) {
            winCount++;
        }
    }
    // If greater than 1 thats a rule violation
    return winCount;
}

// Column wins must be unique
int checkColumns(string tttboard, char player) {
    int winCount = 0;
    for(int i =0; i < 3; i++) {
        if(tttboard.at(i) == player && tttboard.at(i+3) == player && tttboard.at(i+3) == player) {
            winCount++;
        }
    }
    // If greater than 1 thats a rule violation
    return winCount;
}

// Diagonal wins share middle square
int checkDiagonals(string tttboard, char player) {
    int winCount =0;
    // top left diagonal
    if(tttboard.at(0) == player && tttboard.at(4) == player && tttboard.at(8) == player) {
        winCount++;
    }
    // top right diagonal
    if(tttboard.at(2) == player && tttboard.at(4) == player && tttboard.at(6) == player) {
        winCount++;
    }
    return winCount;
}

char tttanalyzer(string tttboard) {
    // edge cases
    // check too many winners
    if(checkInvalid(tttboard)) return 'i';
    if(checkErrorCondition(tttboard)) return 'e';

    int xWins = 0;
    int oWins = 0;
    int temp;

    //compile x wins
    temp = checkRows(tttboard, 'x');
    if(temp > 1) return 'i';
    else xWins += temp;
    temp = checkColumns(tttboard, 'x');
    if(temp > 1) return 'i';
    else xWins += temp;
    temp = checkDiagonals(tttboard, 'x');
    if(temp > 1) return 'i';
    else xWins += temp;

    //compile o  wins
    temp = checkRows(tttboard, 'o');
    if(temp > 1) return 'i';
    else oWins += temp;
    temp = checkColumns(tttboard, 'o');
    if(temp > 1) return 'i';
    else oWins += temp;
    temp = checkDiagonals(tttboard, 'o');
    if(temp > 1) return 'i';
    else oWins += temp;

    if(oWins > 0 && xWins > 2) return 'i';
    if(oWins == 0 && xWins == 0) return 't';
    if(xWins >= 1) return 'x';
    if(oWins >= 1) return 'o';

    return 'e';
}


int main(int argc, char* argv[]) {
    string board = "xxxxoooox";
    cout << "doing analysis on: " << board << " results in " << tttanalyzer(board) << '\n';
    return 0;
}
