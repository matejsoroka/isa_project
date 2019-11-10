//
// Created by Matej Soroka on 28.10.19.
//

#include <regex>
#include "Handler.h"

Handler::Handler(Request *request, Response *response, Dashboard *dashboard) {
    this->request = request;
    this->response = response;
    this->dashboard = dashboard;
    handle_request();
    this->response->raw = this->response->generate_response();
}

int Handler::get_requests()
{
    std::regex r("\\/(boards)");
    if (regex_match(this->request->url, r)) {
        return this->dashboard->get_boards(this->response);
    }
    r.assign("\\/(board)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        return this->dashboard->get_board(this->response,
                this->request->url.substr(7, this->request->url.find("\\/")));
    }
    this->response->code = 404;
    this->response->payload = "Unknown GET request";
    return 404;
}

int Handler::post_requests()
{
    std::regex r("\\/(boards)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        return this->dashboard->create_board(this->response,
                this->request->url.substr(8, this->request->url.find("\\/")));
    }
    r.assign("\\/(board)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = this->request->url.substr(7, this->request->url.find("\\/"));
        return this->dashboard->add_to_board(this->response, board_name, this->request->payload);
    }
    this->response->code = 404;
    this->response->payload = "Unknown POST request";
    return 404;
}

int Handler::put_requests()
{
    std::regex r(R"(\/(board)\/([a-zA-Z0-9]*)\/([0-9])*)");
    if (regex_match(this->request->url, r)) {
        std::string board_name = this->request->url.substr(7, this->request->url.find("\\/"));
        int ix = board_name.find('/');
        unsigned long id = stoi(board_name.substr(ix + 1, board_name.find("\\/")));
        board_name = board_name.substr(0, ix);
        return this->dashboard->edit_post(this->response, board_name, id, this->request->payload);
    } else {
        this->response->code = 404;
        this->response->payload = "Unknown PUT request";
        return 404;
    }
}

int Handler::delete_requests()
{
    std::regex r("\\/(boards)\\/([a-zA-Z0-9]*)");
    if (regex_match(this->request->url, r)) {
        return this->dashboard->delete_board(this->response,
                this->request->url.substr(8, this->request->url.find("\\/")));
    }
    r.assign(R"((\/(board)\/([a-zA-Z0-9]*)\/([0-9])*))");
    if (regex_match(this->request->url, r)) {
        std::string board_name = this->request->url.substr(7, this->request->url.find("\\/"));
        int ix = board_name.find('/');
        unsigned long id = stoi(board_name.substr(ix + 1, board_name.find("\\/")));
        board_name = board_name.substr(0, ix);
        return this->dashboard->delete_post(this->response, board_name, id);
    }
    this->response->code = 404;
    this->response->payload = "Unknown DELETE request";
    return 404;
}

int Handler::handle_request() {
    if (this->request->method == "GET") {
        return this->get_requests();
    } else if (this->request->method == "POST") {
        return this->post_requests();
    } else if ((this->request->method == "PUT")) {
        return this->put_requests();
    } else if (this->request->method == "DELETE") {
        return this->delete_requests();
    } else {
        this->response->code = 404;
        this->response->payload = "Unknown HTTP request method";
        return 404;
    }
}

