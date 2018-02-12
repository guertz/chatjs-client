#ifndef MODELS_SOCKET_CHAT_CHAT_H
#define MODELS_SOCKET_CHAT_CHAT_H

namespace ChatSocket {

    enum SIGNAL {
        JOIN    = 0,
        SEND    = 1,
        ALL     = 2
    };

    SIGNAL str_to_enum(const std::string& action);
    std::string enum_to_str(const SIGNAL  action);

    class Request : public JsonItem {

        public:
            SIGNAL  type;
            std::string text;

            Request();
            Request(const nlohmann::json& j);
            Request(const std::string& serialized);

            nlohmann::json to_json() const;

    };
    
    class Response : public JsonItem {

        public:
            SIGNAL  type;
            std::string ref;
            std::string text;
            std::string time;
            bool isMe;
            User avatar;

            Response();
            Response(const nlohmann::json& j);
            Response(const std::string& serialized);

            nlohmann::json to_json() const;

    };
}


#endif