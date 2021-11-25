// Copyright 2021 Muhammad Fahad Farid fahadf@bu.edu
// Copyright 2021 Samir Farhat Dominguez safarhat@bu.edu
// Copyright 2021 Kevin Vogt-Lowell kjv@bu.edu

#include "movedef.h"
using std::string;
using std::vector;
using std::cout;
int continueFlag = 0;
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
    if(xCount + oCount != 9) continueFlag = 1;
    if(xCount - oCount >= 2 || oCount - xCount >= 2 ) return true;
    else return false;
}

// Bad shape and bad chars
bool checkErrorCondition(string tttboard) {
    if(tttboard.length() != 9) return true;
    //cout << "Passed length test\n";
    for(char c: tttboard) {
        if(!(c == 'x' | c == 'o' | c == '#')) return true;
    }
    //cout << "Passed character test\n";
    return false;
}

// Row columns must be unique
int checkRows(string tttboard, char player) {
    //cout << "checking rows of " << player << '\n';
    int winCount = 0;
    int index = 0;
    for(int i =0; i < 3; i++) {
        index = i*3;
        if(tttboard.at(index) == player && tttboard.at(index+1) == player && tttboard.at(index+2) == player) {
            winCount++;
        }
    }
    // If greater than 1 thats a rule violation
    //cout << "win count: " << winCount << '\n';
    return winCount;
}

// Column wins must be unique
int checkColumns(string tttboard, char player) {
    //cout << "checking columns of " << player << '\n';
    int winCount = 0;
    for(int i =0; i < 3; i++) {
        if(tttboard.at(i) == player && tttboard.at(i+3) == player && tttboard.at(i+6) == player) {
            winCount++;
        }
    }
    // If greater than 1 thats a rule violation
    //cout << "win count: " << winCount << '\n';
    return winCount;
}

// Diagonal wins share middle square
int checkDiagonals(string tttboard, char player) {
    //cout << "checking diagonals of " << player << '\n';
    int winCount =0;
    // top left diagonal
    if(tttboard.at(0) == player && tttboard.at(4) == player && tttboard.at(8) == player) {
        winCount++;
    }
    // top right diagonal
    if(tttboard.at(2) == player && tttboard.at(4) == player && tttboard.at(6) == player) {
        winCount++;
    }
    //cout << "win count: " << winCount << '\n';
    return winCount;
}

char tttanalyzer(string tttboard) {
    // edge cases
    // check too many winners
    //cout << "checking invalids and errors\n";
    if(checkInvalid(tttboard)) return 'i';
    if(checkErrorCondition(tttboard)) return 'e';

    int xWins = 0;
    int oWins = 0;
    int temp;

    //cout << "Checking player 'x'\n";
    //compile x wins
    temp = checkRows(tttboard, 'x');
    if(temp > 1) return 'i';
    else xWins += temp;
    temp = checkColumns(tttboard, 'x');
    if(temp > 1) return 'i';
    else xWins += temp;
    temp = checkDiagonals(tttboard, 'x');
    if(temp > 2) return 'i';
    else xWins += temp;
    //cout << "Checking player 'o'\n";
    //compile o  wins
    temp = checkRows(tttboard, 'o');
    if(temp > 1) return 'i';
    else oWins += temp;
    temp = checkColumns(tttboard, 'o');
    if(temp > 1) return 'i';
    else oWins += temp;
    temp = checkDiagonals(tttboard, 'o');
    if(temp > 2) return 'i';
    else oWins += temp;

    //cout << "final checks\n";
    if(oWins > 0 && xWins > 0) return 'i';
    if(oWins > 0 && xWins > 2) return 'i';
    if(oWins == 0 && xWins == 0 && continueFlag) return 'c';
    if(oWins == 0 && xWins == 0) return 't';
    if(xWins >= 1) return 'x';
    if(oWins >= 1) return 'o';

    //cout << "Something went wrong 'x'\n";
    return 'e';
}

char tttresult(vector<Move> board) {
    return 'h';
}

vector<string> get_all_boards() {
    return {"this is a place holder", "boo!"};
}

void ttt_tally() {
    return;
}

int main(int argc, char* argv[]) {
    int oCount = 0;
    int xCount = 0;
    int iCount = 0;
    int tCount = 0;
    int eCount = 0;
    int cCount = 0;
    vector<string> m = {"xx##xoxxo", "oooxx##x#", "xoxxoo#ox", "xxxo#oo#x", "#o##ox#xx", "x#xooox##", "o#xox#xox", "#oxxoxo#x", "o#o#xoxxx", "ooxxoxxo#", "xx##x#ooo", "ox#xoxoxx", "xooxxo#xo", "x#x##xooo", "xxxo#o###", "x#xoxoxo#", "xxxoo#x#o", "xxxo#x#oo", "ox##o##o#", "xox#o##ox", "xooo####x", "#xx##xooo", "#oxo#oxxx", "oxoxxx##o", "xo#x#ox##", "o#x#x#o##", "##xoxxxoo", "#xooo#xxx", "xoxoo#x#x", "##xoxoxxo", "#o#xxxoox", "xooxo#oxx", "#ox#oxoxx", "xxoxooo#x", "xxooxox#o", "oxoox##xx", "xo#ooxxox", "#ox#ox##x", "xoo#x###x", "xoox#xxo#", "oxxo##ox#", "xooxoxox#", "oo#x#oxxx", "####ox#o#", "oxo#oxxxo", "xxx##o#o#", "x#oxx#xoo", "x#x#xoxoo", "xoxoxo##x", "xxoooxo#x", "#o#oxoxxx", "xoxx#oxo#", "#oxox#xxo", "ox#ooxoxx", "xooxx##ox", "xxoxo#x#o", "#oxo###o#", "##oxo#oxx", "x##x#oxo#", "x#ox#oxox", "oxoxx#ox#", "o#x#xoxxo", "x#x#xooox", "x#o#x##ox", "##x#xxo#o", "###oxooox", "o##xoxx#o", "x#xxxoooo", "o#x##xo#x", "ox#xooxxo", "xooxxxxoo", "#xoxoooxx", "xooxx#x#o", "ooxxxoxxo", "o#xo#x##x", "#xxxxxxoo", "xxooxxoox", "#xxo#xoox", "oxxxxooox", "x#xoooxox", "xoxoooo##", "o#oxo#xxx", "oox#xox#x", "#xoxo#o#x", "oxo#x#oxx", "o#xx#xoox", "ox#ox##x#", "#oox#oxxx", "#x#ooox#x", "xo#ox#oxx", "#xoxx#xoo", "o#o#ooxxx", "x#oxoooxx", "x#o#x#o#x", "x#xxo#xoo", "xxoxxo#oo", "oxxxox#oo", "oxxxo#oxo", "#oxxx##oo", "oxxo#xo##", "#oxxxxo#o", "xoxxo#oox", "x#ooxox#x", "x#xoooxxo", "o#xoxo##x", "xxx#o###o", "xo##xooxx", "#xoxxx#oo", "ooo#x#x#x", "#xoxxoxoo", "xo#xox#o#", "o#xx#o#ox", "x###xxo#o", "xoxoxox##", "ooxxxoxox", "x#o#xxoox", "x##x##xoo", "x#ooxxo#x", "xxxox#o#o", "xo#oxx##o", "#xoxx#oxo", "xxoxoxxoo", "o##xo#xxx", "#xxoxoox#", "x#ooxo#xx", "ooo##x#xx", "xxoxoo#xo", "oox#xxx#o", "#xoxo#ox#", "oxo#o##xx", "#xxxxoooo", "oxo#xxox#", "xo##ox#ox", "oo#ooooox", "oox##x##x", "o#xxo##xo", "xoxooo#xx", "##o#oxoxx", "xxoxooox#", "xx###xooo", "x##o#oxxo", "oxoxxxoox", "xoxoxoxxo", "oxoxxxoxo", "ooox###xx", "xxxooxo##", "xxooxooxx", "oxxx#ox#o", "xoooxxxox", "#xoxoxoxo", "x#oox#xox", "#x#o#x#ox", "xxxo#o#xo", "o#xoxox#x", "ooxo#xx#x", "oox##oxxx", "#oxxxox#o", "#xo##oxxo", "#ox#xxxoo", "##o#o#xxx", "xoxox#xo#", "o#x#o#xxo", "o#oxxxx#o", "xo#oo#xxx", "ox#xo##xo", "x#o#oxox#", "o#xo#oxxx", "#xoxoxoox", "o#xoo#xxx", "xxoxoox##", "oxx#oo#oo", "#oxxxxoo#", "xoo#x#xox", "#x##xoox#", "o#o#oxxxx", "o#x##x#ox", "#o#xxoxox", "oxxox#x#o", "xo#ox#xox", "o##xooxxx", "xooxo#xx#", "xxooo#oxx", "#xxooo#x#", "oxooxxo#x", "##ooxoxxx", "o#ox#xxox", "xooox##xx", "o#xo#xox#", "xoxoxxoxo", "#xooxx#xo", "#ox##xo##", "o#x#x#x#o", "###oo#xxo", "xxxo##xoo", "xoxxx#ooo", "o#oox#xxx", "#ooxoxxox", "oxoxxx#o#", "x#oxoxxo#", "#ooxxx###", "oooxoxoo#", "x#xx#oxo#", "oo#x#ox#x", "#xxxoxoo#", "xxxxoo##o", "oxo#xx#xx", "o##xxxxoo", "#xxoooxxx", "o##xx#xxx", "#ox#oxxo#", "x#xoxo#ox", "ox##oxx#o", "ox#xoxxoo", "oo#ox#xxx", "xoooxx##x", "ox##xooxx", "#oxoo#xxx", "#xx#o#ooo", "##x##xoox", "#ooxxx#ox", "xxxoxooxo", "o#o#xxoxo", "o###o#xxx", "#o##o#xxx", "xxoxooxox", "oxo#o#x##", "#o#xooxxx", "xo#xxx#oo", "##oxxxxoo", "xxox#o###", "##oooxxxx", "##xoxoxox", "ooox#xxxo", "oooxox#xx", "##oxxxo##", "oxx#xoox#", "#xx#xoxoo", "xoxoox##x", "oo#o#xxxx", "o#oo#xxxx", "xox#x#oox", "##xxx#ooo", "xox#xo#ox", "xo#xxo###", "xx#xooxo#", "o#xxox##o", "o#oxooo#o", "x#o#ox#ox", "oxxo#xoxo", "#xo#oxo#x", "##xx#xooo", "x#oxoxoxo", "xxx###o#o", "x#xooooxx", "#oxox#x##", "#o#x#o#xx", "xoxo#xo#x", "ooxx#xo#x", "xxooxxoxo", "o#xxxxoo#", "#oxxo#xo#", "#oxxo#x#o", "oox#x#xxo", "oxoxoxxox", "x#o#xoxox", "xxo####o#", "#xo#xo#x#", "##oo##xxx", "xo#xx#xx#", "ooxxxx#o#", "o#oxxxxo#", "xoo#xox#x", "x##oxx#o#", "#xoo#ooo#", "xxoox#o#x", "oo#xxxox#", "xo#xxoxo#", "oo#xxoxxx", "xo##oxxxo", "ooxxxxoox", "#xo#x##xo", "xx##xooxo", "##xo#x#ox", "oooxx#oxx", "xxxo##oox", "oxxoxoo#x", "#ox##x#ox", "oxoxxooxx", "##oxxx##o", "x#ox##x#o", "ox#o#xo#x", "oxxo#ooxx", "#xx#x#ooo", "oxxox#xo#", "o#xxoxxoo", "xxoo##oxx", "xo#o#oxxx", "xo#xoxx#o", "o##ooxxxx", "oxxxo#xoo", "x#xx##ooo", "xoxxo#x#o", "xo#ox###x", "xxx#oox#o", "ooxo##xxx", "x#oxo#o#x", "o##oxoxxx", "xxo#xo##o", "#o##oxxox", "oooxoxxx#", "oxxxoxoox", "#xo#oxox#", "##oxoxox#", "xo#oxo#xx", "x#oxxx#oo", "ooox#x##x", "#oxxxoxox", "#xx#oxoox", "oxx#oxxoo", "xxx#oo##x", "##xox#x#o", "#oo###xxx", "xox#xoxo#", "#x#x#xooo", "xxxxo#o#o", "xo#xo#x##", "xx#xoox#x", "oxoxoxox#", "xoxo#x#o#", "###xooxox", "#x#oxoxox", "xxx#o#oox", "oo#xoxxxo", "#oxoox#xx", "xo#x#oxox", "xxo#o#ox#", "oxoo##xxx", "ox##ox#x#", "xoox#ox#x", "ooo#xx#x#", "#ox#xoxxo", "oxoxox#xo", "xxo#xxooo", "o#x#oxx#o", "ooxox#x#x", "xxxxo#oo#", "##x#x#xoo", "xoxoxooxx", "ox#oxoxx#", "##xoooxo#", "oox#xoxx#", "xxooxoxox", "ooo#x#xx#", "#xoxxxo#o", "##xooxxox", "#oxooxx#x", "ooxxxox##", "#ooxxxxo#", "oo#xxx#xo", "oo#xo#xxx", "xxxxooo##", "oxx##xoo#", "ooxoxxx##", "xo#oxox#x", "oxx#xox#o", "xooxxxoox", "x#o#oxo#x", "o#o###xxx", "#xoxxo##o", "ooo#xxxxo", "#ox#x#x#o", "#xxoxo#ox", "x#o#xxxoo", "xo##xoxox", "oxx#xoxo#", "oox#o#xxx", "ooxxxooxx", "xxxox#oo#", "#ooxxxox#", "ooxoxxxxo", "o#xxooxxo", "x#xoxoo#x", "x#x#oxoox", "x##xo#xo#", "#oo#xoooo", "xxxo####o", "o#ox##x#o", "#oxoxox#x", "#xoooxxox", "#xxooox##", "#xo#xooxx", "xo###ooxx", "o#oxxx#ox", "o##o##xxx", "oxoxo#xxo", "#xxxoxooo", "##xoxxoox", "oxxoox##x", "oxoxxox#o", "##oo#xxox", "oxx#ox##o", "x#xox#oox", "x#oxxoxo#", "o#oxxxox#", "xxxoxoxoo", "x#o#xo#xo", "xxx#xooo#", "#oxxxoxo#", "xxx#oxo#o", "#xoooxoxx", "x#xoxxooo", "oox#ox#xx", "xxo##ox#o", "ox#xxxo#o", "oxooxxxxo", "oxox#oxxo", "xxo#o#o#x", "o#xxxxo##", "xxxoxo#o#", "xxo#x#oox", "##xxoxoox", "#ox#x#xo#", "x#xx#oxoo", "ox##ooxxx", "o#x#ooxxx", "xoxoooxx#", "##o#x#x##", "xx#oxo#xo", "x#oxo#xxo", "x##xo#x#o", "ox#oxxoox", "#xxoooxox", "##oxoxo#x", "oxxxoxo#o", "xxoxoxoo#", "xxxoo##ox", "ox#ooxxxo", "#ooxxxx#o", "##x#oooxx", "##oxxxoxo", "oxx##xoox", "#x#xx#xoo", "o#oox####", "xxxooxoxo", "xxx###oo#", "#oxxoxxoo", "ooxxo#xxo", "oo#x##oo#", "##ox#oxxo", "oxx#x#oxo", "o#xxoxo#x", "ooo#xx##x", "xox#ooxox", "xxox#ooxo", "xo##xxoxo", "xooo##xxx", "xooxxxoxo", "o##xo#xxo", "xxoxo#o##", "xxxo#xo#o", "o#x#oxxox", "###xxx#oo", "ox##xoxxo", "o###oxxxo", "#oxoxxo#x", "xxx#o#oxo", "oo####xxx", "ooox##xx#", "oxxoo#xxo", "####ooxxx", "##xooxoxx", "##o#xoox#", "xxx#oo#ox", "xxox#xooo", "xxoooxxox", "#xoox#oxx", "xo#oxx#ox", "xox#o#xo#", "xxxoxo##o", "oxoxxxxoo", "#xo#ooxxx", "xo##x##ox", "xoox##xox", "xooxoxxxo", "###o#oxxx", "o##o#xoxx", "oxxoxxoo#", "x#xoox#ox", "#oxx#xoox", "o#xoxo###", "x#xooxo#x", "xo#x##xo#", "x#o#o#oxx", "xxoxo#oox", "xoxoxoxox", "xx#ooo#x#", "xxo###xxo", "##ox###x#", "xx#oxo#ox", "oxxoxoxox", "#xxoxxxox", "ooxxxxxoo", "x#oo#oxxx", "xxo#xoox#", "xoox#oxx#", "oxxxxooxo", "ox#xxoox#", "#o#xxxo##", "#xxooooxx", "o#xo#xxox", "#oxxooxox", "xxoooxox#", "ooox#xxox", "#o#o##xxx", "ooxox#oxx", "x#ox#xxoo", "#xxooxo#x", "o#xoxxxo#", "xo##oxxo#", "xxxx#oo#o", "xxoooox#x", "xxxo#o#ox", "##x#xxooo", "xo#o#oooo", "o#xxxoxo#", "xooxxx#o#", "#oxoxoxx#", "ox##xxoxo", "o#oxxx###", "xxx##ooxo", "xo#x##x#o", "oo#oxxoxx", "ooxxoxx#o", "#xxoox#ox", "x#oooxoxx", "#xxxooxo#", "oxxxoox#o", "#xoox#xxo", "xo##ooxxx", "oooxxoxx#", "#ox#ooxxx", "xo#xo###x", "ox#xxxoo#", "#ooxxx#xo", "ooxoxxox#", "xoxx##xoo", "#oxoxxx#o", "oo#xxx#ox", "#xxo#ox#x", "x#xooo#x#", "xo#xxo#ox", "ox#oxxo##", "o#ox#oxxx", "oxx#o#x#o", "#xoox##x#", "ox#oo#xxx", "oxo#xoxx#", "#x#ox##xo", "###xxxoo#", "#o#xxxoxo", "xx#xoxooo", "xxx#xo#oo", "x##xxooox", "ox#xx#oxo", "#ox##xxoo", "oooxx###x", "o#xx##x#o", "o#xoxooxx", "oxooxoxxx", "xoxxoooxx", "o##ox#oxx", "o#xoxxo##", "o#oxoxxxo", "xo#xoxoox", "##x#oxo#x", "#xo#xxoxo", "o####oxxx", "xx#oooxox", "#x#oxo#x#", "xxxoo##xo", "x#oxx#oox", "oxxo##o#x", "xx#oooxxo", "o#xxo#x#o", "xxoo#oxxo", "xxxoxxx#x", "#x#xxooxo", "oxooox#oo", "xxxo##o##", "#ooo#xxxx", "#xxoxo#xo", "xxxoo####", "xxx#oo#xo", "#xo##xx#o", "oxoxo#oxx", "x#ox##xo#", "xx#x#oxoo", "o#x#xoxox", "x##xooxxo", "o#xooxxxo", "##o#xx#o#", "x#x#x#ooo", "##ooox###", "###xxxo#o", "xx#xxo##o", "x##x#ooxx", "oxxxo###o", "oxxox#oox", "xxox##xo#", "#xxox#xoo", "xxo#ooxxo", "#xo#xox#o", "oox#oxx#x", "xoxxxooxo", "xx##xooox", "o##xxxoxo", "#x##xo#xo", "xo#xx#xoo", "x#oxxo##o", "oxxx#o#ox", "o#xoxxoxo", "x##x#xooo", "o#ox###x#", "o#x#x#xo#", "xoxox#o#x", "oooo#ooxx", "o###o##o#", "xoxoxxxoo", "ox#ox####", "xoo##oxxx", "x#oxoox#x", "o#xoxxxoo", "xxoox#ox#", "#oxoxxxo#", "#o##oxo##", "#o#ooxxxx", "#xoo#xox#", "xo#oxxo#x", "oxo#o#xxx", "xxx#ooxo#", "#ooxxxo#x", "oox#xx#ox", "#xxoxox##", "o#oxoooxo", "xoxooxxxo", "xx#oxoooo", "x#oxoxo##", "xxx##oxoo", "x#xoxox#o", "o##oxxo#x", "xooox#x#x", "ox##o#xxo", "xxxooxxoo", "#o###oo#o", "xxxxoo#o#", "xxx#o#xoo", "xxxooxoox", "ooxxxxo##", "oxxooxox#", "oxxooo#xx", "##xoox##x", "o#xxoxoxo", "xx#xxoooo", "xooxxooxx", "xox#oxo#x", "x###x#oox", "xx#ooox##", "x#oox###x", "ooxxooxxx", "oox#oxxxo", "xo#xx#oox", "x#ooxox##", "x#oxxoo#x", "o#xxxox#o", "oxxoxxo#o", "oxo#o#o##", "ooo#xxxox", "x##ooox#x", "oxxxooxox", "#ox##xo#x", "oxo#x##x#", "#x#ooo#xx", "xooxoxo#x", "xxx#oo###", "###xoxox#", "o#xxox#ox", "oxxox#o##", "xx#oxxooo", "xooxxx##o", "xxo#oooxx", "oxo#xx#xo", "xo##oo#xo", "oox##xxox", "xxoxo#oxo", "oox##xx#o", "oox##xox#", "ox#oxx#xo", "#oooo#ox#", "oxoo#xoxx", "##xo#xo#x", "xoxoxxoox", "#oxoxxxxo", "xoxox#o#o", "o##x###x#", "ox#o##oxx", "o#oxx#xxo", "o#xox#x##", "xxox##xoo", "xxxoo#xo#", "xoxxoxoxo", "x#oox#oxx", "oxx#o##xo", "#xxoxoxo#", "xox#ox#o#", "ox#xoxoxo", "oxo#x#xxo", "ooxo###o#", "ooxoxoxxx", "xo##xxoox", "x##xoxxoo", "xxxox##oo", "oxxxooo#x", "xox##ox##", "ooo#xxoxx", "oxoxoxo#x", "xo##xo#xo", "#oxxxxo#x", "o#xoxx#ox", "xoxooxoxx", "oox#x#xox", "xxxxooxoo", "oooxx#x##", "xxoxxoo#o", "#oxoo#oo#", "x###xo#ox", "ooooxx#xx", "#xoxxxoo#", "xx#ox#oox", "xooxxxo##", "o##xxx##o", "o##xxxoox", "#xxoxxooo", "ooooxxxx#", "xxox#oxo#", "#o#xxx##o", "o##o##xx#", "xxx#xoo#o", "oo#xoxxox", "xoo#x#oxx", "xxxo#oox#", "#oxo#xoxx", "x####oo#x", "#ooox#xxx", "ooox#ox##", "xxxxoooxo", "oo##x#x#x", "oxoox#xx#", "x#ooo#xxx", "#oo#oxxxx", "xo##oxo#x", "#xxooo##x", "xo#xxxo#o", "#oxox#xox", "o#xox#o#x", "xooxxxoxx", "oxx#xo#xo", "xoo#oxxox", "x#oxxooxo", "ox#ox#xxo", "#ox#o#xox", "x#xox#xoo", "o#xo##oxx", "ooox#xoxx", "x#o##oxxo", "#xx#xooxo", "xxx##o##o", "xxx##oo##", "##xoooxx#", "xo#xoox#x", "xoxoo#xox", "###oo#xxx", "oxoxxo#x#", "x##oxooxx", "#x#ox#ox#", "xxoooxxxo", "xooxox#ox", "ooooxxx#x", "o#xoox#xx", "xooxooxxx", "xoxxxooox", "xxooxo##x", "##xxxoxoo", "ox#ox#o#x", "#xoo#oxxx", "####o#xx#", "xox#xox#o", "xooxx#xo#", "ooxxoxoxx", "oxxooox#x", "#x#oxxoxo", "xxx#ooox#", "xoo#o#xxx", "oo#xox#ox", "x##ox#o#x", "oxxoxoxxo", "xxooox#x#", "oxx#ooxxo", "x#o###ox#", "xxox#o##o", "oooxxxxox", "oxx#x#xoo", "#xo#x#ox#", "#x#xx#ooo", "oxo#xx###", "xoxox#x#o", "oxxo#xxo#", "o##xox#xo", "xooxxox##", "#x#oxooxx", "#o#xo#xox", "xx###xx#x", "oxxoxxxoo", "xo#xxoo#x", "###xoooox", "xoooxxoxx", "x#oo#o#ox", "xxxo#ox#o", "xxoooo#xx", "xo#oo##ox", "o#oxxoxxo", "#xxx##ooo", "o#oxoxoxx", "#ooxxoxxo", "xxxx#o#oo", "x#ooxoxxo", "#oxxx#xoo", "oxxox##xo", "#xox#o#xo", "xooooxxxx", "xoo#xx#ox", "ooxox#xx#", "ooxoxxxox", "xxo#xoo#x", "#x##xxooo", "#xoxoxo##", "o#xox#xxo", "oooxxox#x", "xxooooxx#", "oox#xxxo#", "oxox#xo##", "xxoxoxo#o", "x#o#xooxx", "o#x#ox#xo", "xxoxx#ooo", "ox#xox##o", "o##xxx#o#", "xoox#xx#o", "xoooxxxxo", "#xxoxox#o", "xxxoxooox", "oo#xxxx#o", "xo#oxoxxo", "ooxoxx##x", "xooxxoxox", "xoxox##ox", "x###o#xo#", "o#xoxxx#o", "###o###oo", "#x#oxoxxo", "##oxxxoox", "o#oxxx#xo", "xx#x#xx##", "ox#oxo#xx", "xo#oxxxo#", "x#ox#ox##", "o#xxx#xoo", "oxxxx#ooo", "ox#o#xox#", "xox#x#xoo", "##x#xoxo#", "xoo#xxo#x", "xx#x##ooo", "#ox#xox##", "oxooxx#x#", "oxx#ox#ox", "#x##x#oxo", "o#ooxxoxx", "oo##xoxxx", "xxx####oo", "x#xxoxooo", "oox#xxo#x", "#oxo#xxox", "#oxo#x##x", "xx#oxoox#", "#o#xxxxoo", "#xo#xx##x", "oox##xoxx", "x##xoox##", "ooo#xxx##", "x##o##o#x", "xox#oxxoo", "x##oxoxox", "xoxxooxxo", "x#oxxxoo#", "x##x#ox#o", "ooxxx#xo#", "#x#oxxxoo", "xoxx#ox#o", "o#x#oxxo#", "ooo#x##xx", "oxooxxxox", "x#o###oox", "oxoooxxxx", "xo#xooxx#", "oxo#xo#xx", "ox##ox#xo", "xx#xo#xoo", "xooxx#o#x", "x#o#xox#o", "ooox##x#x", "x#oxoxx#o", "#x#x##o##", "xxxo###o#", "#xox#ox#o", "xo##x#o#x", "xo#xo#xxo", "xxxoxoo##", "xoo####x#", "#o#xxx#o#", "##xooo#xx", "##oxxo#xo", "xxo#oxo##", "x#xxoox#o", "xxo#xoxoo", "x#oxo#x##", "ox#o#oxxx", "#xooxo#xx", "###o#####", "xxxoox##o", "xoxxoxoo#", "xo#xxox#o", "x##oooxx#", "o##oxooox", "xxxoox#o#", "x##ox##ox", "x#oxooxx#", "oxoxx##xo", "oo####x#o", "x#xooo##x", "xox#xxooo", "##x#ox#ox", "#ox#xoxox", "x#oxoxoox", "x##ooo#xx", "x#xo##o##", "oo##oxxxx", "xxxxoooox", "xoox##xxo", "oxoxoxx#o", "xoxxo##o#", "ooxx#x#ox", "oooxxo#xx", "xxxxo##oo", "xx#oxoo#x", "#x#x##xoo", "oooxx#xox", "#xooxxox#", "#xoxooxxo", "##oxxx#o#", "oxxx#xooo", "xxxx#oxo#", "x##xoxoo#", "x#oxo#xox", "xxooxo#x#", "oooxx#xxo", "oxxoox#xo", "oxxo#x#ox", "x##oxxoox", "ooxooxxxx", "o#xox#ox#", "oo#xxxo#x", "o#xoxoxx#", "#x#oox#x#", "xoxxoox##", "#oxxo##ox", "xoo#xo#xx", "o#oxxxo#x", "#oox#oxoo", "xox#xoo#x", "o#oo####x", "oxx#xxooo", "xxx#o##o#", "xoo#oo#o#", "oxo#oxoxx", "xoxxox#oo", "xxo#oxoxo", "x#xxooxo#", "#o###oxxx", "oxoxxoxox", "oxxxoo#xo", "o##oxxox#", "xxo#oxoox", "##x#xox#o", "xxoxxooox", "#o#xox#ox", "##o##oxxx", "#o##oooox", "xxooxxxoo", "xoxxxo#oo", "x#oxo#ox#", "xoxxxoxoo", "ooox#x#x#", "xxx#ox#oo", "xxoxo#xo#", "xxoxxoxox", "x###xxooo", "#xoxxoox#", "ooxxox##x", "##xox#xo#", "x#xo#xoox", "ooo##xx#x", "xo##xo##x", "o#xxxxo#o", "#ooxoxoxx", "#oxxxx#oo", "oox#x#x##", "##oxooxxx", "ox##xo#x#", "##o#xoxxo", "x##xooxox", "xoo#ooxx#", "o#x#xox##", "ooxo#xxx#", "xxx#o#o##", "#oooooooo", "ox#xxo#xo", "xoxo#x#ox", "xooxo#x#x", "o#x#oxoxx", "x#xoox###", "oxx#oxo#x", "ooo##xxx#", "oxxoxox##", "xoxx#xooo", "xxo##o#xo", "ox#x#oooo", "xooxxo##x", "x##oxo##x", "xxxo##oxo", "oxoxxxo##", "x#o#ooxxx", "oox#xoooo", "##xx#o#xo", "xoooxoxxx", "#oxxox#o#", "o#oxox##x", "xxxo#oxo#", "x#oxxo#ox", "xo#x#oxxo", "x##xx#ooo", "x#o#xo##x", "xo#xo##ox", "xo#x#xxoo", "oxo##oxxx", "oooooox#x", "o#oxx#ox#", "oo#o#xx#o", "oo#x#x###", "oxoxooxxx", "o#x#ox##x", "xoxooxxo#", "oo#xxx###", "xxoox##xo", "#x##xoo#x", "xoo#xoxxo", "xoo#oxoxx", "o#ooxxxxo", "ooox#xx##", "#xo#o#oxx", "oxxooxxox", "ox#xox#oo", "xxxoo#o#x", "#oxoxxox#", "ox#xo#x#o", "#xxxooxx#", "ooxx#x##x", "#oo#xoxxx", "xoox##x##", "ooxxo#xox", "xoo###oxo", "xxo#xo#ox", "xxx#oxoo#", "#oxoxx#ox", "x#ox#o#xo", "#xooxoxx#", "x###xoo#x", "#ooxo#xxx", "x#ooxxoo#", "oxxoxo#x#", "x#ooxx#ox", "o#xxxx#oo", "ox#xxx#oo", "xox##xoox", "xo##o#xox", "oxoooo##x", "xxxx#ooo#", "o#o##oxox", "ooxxox#xo", "xxxo#xoo#", "#ox#xxoox", "##xooox#x", "xxoox##ox", "o#x#xxxoo", "xxo#x#oxo", "ooxxxxoxo", "o#xooxx#x", "xooxoxx##", "xxx##ooox", "#x#oooxx#", "oxxoooxx#", "oxxooxx#o", "xx#ooooxx", "x##xoxo#x", "x##oooox#", "xo#xxxoo#", "#xxox#oxo", "oxxoo#oxx", "##oxxox#o", "oox##oxx#", "xx#ooo##x", "xoxooox#x", "#xxxooo##", "##xoxox##", "oxxxoooxx", "ox##x##xo", "oo#xxxxo#", "o#xx##oox", "oxxxxoxoo", "x#oxxxo#o", "xxxoo#ox#", "xx#xoox#o", "#xo##o##x", "ooxxxx##o", "xox#ox###", "ooxxx##xo", "ox##x#ox#", "xxx#ooo#x", "ooxxx#x#o", "x##xxoxoo", "ooxo#x#xx", "#xxoooxxo", "xx#ox#oxo", "oxx#oxoxo", "#o#xoxxo#", "#o###xx#o", "o##xxxo##", "oooxoxx#x", "o#x#xxoox"};
    for(string board : m) {
        cout << "doing analysis on: " << board << '\n';
        char answer = tttanalyzer(board);
        cout << "result is " << answer << '\n';
        if(answer == 'o') oCount++;
        if(answer == 'x') xCount++;
        if(answer == 't') tCount++;
        if(answer == 'c') cCount++;
        if(answer == 'e') eCount++;
        if(answer == 'i') iCount++;
    }
    cout << oCount << " " << xCount << " " << tCount << " " << cCount << " " << eCount << " " << iCount;
    string board = "xoxxoo#ox";
    char answer = tttanalyzer(board);
    //cout << "result is " << answer << '\n';
    return 0;
}

