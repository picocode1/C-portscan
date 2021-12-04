#include<stdio.h>    
#include<winsock2.h>
#include <stdbool.h>
#pragma comment(lib, "ws2_32.lib"); //To link the winsock library  

bool Scan(char ip[32], int port) {
	WSADATA version;
	SOCKADDR_IN addr;
	SOCKET mySocket;
    
	int iResult = WSAStartup(MAKEWORD(2,2), &version);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);

	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR){
        closesocket(mySocket);
        WSACleanup();
        return false; //Failed to connect.
    }
    else
    {
        return true; //Connected
    }
} 

int main() {
    char ip[] = "127.0.0.1";
    int port = 1234;
    int result = Scan(ip, port);

    if (result) return printf("Success! %s:%d is alive.", ip, port);

    printf("Failed! %s:%d is dead.", ip, port);
    return 0;
}
