//
// Created by matthew on 28.10.19.
//

#ifndef ISA_PROJECT_HANDLER_H
#define ISA_PROJECT_HANDLER_H


#include "Request.h"
#include "Response.h"

class Handler {
    Request* request;
    Response* response;
public:
    explicit Handler(Request* request, Response* response);
};


#endif //ISA_PROJECT_HANDLER_H
