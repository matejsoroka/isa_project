#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <netdb.h>
#include "Request.h"

#define MAX 8192

void
print_help()
{
    std::cout << "Run with port as argument -p for port and -H for host, host can be IP "
                 "address of server or hostname of server.\n\n"
                 "./isaclient -H 127.0.0.1 -p 80 <command>\n"
                 "where command can be from supported commands below.\n\n"
                 "boards - Get list of boards\n"
                 "board add <name> - Create new board\n"
                 "board delete <name> - Delete board\n"
                 "board list <name> - List board posts\n"
                 "item add <name> <content> - Add post to board\n"
                 "item delete <name> <id> - Delete board post by id\n"
                 "item update <name> <id> <content> - Edit post by id" << std::endl;
}

int
main(int argc, char** argv)
{

    int option;

    std::string server_ip;
    double port;

    while((option = getopt(argc, argv, "H:p:h")) != -1) {
        switch (option){
            case 'H':
                server_ip = optarg;
                break;
            case 'p':
                port = strtod(optarg, nullptr);
                break;
            case 'h':
                print_help();
                return 0;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }

    /* Initialize request object */
    Request req("");

    if (argc == 6 && !strcmp(argv[5], "boards")) { // If having six arguments

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

    } else if (argc == 9 && !strcmp(argv[5], "item")) {  // If having nine arguments

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

    } else { // Invalid count of arguments
        std::cerr << "Invalid request" << std::endl;
        return 1;
    }

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) return -1;

    sockaddr_in hint{};           // Initialize address structure
    hint.sin_family = AF_INET;    // Set IP version
    hint.sin_port = htons(port);  // Set port for service
    struct hostent *servent;      // Initialize host server struct

    /* DNS resolution */
    if ((servent = gethostbyname(argv[2])) == nullptr)
        std::cout << "Get hostbyname error" << std::endl;

    // Copy server address
    memcpy(&hint.sin_addr,servent->h_addr,servent->h_length);

    // Establish connection between client and server
    int server_connect = connect(sock, (sockaddr *) &hint, sizeof(hint));
    if (server_connect == -1) {
        return 1;
    }

    // Send request to server
    int send_request = send(sock, req.raw.c_str(), req.raw.size() + 1, 0);
    if (send_request == -1) {
        std::cerr << "Error sending request";
        return 1;
    }

    // Create request buffer and initialize it
    char buff[MAX];
    memset(&buff, 0, MAX);

    // Receive response from server
    recv(sock, buff, MAX, 0);

    // Convert char array to string and strip headers
    std::string payload = buff;

    std::cerr << payload.substr(0, payload.find("\r\n\r\n")) << std::endl;  // Headers to stderr
    std::cout << payload.substr(payload.find("\r\n\r\n") + 4) << std::endl; // Payload to stdout

    close(sock);

    return 0;
}