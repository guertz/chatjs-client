#include <iostream>
#include <string>
#include <map>
#include <json.hpp>

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
    static string chatStatus = "{ \"ready\": false, \"selected\": \"undefined\", \"last-message\": \"undefined\" }";

    void Bootstrap(){

        WebUI::Execute(
                safeptr::parse_asset(
                    _binary_src_pages_chat_details_chat_details_js_start)
            );

        WebUI::Register("ChatDetails::Submit", Events::Submit);

        const string disable_form = "components.ChatDetails.disable()";

        ChatState::Chat::Register("ChatDetails::RefreshChats", Chat::State);

        WebUI::Execute(disable_form);
    }

    namespace Events {
        void Refresh(){

            json jChatStatus = json::parse(chatStatus);

            if(strcmp(jChatStatus["selected"].get<string>().c_str(), "undefined") != 0){

                const ChatState::chat_details chat = ChatState::Chat::Get(jChatStatus["selected"].get<string>());

                unsigned int counter = 0;

                json jWrapper = R"(
                    {
                        "_reference": "fakecontent",
                        "messages": "[]"
                    }
                )"_json;

                ostringstream oss;
                oss<<"[";
                    
                ChatState::typo_chat::const_reverse_iterator _r_it = chat.messages.rbegin();

                while(_r_it != chat.messages.rend() && counter < MESSAGES){

                    const ChatState::message_block msgx = _r_it->second;

                    json tmpMsg;
                        tmpMsg["isMe"] = msgx.isMe;
                        tmpMsg["avatar"] = msgx.avatar; // duplicate is better here?
                        tmpMsg["content"] = msgx.content;
                        tmpMsg["time"] = msgx.time;

                    oss<<tmpMsg.dump();

                    jChatStatus["last-message"] = _r_it->first;

                    _r_it++;
                    counter++;

                    if(_r_it != chat.messages.rend() && counter < MESSAGES)
                        oss<<",";
                }

                oss<<"]";

                jWrapper["_reference"] = jChatStatus["selected"].get<string>();
                jWrapper["messages"]   = json::parse(oss.str());

                const string js_chat = "components.ChatDetails.populate('" +
                                            jWrapper.dump() +
                                        "')";
                                        
                WebUI::Execute(js_chat);

                chatStatus = jChatStatus.dump();

            }
        }

        void OpenChat(const string& args){
            const char* js_enable = "components.ChatDetails.enable()";

            json jChatInput = json::parse(args);
            
            json jChatStatus = json::parse(chatStatus);

                jChatStatus["selected"] = jChatInput.at("ref");
                jChatStatus["last-message"] = "undefined";

            chatStatus = jChatStatus.dump();

            Chat::State();

            WebUI::Execute(js_enable);
        }

        void Submit(const string& args){

            json jChat = json::parse(chatStatus);
            json jArgs = json::parse(args);

            json jExtern = R"(
                {
                    "reference": "fakeref",
                    "text": "faketext"
                }
            )"_json;

            jExtern["reference"] = jChat["selected"].get<string>();
            jExtern["text"] = jArgs.at("text").get<string>();

            ChatState::Chat::SendAMessage(jExtern.dump());

        }
    }

    namespace Chat {
        void State(){
            // Provare con una stringa che magari non dipende dalle altre
            json jChatStatus = json::parse(chatStatus);

            cout<<"## Post parse json"<<endl;

            // if( jChatStatus["ready"].get<bool>()){

                cout<<"## Ready"<<endl;
                if(strcmp(jChatStatus["selected"].get<string>().c_str(), "undefined") != 0){
                    cout<<"## Valid"<<endl;
                    Events::Refresh();
                }        

            // }

        }
    }
}