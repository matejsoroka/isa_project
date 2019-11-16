#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "Request.h"
#include "Handler.h"
#include "Dashboard.h"

#define MAX 8192

void
print_help()
{
    std::cout << "Run program with port as argument -p for example\n"
                 "./isaserver -p 8080" << std::endl;
}

void
handle_request(int socket, Dashboard *dashboard)
{
    // Init buffer
    char buff[MAX];
    memset(&buff, 0, MAX);

    // read the message and copy it to buffer
    read(socket, buff, sizeof(buff));

    // Generate request from message
    Request req(buff);

    // Initialize response object
    Response res = Response();

    // If request is invalid
    if (req.method == "ERROR") {
        res.payload = "Invalid request";
        res.code = 404;
        res.generate_response();
        strcpy(buff, res.raw.c_str());
        send(socket, buff, sizeof(buff), 0);
        return;
    }

    // Initialize handler which handle request, make operations in dashboard and generate response
    Handler(&req, &res, dashboard);

    // Send response back
    strcpy(buff, res.raw.c_str());
    send(socket, buff, sizeof(buff), 0);
}

int
main(int argc, char** argv)
{
    double port = 0;
    if (argc == 3) {
        if (!strcmp(argv[1], "-h")) {
            print_help();
            return 0;
        } else if (!strcmp(argv[1], "-p")) {
            port = strtod(argv[2], nullptr);
            if (port == 0) {
                std::cerr << "Port is not a number" << std::endl;
                return 10;
            }
        } else {
            std::cerr << "Unknown argument" << std::endl;
            return 10;
        }
    } else {
        std::cerr << "Please set up port correctly" << std::endl;
        return 10;
    }

    int s_fd, c_fd, len;
    struct sockaddr_in server{}, client{};

    // Create server socket
    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd == -1) {
        std::cerr << "Unable to create socket" << std::endl;
        return 1;
    }

    // Reset server address
    memset(&server, 0, sizeof(server));

    // Assign IP version, PORT
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Socket bind
    if ((bind(s_fd, (struct sockaddr*)&server, sizeof(server))) != 0) {
        std::cerr << "Unable to bind socket, try to choose another port" << std::endl;
        return 1;
    }

    Dashboard dashboard;

    while(true)
    {
        // Start listening
        if ((listen(s_fd, 5)) != 0) {
            std::cerr << "Unable to bind listen" << std::endl;
            return 1;
        } else {
            std::cout << "Server is listening on port: " << port << std::endl;
        }

        len = sizeof(client);
        // Accept the data from source
        c_fd = accept(s_fd, (struct sockaddr*)&client, reinterpret_cast<socklen_t *>(&len));
        if (c_fd < 0) {
            std::cerr << "Unable to accept request" << std::endl;
        }
        handle_request(c_fd, &dashboard);
    }

}