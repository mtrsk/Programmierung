#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define SOCKET int
#define MAX_ALLOWED_CONN 5

int main() {
    // getaddrinfo has a structure 'hints' as one of its arguments.
    struct addrinfo hints;
    // Zero out hints
    memset(&hints, 0, sizeof(hints));
    // Setting some values that are going to be needed by getaddrinfo
    // AF_INET -> IPV4 addresses
    // SOCK_STREAM -> Use TCP
    // AI_PASSIVE -> Gets getaddrinfo to setup the address
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Use getaddrinfo to populate a structure 'bind_address' with values.
    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    // Create socket and then check if its valid
    printf("Creating the socket...\n");
    SOCKET socket_server;
    socket_server = socket(
        bind_address->ai_family,
        bind_address->ai_socktype,
        bind_address->ai_protocol
    );

    if (socket_server < 0){
        fprintf(stderr, "socker() creation has failed with (%d)\n", errno);
        return 1;
    };

    // The socket must initially be created to accept IPV6 connections only.
    // Now one can modify it to also accept IPV4 using setsockopt.
    int option = 0;
    if (setsockopt(socket_server, IPPROTO_IPV6, IPV6_V6ONLY, (void *) &option, sizeof(option))){
        fprintf(stderr, "setsockopt() failed with (%d)\n", errno);
    };

    // bind returns 0 on sucess and non-zero on failure.
    printf("Binding the socket to local address...\n");
    if (bind(socket_server, bind_address->ai_addr, bind_address->ai_addrlen)){
        fprintf(stderr, "bind() failed with (%d)\n", errno);
        return 1;
    };
    freeaddrinfo(bind_address);

    // If the socket is created and is bound to an address one can use
    // the listening function.
    printf("Listening...\n");
    if (listen(socket_server, MAX_ALLOWED_CONN) < 0){
        fprintf(stderr, "listen() failed with (%d)\n", errno);
        return 1;
    };
    // If nothing was wrong, then wait for the client to connect...
    printf("Waiting for connection...\n");

    // Store the addr info of the client.
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    SOCKET socket_client = accept(
        socket_server,
        (struct sockaddr*) &client_address,
        &client_len
    );

    if (socket_client < 0){
        fprintf(stderr, "accept() failed with (%d)\n", errno);
        return 1;
    };

    // Logs the new connection to the buffer
    printf("Client is connected\t");
    char addr_buffer[100];
    getnameinfo(
        (struct sockaddr*) &client_address,
        client_len,
        addr_buffer,
        sizeof(addr_buffer),
        0,
        0,
        NI_NUMERICHOST
    );
    printf("%s\n", addr_buffer);

    // Parse the client's HTTP request
    char request[1024];
    int bytes_recv = recv(socket_client, request, 1024, 0);
    printf("%d bytes received\n", bytes_recv);

    // Send a const HTTP response (for now...)
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "System Time: ";
    int bytes_sent = send(socket_client, response, strlen(response), 0);
    if (bytes_sent < 0) {
        fprintf(stderr, "send() failed with (%d)\n", errno);
        return 1;
    };

    // Getting the system time
    time_t timer;
    time(&timer);

    char *time_msg = ctime(&timer);
    bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
    if (bytes_sent < 0) {
        fprintf(stderr, "send() failed with (%d)\n", errno);
        return 1;
    };

    printf("Closing connection...\n");

    // Close both sockets
    close(socket_client);

    close(socket_server);

    return 0;
}
