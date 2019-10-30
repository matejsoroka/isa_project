//
// Created by matthew on 30.10.19.
//

#ifndef ISA_PROJECT_DASHBOARD_H
#define ISA_PROJECT_DASHBOARD_H


#include "Board.h"

class Dashboard {
    std::vector<Board *> boards;

public:
    int create_board(std::string board_name);
    int add_to_board(std::string board_name, std::string message);
    int edit_post(std::string board_name, int id, std::string message);
    int get_boards();
    int get_board(std::string board_name);
    int delete_post(std::string board_name, int id);
    int delete_board(std::string board_name);
};


#endif //ISA_PROJECT_DASHBOARD_H
