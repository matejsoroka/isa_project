#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <netdb.h>
#include "Request.h"

#define MAX 8192

int
main(int argc, char** argv)
{
    double port = 0;
    std::string server_ip;

    if (argc > 5 && !strcmp(argv[1], "-H") && !strcmp(argv[3], "-p")) {
        port = strtod(argv[4], nullptr);
        if (port == 0) {
            std::cerr << "Port is not a number" << std::endl;
            return 10;
        }
        server_ip = argv[2];
    } else {
        std::cerr << "Please set up port or address correctly" << std::endl;
        return 10;
    }

    Request req("");

    if (argc == 6 && !strcmp(argv[5], "boards")) {
        req.set_request(server_ip, "/boards", "GET", "");
    } else if (argc == 8 && !strcmp(argv[5], "board")) {
        if (!strcmp(argv[6], "add")) {
            std::ostringstream url;
            url << "/boards/" << argv[7];
            req.set_request(server_ip, url.str(), "POST", "");
        } else if (!strcmp(argv[6], "delete")) {
            std::ostringstream url;
            url << "/boards/" << argv[7];
            req.set_request(server_ip, url.str(), "DELETE", "");
        } else if (!strcmp(argv[6], "list")) {
            std::ostringstream url;
            url << "/board/" << argv[7];
            req.set_request(server_ip, url.str(), "GET", "");
        } else {
            std::cerr << "Invalid request" << std::endl;
            return 1;
        }
    } else if (argc == 9 && !strcmp(argv[5], "item")) {
        if (!strcmp(argv[6], "add")) {
            std::ostringstream url;
            url << "/board/" << argv[7];
            req.set_request(server_ip, url.str(), "POST", argv[8]);
        } else if (!strcmp(argv[6], "delete")) {
            std::ostringstream url;
            url << "/board/" << argv[7] << argv[8];
            req.set_request(server_ip, url.str(), "DELETE", "");
        } else if (!strcmp(argv[6], "update")) {
            std::ostringstream url;
            url << "/board/" << argv[7];
            req.set_request(server_ip, url.str(), "PUT", argv[8]);
        } else {
            std::cerr << "Invalid request" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Invalid request" << std::endl;
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) return -1;

    sockaddr_in hint{};

    hint.sin_family = AF_INET;
    struct hostent *servent;

    if ((servent = gethostbyname(argv[2])) == nullptr) // check the first parameter
        std::cout << "Get hostbyname error" << std::endl;

    hint.sin_port = htons(port);
    memcpy(&hint.sin_addr,servent->h_addr,servent->h_length);

    int server_connect = connect(sock, (sockaddr *) &hint, sizeof(hint));
    if (server_connect == -1) {
        return 1;
    }

    char buff[MAX];

    int send_request = send(sock, req.raw.c_str(), req.raw.size() + 1, 0);
    if (send_request == -1) {
        std::cerr << "Error sending request";
        return 1;
    }

    memset(&buff, 0, MAX);
    int received = recv(sock, buff, MAX, 0);

    std::cout << buff << "\n";

    close(sock);

    return 0;
}