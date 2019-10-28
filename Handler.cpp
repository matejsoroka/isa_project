//
// Created by matthew on 28.10.19.
//

#include "Handler.h"

Handler::Handler(Request *request, Response *response) {
    this->request = request;
    response->code = 200;
    response->payload = "All good";
    response->raw = response->generate_response();
    this->response = response;
}
