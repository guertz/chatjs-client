#ifndef PAGES_CHAT_DETAILS_CHAT_DETAILS_H
#define PAGES_CHAT_DETAILS_CHAT_DETAILS_H

namespace ChatDetails {

    void Bootstrap();

    namespace Events {
        inline void Submit(const std::string& args);
    }

    namespace State {
        void Chat();
    }
}

#endif