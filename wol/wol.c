#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "wol.h"

mac_t *mac_alloc(void) {
    return (mac_t*)malloc(sizeof(mac_t));
}

int mac_build_packet(mac_t *mac) {
    unsigned int i;
    mac->packet_length = 6*17;
    mac->packet = malloc((size_t)mac->packet_length);
    
    if (mac->packet == NULL) {
        return 0;
    }
    
    /* Set the first 6 bytes of the packet to FF:FF:FF:FF:FF:FF */
    for (i = 0; i < 6; i++) {
        mac->packet[i] = 255;
    }
    
    /* The next part is the mac address 16 times. */
    for (i = 1; i < 17; i++) {
        mac->packet[i*6] = mac->octet_one;
        mac->packet[i*6 + 1] = mac->octet_two;
        mac->packet[i*6 + 2] = mac->octet_three;
        mac->packet[i*6 + 3] = mac->octet_four;
        mac->packet[i*6 + 4] = mac->octet_five;
        mac->packet[i*6 + 5] = mac->octet_six;
    }
    
    return 1;
}

void *mac_free_packet(char *packet) {
    free(packet);
}

int mac_from_str(mac_t *mac, const char *string) {
    if (sscanf(string, "%x:%x:%x:%x:%x:%x", &mac->octet_one, &mac->octet_two, &mac->octet_three, &mac->octet_four, &mac->octet_five, &mac->octet_six) != 6) {
        return 0;
    }
    
    return mac_build_packet(mac);
}

int mac_wake(mac_t *mac) {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    int broadcast = 1;
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9);
    
    if (sock == -1) {
        return -1;
    }
    
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(int)) == -1) {
        return -2;
    }
    
    if (!inet_aton("255.255.255.255", &addr.sin_addr)) {
        return -3;
    }
    
    if (sendto(sock, mac->packet, mac->packet_length, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != mac->packet_length) {
        return -4;
    }
    
    return 1;
}

void mac_dealloc(mac_t *mac) {
    if (mac->packet != NULL) {
        free(mac->packet);
    }
    
    free(mac);
}

