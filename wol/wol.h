typedef struct mac_struct {
    char *packet;
    int packet_length;
    
    int octet_one;
    int octet_two;
    int octet_three;
    
    int octet_four;
    int octet_five;
    int octet_six;
} mac_t;

/*
  Allocate memory for a mac address.
  
  Returns NULL on failure.
*/
mac_t *mac_alloc(void);

/*
  Generates a wake on lan packet
  
  Returns 1 on sucsess or 0 on failure.
*/
int mac_build_packet(mac_t *mac);

void *mac_free_packet(char *packet);

/*
  Convert a string to a mac_t, this can be a string seperate with : or -.
  
  Examples:
    mac_from_str("01:23:45:67:89:ab");
  
  Returns 1 on sucsess or 0 on failure.
*/
int mac_from_str(mac_t *mac, char *string);

/*
  Wake up this mac address.
  
  Returns 1 on sucsess or <0 on failure.
*/
int mac_wake(mac_t *mac);

/*
  Release the mac address.
*/
void mac_dealloc(mac_t *mac);

