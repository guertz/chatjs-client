#ifndef STATES_CHAT_STATE_CHAT_STATE_H
#define STATES_CHAT_STATE_CHAT_STATE_H

#include <map>

#include "definitions/chat.h"
#include "definitions/chat-methods/request.h"
#include "definitions/chat-methods/response.h"
#include "definitions/chats-methods/request.h"
#include "definitions/chats-methods/response.h"

#include "protocol/sockets/wscustom.h"

namespace States {

    namespace ChatState {

        typedef std::map<std::string, ws::Socket*> SocketsMap;

        // No argument is fine (get last action);
        typedef std::map<std::string, void(*)()> Subscribers;

        void Bootstrap();
        void Destroy();
        
        // inline void Init(const std::string& );

        // OnLogout destroy chat on both side
        namespace ChatMethods {
            void Register(std::string , void (*)());
            const Chat& getChatByRef(const std::string& );

            void SendAMessage(const std::string& );

            inline void Notify();
            inline void ResponseSuccess(const std::string);
            inline void ResponseError(const std::string);
        }

        namespace ChatsMethods {
            void Register(std::string , void (*)());
            const Chats& getChatsByRef();

            void StartAChat(const string& user_dest);

            inline void Notify();
            inline void ResponseSuccess(const std::string);
            inline void ResponseError(const std::string);
        }

        namespace State {
            void Auth();
        }
    }
}

#endif