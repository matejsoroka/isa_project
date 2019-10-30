//
// Created by matthew on 28.10.19.
//

#ifndef ISA_PROJECT_HANDLER_H
#define ISA_PROJECT_HANDLER_H


#include "Request.h"
#include "Response.h"
#include "Dashboard.h"

class Handler {
    Request* request;
    Response* response;
    Dashboard* dashboard;
public:
    explicit Handler(Request* request, Response* response, Dashboard* dashboard);
    int handle_request();
    int create_board(std::string board_name);
    int get_requests();
    int delete_requests();
    int post_requests();
    int put_requests();
};


#endif //ISA_PROJECT_HANDLER_H
