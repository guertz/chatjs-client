namespace ChatList {

    void Bootstrap();

    namespace Events {
        void UserSelected(const char* arg);
        void NewChat(const char* argc);
    }

    namespace Auth {
        void State(const char* arg);
    }

    namespace Chats {
        void NewChat(const char* args); // better way in state?
        void State(const char* arg);    // should handle both + MessagesChange
                                        // distinct event types
    }
}