#include <stdlib.h>
#include <stdio.h>

#include <netinet/in.h>

typedef struct mac_struct {
    char octet_one;
    char octet_two;
    char octet_three;
    
    char octet_four;
    char octet_five;
    char octete_six;
} mac_t;

/*
  Allocate memory for a mac address.
  
  Returns NULL on failure.
*/
mac_t *mac_alloc(void) {
    return malloc(sizeof(mac_t));
}

/*
  Convert a string to a mac_t, this can be a string seperate with : or -.
  
  Examples:
    mac_from_str("01-23-45-67-89-ab");
    mac_from_str("01:23:45:67:89:ab");
  
  Returns 1 on sucsess or 0 on failure.
*/
int mac_from_str(mac_t *mac, char *string) {
    return 0;
}

/*
  Wake up this mac address.
  
  Returns 1 on sucsess or <0 on failure.
*/
int mac_wake(mac_t *address) {
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
    
    if (sendto(sock, "test", 4, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 4) {
        return -4;
    }
    
    return 1;
}

/*
  Release the mac address.
*/
void mac_dealloc(mac_t *mac) {
    free(mac);
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s <mac_address>\n", argv[0]);
        printf("Mac address should be in either of the following formats:\n");
        printf("  01-23-45-67-89-ab\n");
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
        printf("  01-23-45-67-89-ab\n");
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
