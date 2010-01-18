#include <stdlib.h>
#include <stdio.h>

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
*/
void mac_wake(mac_t *address) {
    
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
    
    mac_wake(mac);
    mac_dealloc(mac);
    
    return 0;
}
