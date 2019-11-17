//
// Created by Matej Soroka on 30.10.19.
//

#include "Dashboard.h"

#include <utility>
#include <sstream>

/*
 * Methods are setting response code and message (payload) for client
 */

int Dashboard::create_board(Response *response, std::string board_name) {
    if (this->board_exists(board_name)) {                           // check if board exists
        response->code = 409;
        response->payload = "Board already exists";
        return 1;
    }
    this->boards.push_back( new Board(std::move(board_name)));   // insert board to vector of boards
    response->code = 201;
    response->payload = "Board successfully created";
    return 0;
}

int Dashboard::get_board(Response *response, const std::string& board_name) {
    Board* board = get_board(board_name);
    if (board) {                     // check if board exists
        if (board->posts.empty()) {  // if board is empty
            response->code = 200;
            response->payload = "Board is empty";
            return 0;
        } else {
            response->code = 200;
            std::stringstream ss;
            ss << "[ " << board->board_name << " ]\n"; // board name
            int i = 1;
            for (const auto& post : board->posts) {    // concat board's messages
                ss << i++ << ". " << post->message << "\n";
            }
            response->payload = ss.str();              // set messages as respond payload
            return 0;
        }
    } else {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
}

int Dashboard::get_boards(Response *response) {
    if (!this->boards.empty()) {
        std::stringstream ss;
        for (const auto& board : this->boards) {
            ss << board->board_name << std::endl;
        }
        response->code = 200;
        response->payload = ss.str();
        return 0;
    } else {
        response->code = 404;
        response->payload = "No board exists";
        return 1;
    }
}

int Dashboard::edit_post(Response *response, const std::string& board_name, unsigned long id, std::string message) {
    Board* board = this->get_board(board_name);
    if (!board) {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
    if (board->posts.size() >= id) {
        board->posts[id - 1]->message = std::move(message);  // index normalization
        response->code = 200;
        response->payload = "Post successfuly edited";
        return 0;
    } else {
        response->code = 404;
        response->payload = "Post does not exists";
        return 1;
    }
}

int Dashboard::add_to_board(Response *response, const std::string& board_name, std::string message) {
    auto board = get_board(board_name);
    if (message.length() == 0) {
        response->code = 400;
        response->payload = "Post cannot be empty";
        return 1;
    }
    if (board) {
        Post* post = new Post(std::move(message));
        board->posts.push_back(post); // adding new post to board
        response->code = 201;
        response->payload = "Post added";
        return 0;
    } else {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
}

int Dashboard::delete_post(Response *response, const std::string& board_name, unsigned long id) {
    Board* board = this->get_board(board_name);
    if (!board) {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
    if (board->posts.size() >= id) {
        board->posts.erase(board->posts.begin() + (id - 1));
        response->code = 200;
        response->payload = "Post successfully deleted";
        return 0;
    } else {
        response->code = 404;
        response->payload = "Post does not exists";
        return 1;
    }
}

int Dashboard::delete_board(Response *response, const std::string& board_name) {
    int ix = this->get_board_index(board_name);
    if (ix != -1) {
        this->boards.erase(this->boards.begin() + ix);
        response->code = 200;
        response->payload = "Board successfully deleted";
        return 0;
    } else {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
}

int Dashboard::board_exists(const std::string& board_name)
{
    return get_board(board_name) ? 1 : 0;
}

Board* Dashboard::get_board(const std::string& board_name) {
    for (auto board : this->boards)
        if (board->board_name == board_name)  // if board name eq to searched board name, return pointer to that board
            return board;
    return nullptr;
}

int Dashboard::get_board_index(const std::string& board_name) {
    int i = 0;
    for (auto board : this->boards) {
        if (board->board_name == board_name)  // if board name eq to searched board name, return its index
            return i;
        i++;
    }
    return -1;
}
