#include <map>
#include "common/helpers/web_ui.h"
#include "providers/sockets/wscustom.h"

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