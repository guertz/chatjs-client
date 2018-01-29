#ifndef PAGES_CHAT_DETAILS_CHAT_DETAILS_H
#define PAGES_CHAT_DETAILS_CHAT_DETAILS_H

#include <iostream>

namespace ChatDetails {

    void Bootstrap();

    namespace Events {
        void Submit(const std::string& );
    }

    namespace State {
        void Chat();
    }
}

#endif