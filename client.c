#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to the server");
        exit(1);
    }

    int num;
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &num);

    send(client_socket, &num, sizeof(num), 0);

    int result;
    recv(client_socket, &result, sizeof(result), 0);

    printf("square of %d is: %d\n", num, result);

    close(client_socket);

    return 0;
}
