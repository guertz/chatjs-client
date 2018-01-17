#include <iostream>
#include <string>
#include <map>
#include <json.hpp>

#include "chat-details.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"

#include "providers/chats/chats.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

namespace ChatDetails {
    const unsigned int MESSAGES = 10;
    static char* chatStatus = safestr::duplicate("{ \"ready\": false, \"selected\": \"undefined\", \"last-message\": \"undefined\" }");

    void Bootstrap(){
        WebUI::Register("ChatDetails::Submit", Events::Submit);

        const char* BUNDLE = js::compact(80, 1, "components.ChatDetails.disableInput()");

        ChatState::Chat::Register("ChatDetails::RefreshChats", Chat::State);

        webview_dispatch(   WebUI::GetContext(), 
                            WebUI::Dispatch, 
                            safeptr::serialize(safestr::duplicate(BUNDLE))
                        );

        safeptr::free_block(BUNDLE);
    }

    namespace Events {
        void Refresh(){

            json jChatStatus = json::parse(chatStatus);

            if(strcmp(jChatStatus["selected"].get<string>().c_str(), "undefined") != 0){

                const chat_details chat = ChatState::Chat::Get(safestr::duplicate(jChatStatus["selected"].get<string>().c_str()));

                unsigned int counter = 0;

                json jWrapper = R"(
                    {
                        "_reference": "fakecontent",
                        "messages": "[]"
                    }
                )"_json;

                ostringstream oss;
                oss<<"[";
                    
                typo_chat::const_reverse_iterator _r_it = chat.messages.rbegin();

                while(_r_it != chat.messages.rend() && counter < MESSAGES){
                    cout<<"\n Looping: "<<counter<<endl;
                    // build json data from this content

                    const message_block msgx = _r_it->second;

                    json tmpMsg;
                        tmpMsg["isMe"] = msgx.isMe;
                        tmpMsg["avatar"] = msgx.avatar; // duplicate is better here?
                        tmpMsg["content"] = msgx.content;
                        tmpMsg["time"] = msgx.time;

                    oss<<tmpMsg.dump();

                    jChatStatus["last-message"] = safestr::duplicate(_r_it->first.c_str());

                    _r_it++;
                    counter++;

                    if(_r_it != chat.messages.rend() && counter < MESSAGES)
                        oss<<",";
                }

                oss<<"]";

                jWrapper["_reference"] = jChatStatus["selected"].get<string>();
                jWrapper["messages"] = json::parse(oss.str());

                const char* JS_SERIALIZED = safestr::duplicate(jWrapper.dump().c_str());
                const char* JS_PUSH_CHAT = js::compact(50 + strlen(JS_SERIALIZED), 3, "components.ChatDetails.refreshAChat('",  JS_SERIALIZED ,"')");

                webview_dispatch(
                    WebUI::GetContext(),
                    WebUI::Dispatch,
                    safeptr::serialize(safestr::duplicate(JS_PUSH_CHAT))
                );

                safeptr::free_block(chatStatus);
                chatStatus = safestr::duplicate(jChatStatus.dump().c_str());

                safeptr::free_block(JS_PUSH_CHAT);
                safeptr::free_block(JS_SERIALIZED);
            }
        }

        void OpenChat(const char* args){
            const char* BUNDLE = js::compact(80, 1, "components.ChatDetails.enableInput()");

            json jChatInput = json::parse(args);
            
            json jChatStatus = json::parse(chatStatus);

                jChatStatus["selected"] = jChatInput.at("ref");
                jChatStatus["last-message"] = "undefined";

            chatStatus = safestr::duplicate(jChatStatus.dump().c_str());

            Chat::State(safestr::duplicate(""));

            webview_dispatch(   WebUI::GetContext(), 
                                WebUI::Dispatch, 
                                safeptr::serialize(safestr::duplicate(BUNDLE))
                            );

            safeptr::free_block(BUNDLE);
        }

        void Submit(const char* args){

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

            ChatState::Chat::SendAMessage(safestr::duplicate(jExtern.dump().c_str()));

            safeptr::free_block(args);
        }
    }

    namespace Chat {
        void State(const char* emptyJson){
            // Provare con una stringa che magari non dipende dalle altre
            json jChatStatus = json::parse(safestr::duplicate(chatStatus));

            cout<<"## Post parse json"<<endl;

            // if( jChatStatus["ready"].get<bool>()){

                cout<<"## Ready"<<endl;
                if(strcmp(jChatStatus["selected"].get<string>().c_str(), "undefined") != 0){
                    cout<<"## Valid"<<endl;
                    Events::Refresh();
                }        

            // }

            safeptr::free_block(emptyJson);
        }
    }
}