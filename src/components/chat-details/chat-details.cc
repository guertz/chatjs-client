#include <iostream>
#include <json.hpp>

#include "chat-details.h"
#include "chat-details.js.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/chats-state/chats-state.h"

using json = nlohmann::json;
using namespace std;
using namespace States;

/**
 * @brief Definizione pagina ChatDetails in cui viene visualizzata la chat attiva
 * @file chat-details.cc
 */

/** Variabile per limitare il numero di messaggi per chat */
// const unsigned int MESSAGES   = 10;

namespace ChatDetails {

    const string CHAT_INACTIVE = "alert('Deve prima essere selezionata una chat')";

    const string ENABLE_FORM  = "components.ChatDetails.enable()";
    const string DISABLE_FORM = "components.ChatDetails.disable()";
    const string RESET_ALL = "components.ChatDetails.resetChat()";

    namespace Events {

        inline void Submit(const std::string& args){
            log_details(TAG::CMP, "ChatDetails::Submit", args);

            json form_args = json::parse(args);
            ChatsState::ChatMethods::SendAMessage(form_args.at("text").get<string>());

        }
    }

    void Bootstrap() {
        log_base(TAG::CMP, "ChatDetails::Bootstrap", "");

        WebUI::Execute(_src_components_chat_details_chat_details_js);
        WebUI::Execute(DISABLE_FORM);

        WebUI::Register("ChatDetails::Submit", Events::Submit);

        ChatsState::ChatMethods::Register("ChatDetails", State::Chat);

    }

    void Destroy() {
        log_base(TAG::CMP, "ChatDetails::Destroy", "");
    }

    namespace State {
        inline void Chat(){
            if(ChatsState::isCurrentChat()){
                const string js_chat = "components.ChatDetails.populateChatDetails('" +
                                            ChatsState::getCurrentChat() +
                                        "')";

                WebUI::Execute(js_chat);
                WebUI::Execute(ENABLE_FORM);
            } else { 
                WebUI::Execute(RESET_ALL);
                WebUI::Execute(DISABLE_FORM);
            }
        }
    }
}