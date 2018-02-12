#ifndef STATES_CHAT_STATE_CHAT_STATE_H
#define STATES_CHAT_STATE_CHAT_STATE_H

#include <map>

#include "models/chat/chat.h"
#include "models/socket/chat/chat.h"
#include "models/socket/chats/chats.h"


namespace States {

    namespace ChatState {
        
        /** 
        * Definizione della struttura map che associa ad ogni stringa 
        * un puntatore a funzione. Viene utilizzata per gestire i componenti
        * che sottoscrivono ad ascoltare gli eventi di questo stato e a
        * notificare dei cambiamenti
        */
        typedef std::map<std::string, void(*)()> Subscribers;

        namespace ChatMethods {

            /**
            * Inserisce nella mappa dei subscribers ::Subscribers un evento di callback.
            *
            * @param[in] cb_name string contenente il nome di riferimento all'evento di callback
            * @param[in] cb_fn Puntatore a funzione relativo all'evento di callback da invocare
            * 
            */
            void Register(std::string cb_name, void (*cb_fn)());

            void SendAMessage(const std::string& text);

        }

        namespace ChatsMethods {
            void Register(std::string , void (*)());

            void StartAChat(const std::string& user_dest);

            // Chats
            const std::string getSerializedChats();

            // Chat (current of chats)
            void setCurrentChat(const std::string& reference);
            bool isCurrentChat();

            const std::string getCurrentChatRef();
            const std::string getCurrentChat();

        }

        void Bootstrap();
        void Destroy();

        namespace State {
            void Auth();
        }
    }
}

#endif