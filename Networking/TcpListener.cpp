#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "TcpListener.hpp"

TcpListener::TcpListener(std::uint16_t port, std::uint16_t backlog)
    : m_port(port),
    m_backlog(backlog)

{}

void TcpListener::Start() {
    Init();
}

void TcpListener::Stop() {
    close(m_sock_fd);
}

std::unique_ptr<NetworkStream> TcpListener::AcceptClient() {
    int new_fd;
    socklen_t sin_size;
    struct sockaddr_storage their_addr; // connector's address information
    char s[INET6_ADDRSTRLEN];

    printf("server: waiting for connections...");

    sin_size = sizeof their_addr;
    new_fd = accept(m_sock_fd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
    }

    inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
        s, sizeof s
    );
    printf("server: got connection from %s", s);

    return std::make_unique<NetworkStream>(new_fd);
}

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *TcpListener::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Beej's Guide to Network programming, but modified
void TcpListener::Init() {
    struct addrinfo hints, *servinfo, *p;
    struct sigaction sa;
    int yes=1;
    int rv;


    SetupSocketSpecs(hints);

    if ((rv = getaddrinfo(NULL, std::to_string(m_port).c_str(), &hints, &servinfo)) != 0) {
        printf("getaddrinfo: %s", gai_strerror(rv));
        throw std::exception();
    }

    // Bind to socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((m_sock_fd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server socket");
            continue;
        }

        if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(m_sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(m_sock_fd);
            perror("socket binding");
            continue;
        }

        break;
    }    
    // Bind to socket end

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        perror("server faild to bind");
        exit(1);
    }

    if (listen(m_sock_fd, m_backlog) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

void TcpListener::SetupSocketSpecs(struct addrinfo& hints) {
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    printf("Set up socket specs");
}

void TcpListener::BindToSocket(struct addrinfo* p, struct addrinfo *servinfo, int& yes) {
    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((m_sock_fd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(m_sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(m_sock_fd);
            perror("socket binding");
            continue;
        }

        break;
    }
}
