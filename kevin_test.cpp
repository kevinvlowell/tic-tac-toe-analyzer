#include <iostream>
#include <vector>
#include <string>

using namespace std;

// helper function for get_all_boards. updates x's and returns index of col to increment
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


int main() {

    get_all_boards();

    return 0;
}