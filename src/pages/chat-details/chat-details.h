namespace ChatDetails {

    void Bootstrap();

    namespace Events {
        void Submit(const char* );
        void OpenChat(const char* );
    }

    namespace Chat {
        void State(const char* );
    }
}