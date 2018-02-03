#ifndef DIRECTIVES_NAVBAR_PROFILE_PROFILE_H
#define DIRECTIVES_NAVBAR_PROFILE_PROFILE_H

namespace Navbar {
    namespace Profile {
        void RegisterLink();
        void EraseLink();

        namespace Events {
            void Disconnect(const std::string&);
            void SetText(const std::string);
        }


    }
}

#endif