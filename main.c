#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

void show_packet(unsigned char *buffer) {

    struct iphdr *ip = (struct iphdr*)buffer;
    struct sockaddr_in addr_src, addr_dst;

    if (ip->protocol == 6)
        printf("tcp ");
    else if (ip->protocol == 17)
        printf("udp ");

    printf("size: %d \n", ntohs(ip->tot_len));

    addr_src.sin_addr.s_addr = ip->saddr;
    addr_dst.sin_addr.s_addr = ip->daddr;

    printf("source: %s ", inet_ntoa(addr_src.sin_addr));
    printf("dest: %s\n", inet_ntoa(addr_dst.sin_addr));
}


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
            //printf("%d ", buffer[i]);
        }
        show_packet(buffer);
    }

    close(sock);
    return 0;
}
