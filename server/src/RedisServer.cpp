#include "../include/RedisServer.h"

static RedisServer* globalServer = NULL;
RedisServer::RedisServer(int port) : port(port),serverSocket(-1), running(true){
    globalServer=this;
}

void RedisServer::shutdown(){
    running=false;
    if(serverSocket!=-1){
        close(serverSocket);
    }
    cout<<"Server shutdown complete"<<endl;
}

void RedisServer::run(){
    serverSocket=socket(AF_INET,SOCK_STREAM,0); //AF_INET is ipv4 protocol, SOCK_STREAM is tcp socket, 0 uses tcp as default protocol
    if(serverSocket<0){
        cerr<<"Error creating server socket"<<endl;   
        return;
    }

    sockaddr_in serverAddress; //to store address of the socket
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port); //Converts port to network byte order.
    serverAddress.sin_addr.s_addr = INADDR_ANY; //Accept connections on any IP.


    //bind associates socket with configured port and ip address
    if(bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        cerr<<"Error Binding Server Socket"<<endl;
        return;
    }

    //allows 10 queued connections
    if(listen(serverSocket,10)<0){
        cerr<<"Error listening to server socket"<<endl;
    }

    cout<<"Redis server listening on port"<<port<<endl;


}