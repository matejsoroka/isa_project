//
// Created by Matej Soroka on 30.10.19.
//

#ifndef ISA_PROJECT_DASHBOARD_H
#define ISA_PROJECT_DASHBOARD_H


#include "Board.h"
#include "Response.h"

class Dashboard {
    std::vector<Board *> boards; // vector of boards

public:

    /**
     * Create an empty board with name
     * @param response pointer to response object
     * @param board_name board name
     * @return int return code
     */
    int create_board(Response *response, std::string board_name);

    /**
     * Add post to board
     * @param response pointer to response object
     * @param board_name board name
     * @param message board post message
     * @return int return code
     */
    int add_to_board(Response *response, const std::string& board_name, std::string message);

    /**
     * Edit post from board in position selected by id
     * @param response pointer to response object
     * @param board_name board name
     * @param id position
     * @param message board post message
     * @return int return code
     */
    int edit_post(Response *response, const std::string& board_name, unsigned long id, std::string message);

    /**
     * Get boards list
     * @param response pointer to response object
     * @return int return code
     */
    int get_boards(Response *response);

    /**
     * Get board object by board name
     * @param board_name board name
     * @return Board pointer
     */
    Board* get_board(const std::string& board_name);

    /**
     * Get board
     * @param response pointer to response object
     * @param board_name board name
     * @return int return code
     */
    int get_board(Response *response, const std::string& board_name);

    /**
     * Delete board with board name
     * @param response pointer to response object
     * @param board_name board name
     * @return return code
     */
    int delete_board(Response *response, const std::string& board_name);

    /**
     * Check if board exists
     * @param board_name board name
     * @return return code
     */
    int board_exists(const std::string& board_name);

    /**
     * Get board index in vector of boards
     * @param board_name board name
     * @return index of board
     */
    int get_board_index(const std::string &board_name);

    /**
     * Delete post from board by index
     * @param response pointer to response object
     * @param board_name board name
     * @param id position
     * @return return code
     */
    int delete_post(Response *response, const std::string &board_name, unsigned long id);
};


#endif //ISA_PROJECT_DASHBOARD_H
