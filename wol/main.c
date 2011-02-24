#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "wol.h"

mac_t *mac_alloc(void) {
    return malloc(sizeof(mac_t));
}

int mac_build_packet(mac_t *mac) {
    int i;
    mac->packet_length = 6*17;
    mac->packet = malloc(mac->packet_length);
    
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

int mac_from_str(mac_t *mac, char *string) {
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

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s <mac_address>\n", argv[0]);
        printf("Mac address should be in either of the following formats:\n");
        printf("  01:23:45:67:89:ab\n");
        
        return 0;
    }
    
    mac_t *mac = mac_alloc();
    
    if (mac == NULL) {
        printf("Problem allocating memory.\n");
        return 1;
    }
    
    if (mac_from_str(mac, (char *)argv[1]) == 0) {
        printf("Incorrect mac address, was this in either of the following formats:\n");
        printf("  01:23:45:67:89:ab\n");
        
        mac_dealloc(mac);
        return 2;
    }
    
    if (mac_wake(mac) != 1) {
        printf("A strange networking error occured.\n");
        mac_dealloc(mac);
        return 3;
    }
    
    mac_dealloc(mac);
    
    return 0;
}
