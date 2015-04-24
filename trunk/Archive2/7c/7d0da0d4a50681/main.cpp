// I know this is more C but still.

int send_data(char *message){
    if( send(sock , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 0;
    }
    printf("Sent message [");
    for (int i = 0; i < sizeof(message)/sizeof(char);i++)
        printf("%.02hhx ",message[i]);
    printf("]\n");
    return 1;
}


int handle_std_rec(char *reply, int n){
    for (int i = 0; i < n; i++){
        printf("%.02hhx ",reply[i]);
    }

    printf("\n");
    char msg[4] = {0x00,0x02,0x01,reply[2]}; // 3rd bit in FCDR msg is record-number
    send_data(msg);
}

-- output
Reply:  BYTES=57
00 37 58 af b0 18 81 15 04 24 13 26 00 10 38 0f ff ff 88 83 55 00 ff ff ff ff ff ff 00 10 39 3f ff ff ff ff ff ff ff ff ff ff ff ff 3f 3f 03 00 00 0f 00 8f 3f 1f 00 00 00
Sent message [00 02 01 58 00 00 00 00 ]
