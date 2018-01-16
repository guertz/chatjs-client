// TODO unify const char* usage

#include "easywsclient.h"
#include "common/helpers/helpers.h"
#include "wscustom.h"

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <signal.h>

using namespace ws;
using namespace Helpers;

unsigned int THREAD_SLEEP = 500;

void handle(const char* arg)
{
    cout<<"Logging socket: "<<arg<<endl;

    safeptr::free_block(arg);
}

void core(struct thread_data& my_data){

    bool sended  = false;

    while (my_data.channel->getReadyState() != WebSocket::CLOSED) {
        my_data.channel->poll(THREAD_SLEEP);

        bool isWriting = (my_data.buffer.size() > 0);

        if(isWriting){

            if(!sended){
                my_data.channel->send(my_data.buffer);
                sended    = true;

            }else{
                // SINGLE means ack or not in here
                if(!my_data.SINGLE){

                    my_data.buffer = "";
                    sended = false;
                    isWriting = false;
                    
                    my_data.channel->dispatch([&my_data](const std::string& socketResponse) {

                        const char* converted = socketResponse.c_str();
                        
                        // client should handle based on the response knowing that the message could be:
                        // 1) ack => message received correctly
                        // 2) close => end of trasmission (EOF)?
                        // 2) whatever else i except to receive

                        my_data.callback(converted);                        

                        if(strcmp(converted, "close") == 0)
                            my_data.channel->close();

                        // NEVER DELETE BLOCKS THAT CAME FROM A LOCAL SPACE (NO DUPLICATION AS WELL)
                        // safeptr::free_block(converted);

                    });
                }else
                    my_data.channel->close();

            }
            

        }else{

            my_data.channel->dispatch([&my_data](const std::string& socketResponse) {
                my_data.callback(safestr::duplicate(socketResponse.c_str()));
            });
            
            if(my_data.SINGLE)
                my_data.channel->close();
        }
    }
    
           // dont know if i did always close it...
    delete my_data.channel;
           my_data.channel = NULL;
           
   
           // flush struct data on complete

           my_data.buffer = "";
           my_data.SINGLE  = false;
           my_data.callback= NULL;

}

void ws::Socket::get(){
    this->get(handle);
}

void ws::Socket::get(void (*fn)(const char* arg)){
    // if(this->tdat.SINGLE){
    //     ws::SocketException read_on_single_thread_error;
    //     throw read_on_single_thread_error; // vs assert?
    // }
    
    // ELSE NOT REACHED IF THROWN EXCEPTION?

    if(this->COMPUTING){
        ws::SocketComputingException computing_exception;
        throw computing_exception; 
    }
    
    this->tdat.callback = fn;
    thread run(core, std::ref(this->tdat));
           run.detach(); 
           
    this->COMPUTING = true;
    this->watcher = &run;
}

// only if channel exists as a pointer!!
void ws::Socket::write(const string &s){
    this->write(s, handle);
}

void ws::Socket::write(const string &s, void (*fn)(const char* arg)){
    cout<<"Bufferizing"<<endl;
    // abortire se stringa vuota passata..
    // if(!this->tdat.SINGLE){
    //     ws::SocketException write_on_multiple_thread_error;
    //     throw write_on_multiple_thread_error; // vs assert?
    // }

    // ELSE NOT REACHED IF THROWN EXCEPTION?

    // if(this->COMPUTING){
        // ws::SocketComputingException computing_exception;
        // throw computing_exception; 
    // }
    
    this->tdat.buffer = s;

    if(!this->COMPUTING){
        this->tdat.callback = fn;

        // prima non andava perch'è l'oggetto moriva
        thread run(core, std::ref(this->tdat));
            run.detach();
            
        this->COMPUTING = true;
        this->watcher = &run;
    }
}

void ws::Socket::set_type(bool t){
    this->stop();
    this->tdat.SINGLE = t;
}

void ws::Socket::stop(){
    
    // ALTRI CASI?
    if(!this->tdat.SINGLE && this->COMPUTING){
        this->tdat.channel->close(); // dereferenziato scorrettamente
        cout<<"THREAD IS NOW stopping";
        this->COMPUTING = false; // questa variabile è meglio settarla quando esce il thread?
                                 // quindi va inserita nella cosa condivisa
                                 // mutex - wait, while loop
    }else
        cout<<"# there should be nothing to stop "<<endl;
}

ws::Socket::Socket(string s){
    this->initZ(s,false);
}
ws::Socket::Socket(string s,bool t){
    this->initZ(s,t);
}

void ws::Socket::initZ(string s, bool t){

    this->COMPUTING = false;
    
    this->tdat.channel = WebSocket::from_url("ws://127.0.0.1:8000/"+s);
    this->tdat.SINGLE = t;
    this->tdat.buffer = "";
    this->tdat.callback = handle;

    // if(!this->tdat.channel)
    // throw error
}

