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
        typedef std::map<std::string, void(*)()> Subscribers;

        void Bootstrap();
        void Destroy();
        
        namespace ChatMethods {
            void Register(std::string , void (*)());
            inline void InitAChat(const Chat& chat);

            void SendAMessage(const std::string& text);

            inline void Notify();
            inline void ResponseSuccess(const std::string);
            inline void ResponseError(const std::string);
        }

        namespace ChatsMethods {
            void Register(std::string , void (*)());

            inline void Init(const std::string& AUTH);
            
            const std::string getSerializedChats();

            void setCurrent(const std::string& reference);
            const std::string getCurrent();
            bool isCurrentChat();
            const std::string getCurrentChat();

            void StartAChat(const std::string& user_dest);

            inline void Notify();
            inline void Clean();
            inline void ResponseSuccess(const std::string);
            inline void ResponseError(const std::string);
        }

        namespace State {
            void Auth();
        }
    }
}

#endif