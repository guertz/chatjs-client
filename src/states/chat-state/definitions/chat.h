#ifndef STATES_CHAT_STATE_DEFINITIONS_CHAT_H
#define STATES_CHAT_STATE_DEFINITIONS_CHAT_H

namespace States {
    namespace ChatState {

        enum ACK_LEVEL {
            WAITING,
            SENT,
            RECEIVED
        };

        // const data = true!!
        typedef struct message_block_data {
            std::string content;
            ACK_LEVEL status;
            bool isMe;
            std::string avatar;
            std::string time;
        } message_block;

    }
}


#endif