//
// Created by Matej Soroka on 30.10.19.
//

#include "Board.h"

#include <utility>

/**
 * Initialize board with board name
 * @param board_name
 */
Board::Board(std::string board_name) {
    this->board_name = std::move(board_name);
}