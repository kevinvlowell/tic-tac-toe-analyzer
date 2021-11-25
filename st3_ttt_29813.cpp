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
    if(xCount - oCount >= 2 || oCount - xCount >= 2 ) return true;
    else return false;
}

// Bad shape and bad chars
bool checkErrorCondition(string tttboard) {
    if(tttboard.length() != 9) return true;
    cout << "Passed length test\n";
    for(char c: tttboard) {
        if(!(c == 'x' | c == 'o' | c == '#')) return true;
    }
    cout << "Passed character test\n";
    return false;
}

// Row columns must be unique
int checkRows(string tttboard, char player) {
    cout << "checking rows of " << player << '\n';
    int winCount = 0;
    int index = 0;
    for(int i =0; i < 3; i++) {
        index = i*3;
        if(tttboard.at(index) == player && tttboard.at(index+1) == player && tttboard.at(index+2) == player) {
            winCount++;
        }
    }
    // If greater than 1 thats a rule violation
    cout << "win count: " << winCount << '\n';
    return winCount;
}

// Column wins must be unique
int checkColumns(string tttboard, char player) {
    cout << "checking columns of " << player << '\n';
    int winCount = 0;
    for(int i =0; i < 3; i++) {
        if(tttboard.at(i) == player && tttboard.at(i+3) == player && tttboard.at(i+3) == player) {
            winCount++;
        }
    }
    // If greater than 1 thats a rule violation
    cout << "win count: " << winCount << '\n';
    return winCount;
}

// Diagonal wins share middle square
int checkDiagonals(string tttboard, char player) {
    cout << "checking diagonals of " << player << '\n';
    int winCount =0;
    // top left diagonal
    if(tttboard.at(0) == player && tttboard.at(4) == player && tttboard.at(8) == player) {
        winCount++;
    }
    // top right diagonal
    if(tttboard.at(2) == player && tttboard.at(4) == player && tttboard.at(6) == player) {
        winCount++;
    }
    cout << "win count: " << winCount << '\n';
    return winCount;
}

char tttanalyzer(string tttboard) {
    // edge cases
    // check too many winners
    cout << "checking invalids and errors\n";
    if(checkInvalid(tttboard)) return 'i';
    if(checkErrorCondition(tttboard)) return 'e';

    int xWins = 0;
    int oWins = 0;
    int temp;

    cout << "Checking player 'x'\n";
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
    cout << "Checking player 'o'\n";
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

    cout << "final checks\n";
    if(oWins > 0 && xWins > 2) return 'i';
    if(oWins == 0 && xWins == 0) return 't';
    if(xWins >= 1) return 'x';
    if(oWins >= 1) return 'o';

    cout << "Something went wrong 'x'\n";
    return 'e';
}


/*int main(int argc, char* argv[]) {
    string board = "###xxxoo#";
    cout << "doing analysis on: " << board << '\n';
    char answer = tttanalyzer(board);
    cout << "result is " << answer << '\n';
    return 0;
}*/


// MAIN

int main() {
  int n;
  std::string board;
  Move m;
  std::vector<Move> moves;
  std::vector<std::string> boards;
  std::string asktype;

  while (std::cin >> asktype) {
    if (asktype == "v") {  // test tttresult vector
      moves.clear();
      std::cin >> n;
      for (int i = 0; i < n; i++) {
        std::cin >> m.r >> m.c >> m.player;
        moves.push_back(m);
      }
      std::cout << tttresult(moves) << "\n";
    } else if (asktype == "s") {  // test tttresult string
      std::cin >> board;
      std::cout << tttresult(board) << "\n";
    } else if (asktype == "a") {  // test get_all_boards
      boards = get_all_boards();
      for (auto b : boards) {
        std::cout << b << "\n";
      }
    } else if (asktype == "t") {  // test ttt_tally
      ttt_tally();
    } else {
      return 0;
    }
  }
  return 0;
}
