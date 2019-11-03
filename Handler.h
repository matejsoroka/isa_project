//
// Created by Matej Soroka on 28.10.19.
//

#ifndef ISA_PROJECT_HANDLER_H
#define ISA_PROJECT_HANDLER_H


#include "Request.h"
#include "Response.h"
#include "Dashboard.h"

class Handler {
    Request* request;         // pointer to request object
    Response* response;       // pointer to response object
    Dashboard* dashboard;     // pointer to dashboard object

    /**
     * Handle request
     * @return return code
     */
    int handle_request();

    /**
     * Process GET request
     * @return return code
     */
    int get_requests();

    /**
     * Process DELETE request
     * @return return code
     */
    int delete_requests();

    /**
     * Process POST request
     * @return return code
     */
    int post_requests();

    /**
     * Process PUT request
     * @return return code
     */
    int put_requests();

public:
    /**
     * When add objects are set, handler handles request, uses dashboard as data source
     * and sets response
     * @param request Requests object
     * @param response Response object
     * @param dashboard Dashboard object
     */
    explicit Handler(Request* request, Response* response, Dashboard* dashboard);
};


#endif //ISA_PROJECT_HANDLER_H
