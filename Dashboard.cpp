//
// Created by matthew on 30.10.19.
//

#include "Dashboard.h"

#include <utility>

int Dashboard::create_board(std::string board_name) {
    this->boards.push_back( new Board(std::move(board_name)));
    return 0;
}

int Dashboard::get_board(std::string board_name) {
    Board *board = this->boards[0];
    int foo = 1;
    return foo;
}

int Dashboard::get_boards() {

}

int Dashboard::edit_post(std::string board_name, int id, std::string message) {

}

int Dashboard::add_to_board(std::string board_name, std::string message) {

}

int Dashboard::delete_post(std::string board_name, int id) {

}

int Dashboard::delete_board(std::string board_name) {

}

