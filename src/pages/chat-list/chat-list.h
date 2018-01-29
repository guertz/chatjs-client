#ifndef PAGES_CHAT_LIST_CHAT_LIST_H
#define PAGES_CHAT_LIST_CHAT_LIST_H

#include "states/auth-state/auth-state.h"

namespace ChatList {

    void Bootstrap();

    namespace Events {
        void UserSelected(const std::string& arg);
        void NewChat(const std::string& arg);
    }

    namespace State {
        void Auth();
        void Chats();
    }
}

#endif