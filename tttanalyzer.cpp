// Copyright 2021 Muhammad Fahad Farid fahadf@bu.edu
// Copyright 2021 Samir Farhat Dominguez safarhat@bu.edu
// Copyright 2021 Kevin Vogt-Lowell kjv@bu.edu
#include "movedef.h"
using std::string;
using std::vector;
using std::cout;

// Rule violations
bool checkInvalid(string tttboard) {
  int xCount = 0;
  int oCount = 0;
  for (char c : tttboard) {
    if (c == 'x') xCount++;
    if (c == 'o') oCount++;
  }
  if (xCount - oCount >= 2 || oCount  > xCount) {
    return true;
  } else {
    return false;
  }
}

// Bad shape and bad chars
bool checkErrorCondition(string tttboard) {
  if (tttboard.length() != 9) return true;
  for (char c : tttboard) {
    if (!(c == 'x' | c == 'o' | c == '#')) return true;
  }
  return false;
}

// Row columns must be unique
int checkRows(string tttboard, char player) {
  int winCount = 0;
  int index = 0;
  for (int i = 0; i < 3; i++) {
    index = i * 3;
    if (tttboard.at(index) == player && tttboard.at(index + 1) == player
        && tttboard.at(index + 2) == player) {
      winCount++;
    }
  }
  return winCount;
}

// Column wins must be unique
int checkColumns(string tttboard, char player) {
  int winCount = 0;
  for (int i = 0; i < 3; i++) {
    if (tttboard.at(i) == player && tttboard.at(i + 3)
        == player && tttboard.at(i + 6) == player) {
      winCount++;
    }
  }
  // If greater than 1 thats a rule violation
  return winCount;
}

// Diagonal wins share middle square
int checkDiagonals(string tttboard, char player) {
  int winCount = 0;
  // top left diagonal
  if (tttboard.at(0) == player && tttboard.at(4) == player
      && tttboard.at(8) == player) {
    winCount++;
  }
  // top right diagonal
  if (tttboard.at(2) == player && tttboard.at(4) == player
      && tttboard.at(6) == player) {
    winCount++;
  }
  return winCount;
}

char tttresult(string tttboard) {
  // edge cases
  if (checkErrorCondition(tttboard)) return 'e';
  if (checkInvalid(tttboard)) return 'i';

  int xWins = 0;
  int oWins = 0;
  int temp;

  // compile x wins
  temp = checkRows(tttboard, 'x');
  if (temp > 1) {
    return 'i';
  } else {
    xWins += temp;
  }
  temp = checkColumns(tttboard, 'x');
  if (temp > 1) {
    return 'i';
  } else {
    xWins += temp;
  }
  temp = checkDiagonals(tttboard, 'x');
  if (temp > 2) {
    return 'i';
  } else {
    xWins += temp;
  }

  // compile o  wins
  temp = checkRows(tttboard, 'o');
  if (temp > 1) {
    return 'i';
  } else {
    oWins += temp;
  }
  temp = checkColumns(tttboard, 'o');
  if (temp > 1) {
    return 'i';
  } else {
    oWins += temp;
  }
  temp = checkDiagonals(tttboard, 'o');
  if (temp > 2) {
    return 'i';
  } else {
    oWins += temp;
  }

  // check ordering
  int xCount = 0;
  int oCount = 0;
  for (char c : tttboard) {
    if (c == 'x') xCount++;
    if (c == 'o') oCount++;
  }

  // check results of analysis
  if (oWins > 0 && xWins > 0) return 'i';
  if (oWins > 0 && xWins > 2) return 'i';
  if (oWins == 0 && xWins == 0 && xCount + oCount != 9) return 'c';
  if (oWins == 0 && xWins == 0) return 't';
  if (xWins >= 1 && xCount > oCount) return 'x';
  if (oWins >= 1 && xCount == oCount ) return 'o';

  // nothing found, must have been i
  return 'i';
}

char tttresult(vector<Move> board) {
  return 'h';
}

// helper function for get_all_boards
// updates x's and returns col index to increment next
int column_incrementer(int current_ind, string& board) {
    if (board.at(current_ind) != 'x') {
        return current_ind;
    } else {
        // convert x's to #
        board.at(current_ind) = '#';
        return column_incrementer(--current_ind, board);
    }
}


vector<string> get_all_boards() {

  vector<string> all_boards;
  string board("#########");

  all_boards.push_back(board);

  // generate all boards starting from empty board

  int change_index;
  int board_size = board.length();

  while (board.compare("xxxxxxxxx") != 0) {

      change_index = column_incrementer(board_size-1, board);

    // handle changes for #'s and o's
      if (board.at(change_index) == '#') {
          board.at(change_index) = 'o';
      } else if (board.at(change_index) == 'o') {
          board.at(change_index) = 'x';
      }
      all_boards.push_back(board);
  }

  return (all_boards);
}

void ttt_tally() {
  
  vector<string> all_boards = get_all_boards();
  int x_tally = 0, o_tally = 0, t_tally = 0, i_tally = 0, c_tally = 0;
  char result;

  for (int i = 0; i < all_boards.size(); i++) {
    result = tttresult(all_boards.at(i));

    switch (result) {
      case 'x':
        x_tally++;
        break;
      case 'o':
        o_tally++;
        break;
      case 't':
        t_tally++;
        break;
      case 'i':
        i_tally++;
        break;
      case 'c':
        c_tally++;
        break;
    }
  }

    cout << "x " << x_tally << "\n";
    cout << "o " << o_tally << "\n";
    cout << "t " << t_tally << "\n";
    cout << "i " << i_tally << "\n";
    cout << "c " << c_tally << "\n";
}

// MAIN
int main() {
  return 0;
}
