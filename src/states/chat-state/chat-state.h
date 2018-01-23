#ifndef STATES_CHAT_STATE_CHAT_STATE_H
#define STATES_CHAT_STATE_CHAT_STATE_H

#include <map>

#include "definitions/chat.h"

#include "protocol/sockets/wscustom.h"

#include "states/auth-state/auth-state.h"

namespace States {

    namespace ChatState {

        typedef std::map<std::string, message_block> typo_chat; // as a Vector ? 

        typedef struct chat_details_data {
            std::string reference;
            std::string destination;
            std::string from;
            std::string creator;
            typo_chat messages;
        } chat_details;

        typedef std::map<std::string, chat_details> typo_chats;
        typedef std::map<std::string, ws::Socket*> typo_chat_watchers;

        typedef std::map<std::string, void(*)(const std::string& arg)> Methods;
        typedef std::map<std::string, void(*)()> Methods_void;

        void Bootstrap();
        void Destroy();
        
        namespace Sockets {
            void Init(const std::string& );

            void NewChatSuccess(const std::string);
            void NewChatError(const std::string);

            void NewMessageSuccess(const std::string);
            void NewMessageError(const std::string);
        }

        namespace Chat {
            void Register(string , void (*)());
            void Notify();
            const chat_details& Get(const string& );
            void SendAMessage(const string& );
        }

        namespace Chats { 
            void Register(string , void (*)(const string& ));
            void Notify(const string& );
            const typo_chats& Get();
            void StartAChat(const string& );   
        }

        namespace Auth {
            void State(const States::AuthState::AuthBaseDefinition::AuthBase& );
        }
    }
}

#endif