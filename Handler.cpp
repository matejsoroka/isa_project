//
// Created by matthew on 28.10.19.
//

#include <regex>
#include "Handler.h"

Handler::Handler(Request *request, Response *response, Dashboard *dashboard) {
    this->request = request;
    this->response = response;
    this->dashboard = dashboard;
    handle_request();
}

int Handler::get_requests()
{
    std::regex r("\\/(boards)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        return this->dashboard->get_boards();
    }
    r.assign("\\/(boards)*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = "foo";
        return this->dashboard->get_board(board_name);
    }
}

int Handler::post_requests()
{
    std::regex r("\\/(boards)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = "foo";
        return this->dashboard->create_board(board_name);
    }
    r.assign("\\/(board)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = "foo";
        std::string message = "message";
        return this->dashboard->add_to_board(board_name, message);
    }
}

int Handler::put_requests()
{
    std::regex r(R"(\/(board)\/([a-zA-Z0-9]*)\/([0-9])*)");
    if (regex_match(this->request->url, r)) {
        int id = 1;
        std::string board_name = "foo";
        std::string message = "this is edited message";
        return this->dashboard->edit_post(board_name, id, message);
    } else {
        return 2;
    }
}

int Handler::delete_requests()
{
    std::regex r("\\/(boards)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = "foo";
        return this->dashboard->delete_board(board_name);
    }
    r.assign("\\/(boards)*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = "foo";
        int id = 1;
        return this->dashboard->delete_post(board_name, id);
    }
    return 2;
}

int Handler::handle_request() {

    if (this->request->metod == "GET") {
        return this->get_requests();
    } else if (this->request->metod == "POST") {
        return this->post_requests();
    } else if ((this->request->metod == "PUT")) {
        return this->put_requests();
    } else if (this->request->metod == "DELETE") {
        return this->delete_requests();
    } else {
        return 1;
    }
}

