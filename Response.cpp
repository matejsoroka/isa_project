//
// Created by Matej Soroka on 28.10.19.
//

#include "Response.h"

#include <sstream>
#include <iomanip>

std::string
Response::generate_response()
{
    auto date = Response::generate_date();
    std::stringstream ss;
    std::string code_msg;

    if (this->code >= 400 && this->code <= 499) {
        code_msg = "Not Found";
    } else if (this->code >= 200 && this->code <= 200) {
        code_msg = "OK";
    } else {
        code_msg = "SERVER ERROR";
    }

    ss << "HTTP/1.1 " << this->code << " " << code_msg << "\n"
        << "Date: " << date << "\n"
        << "Server: Dashboard v0.1\n"
        << "Content-Type: text/plain\n"
        << "Content-Length: " << this->payload.length() << "\n"
        << "Connection: close\n\n"
        << this->payload;

    return ss.str();
}

std::string Response::generate_date()
{
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    std::ostringstream formatted;
    formatted << std::put_time(&tm, "%a, %d %b %Y %H:%M:%S %Z");
    return formatted.str();
}
