#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "wol.h"

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
