#ifndef PAGES_CHAT_LIST_CHAT_LIST_H
#define PAGES_CHAT_LIST_CHAT_LIST_H

#include "states/auth-state/auth-state.h"

namespace ChatList {

    void Bootstrap();

    namespace Events {
        void UserSelected(const std::string& arg);
        void NewChat(const std::string& arg);
    }

    namespace Auth {
        void State(const States::AuthState::AuthBaseDefinition::AuthBase& );
    }

    namespace Chats {
        void NewChat(const std::string& args);
        void State(const std::string& arg);
    }

    namespace Chat {
        void State();
    }
}

#endif