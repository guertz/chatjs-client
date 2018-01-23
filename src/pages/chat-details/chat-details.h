#ifndef PAGES_CHAT_DETAILS_CHAT_DETAILS_H
#define PAGES_CHAT_DETAILS_CHAT_DETAILS_H

namespace ChatDetails {

    void Bootstrap();

    namespace Events {
        void Submit(const std::string& );
        void OpenChat(const std::string& );
    }

    namespace Chat {
        void State();
    }
}

#endif