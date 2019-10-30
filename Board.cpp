//
// Created by matthew on 30.10.19.
//

#include "Board.h"

#include <utility>

Board::Board(std::string board_name) {
    this->board_name = std::move(board_name);
}