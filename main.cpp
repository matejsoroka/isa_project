#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include "Request.h"
#include "Handler.h"
#include "Dashboard.h"

#define MAX 8192
#define PORT 8087

void
func(int sockfd, Dashboard *dashboard)
{
    char buff[MAX];
    int n;
    bzero(buff, MAX);

    // read the message from client and copy it in buffer
    read(sockfd, buff, sizeof(buff));
    // print buffer which contains the client contents

    Request req(buff);
    Response res = Response();
    Handler h(&req, &res, dashboard);

    // and send that buffer to client
    strcpy(buff, res.raw.c_str());
    send(sockfd, buff, sizeof(buff), 0);
}

int
main(int argc, char** argv)
{
    int s_fd, c_fd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(s_fd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    Dashboard dashboard;

    while(true)
    {
        // Now server is ready to listen and verification
        if ((listen(s_fd, 5)) != 0) {
            printf("Listen failed...\n");
            exit(0);
        }
        else
            printf("Server listening..\n");

        len = sizeof(cli);
        // Accept the data packet from client and verification
        c_fd = accept(s_fd, (struct sockaddr*)&cli, reinterpret_cast<socklen_t *>(&len));
        if (c_fd < 0) {
            printf("server acccept failed...\n");
            exit(0);
        }
        else {
            printf("server acccept the client...\n");
        }

        // Function for chatting between client and server
        func(c_fd, &dashboard);
    }

    close(s_fd);
    return 0;
}