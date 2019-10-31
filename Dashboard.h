//
// Created by matthew on 30.10.19.
//

#ifndef ISA_PROJECT_DASHBOARD_H
#define ISA_PROJECT_DASHBOARD_H


#include "Board.h"
#include "Response.h"

class Dashboard {
    std::vector<Board *> boards;

public:
    int create_board(Response *response, std::string board_name);
    int add_to_board(Response *response, const std::string& board_name, std::string message);
    int edit_post(Response *response, std::string board_name, int id, std::string message);
    int get_boards(Response *response);
    Board* get_board(const std::string& board_name);
    int get_board(Response *response, const std::string& board_name);
    int delete_post(Response *response, std::string board_name, int id);
    int delete_board(Response *response, const std::string& board_name);
    int board_exists(std::string board_name);

    int get_board_index(const std::string &board_name);
};


#endif //ISA_PROJECT_DASHBOARD_H
