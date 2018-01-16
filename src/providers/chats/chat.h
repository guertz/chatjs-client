#ifndef chat_definition_h
#define chat_definition_h

enum ACK_LEVEL {
    WAITING,
    SENT,
    RECEIVED
};

// const data = true!!
struct message_block_data {
    char* content;
    ACK_LEVEL status;
    bool isMe;
    char* avatar;
    char* time;
};

typedef struct message_block_data message_block;

#endif