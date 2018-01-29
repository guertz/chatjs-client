#include <iostream>
#include <string>
#include <map>
#include <json.hpp>

#include "env.h"
#include "chat-details.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"

#include "states/chat-state/chat-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;

extern char _binary_src_pages_chat_details_chat_details_js_start[];

namespace ChatDetails {
    const unsigned int MESSAGES = 10;

    const string CHAT_INACTIVE = "alert('Deve prima essere selezionata una chat')";

    const string ENABLE_FORM  = "components.ChatDetails.enable()";
    const string DISABLE_FORM = "components.ChatDetails.disable()";

    void Bootstrap(){

        WebUI::Execute(
                safeptr::parse_asset(
                    _binary_src_pages_chat_details_chat_details_js_start)
            );

        WebUI::Register("ChatDetails::Submit", Events::Submit);

        ChatState::ChatMethods::Register("ChatDetails", State::Chat);

    }

    namespace Events {

        void Submit(const string& args){

            json form_args = json::parse(args);
            ChatState::ChatMethods::SendAMessage(form_args.at("text").get<string>());

        }
    }

    namespace State {
        void Chat(){
            
            const string js_chat = "components.ChatDetails.populateChatDetails('" +
                                        ChatState::ChatsMethods::getCurrentChat() +
                                    "')";

            WebUI::Execute(js_chat);
            WebUI::Execute(ENABLE_FORM);

        }
    }
}