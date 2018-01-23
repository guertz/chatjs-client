#include <map>
#include "chat.h"
#include "protocol/sockets/wscustom.h"

using namespace ws;
using namespace std;

typedef map<string, message_block> typo_chat; // as a Vector ? 

struct chat_details_data {
    char* reference;
    char* destination;
    char* from;
    char* creator;
    typo_chat messages;
};

typedef struct chat_details_data chat_details;

typedef map<string, chat_details> typo_chats;

namespace ChatState {
    typedef map<string, Socket*> typo_chat_watchers;
    typedef map<string, void(*)(const char* arg)> Methods;

    void Bootstrap();
    void Destroy();
    
    namespace Sockets {
        void Init(const string );

        void NewChatSuccess(const string);
        void NewChatError(const string);

        void NewMessageSuccess(const string);
        void NewMessageError(const string);
    }

    namespace Chat {
        void Register(string , void (*)(const char* ));
        void Notify(const char* );
        const chat_details& Get(const char* );
        void SendAMessage(const char* );
    }

    namespace Chats { 
        void Register(string , void (*)(const char* ));
        void Notify(const char* );
        const typo_chats& Get();
        void StartAChat(const string );   
    }

    namespace Auth {
        void State(const char* );
    }
}