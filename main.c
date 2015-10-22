#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

    int sock;
    int addr_size, data_size;
    struct sockaddr addr;
    unsigned char *buffer = (unsigned char*)malloc(65536);

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 1) {
        printf("error creating raw socket.. root?\n");
        return 0;
    }

    addr_size = sizeof(addr);
    memset(buffer, 0, 65536);

    while (1) {

        data_size = recvfrom(sock, buffer, 65536, 0, &addr, &addr_size);
        if (data_size < 0) {
            printf("error recvfrom...\n");
            return 0;
        }

        for (int i=0; i<data_size; i++) {
            printf("%d ", buffer[i]);
        }
    }

    close(sock);
    return 0;
}
