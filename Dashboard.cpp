//
// Created by matthew on 30.10.19.
//

#include "Dashboard.h"

#include <utility>
#include <sstream>

int Dashboard::create_board(Response *response, std::string board_name) {
    if (this->board_exists(board_name)) {
        response->code = 409;
        response->payload = "Board already exists";
        return 1;
    }
    this->boards.push_back( new Board(std::move(board_name)));
    response->code = 201;
    response->payload = "Board successfuly created";
    return 0;
}

int Dashboard::get_board(Response *response, const std::string& board_name) {
    Board* board = get_board(board_name);
    if (board) {
        if (board->posts.empty()) {
            response->code = 404;
            response->payload = "Board is empty";
            return 1;
        } else {
            response->code = 200;
            std::stringstream ss;
            ss << "[ " << board->board_name << " ]\n";
            int i = 1;
            for (const auto& post : board->posts) {
                ss << i++ << ". " << post->message << "\n";
            }
            response->payload = ss.str();
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
            ss << board->board_name << "\n";
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

int Dashboard::edit_post(Response *response, std::string board_name, int id, std::string message) {

}

int Dashboard::add_to_board(Response *response, const std::string& board_name, std::string message) {
    auto board = get_board(board_name);
    if (board) {
        Post* post = new Post(std::move(message));
        board->posts.push_back(post);
        response->code = 200;
        response->payload = "Post added";
        return 0;
    } else {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
}

int Dashboard::delete_post(Response *response, std::string board_name, int id) {

}

int Dashboard::delete_board(Response *response, const std::string& board_name) {
    int ix = this->get_board_index(board_name);
    if (ix != -1) {
        this->boards.erase(this->boards.begin() + ix);
        response->code = 200;
        response->payload = "Board successfuly deleted";
        return 0;
    } else {
        response->code = 404;
        response->payload = "Board does not exists";
        return 1;
    }
}

int Dashboard::board_exists(std::string board_name)
{
    return get_board(board_name) ? 1 : 0;
}

Board* Dashboard::get_board(const std::string& board_name) {
    for (auto board : this->boards)
        if (board->board_name == board_name)
            return board;
    return nullptr;
}

int Dashboard::get_board_index(const std::string& board_name) {
    int i = 0;
    for (auto board : this->boards) {
        if (board->board_name == board_name)
            return i;
        i++;
    }
    return -1;
}
