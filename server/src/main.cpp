#include <bits/stdc++.h>
#include "../include/RedisServer.h"

using namespace std;

int main(int argc,char* argv[]){

    int port=6379; //default port if not given

    if(argc>=2){
        port=stoi(argv[1]);
    }

    RedisServer server(port);

    //Background persistance: dump the db every 5 min
    thread persistanceThread([](){
        while(true){
            this_thread::sleep_for(chrono::seconds(300));
            //dump the db 
        }
    });
    persistanceThread.detach();

    server.run();

    return 0;
}