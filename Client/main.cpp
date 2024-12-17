// Importing required libraries
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <fstream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool Initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

// Logging the message in chat history of the client
void LogMessage(const string &message) {
    ofstream logFile("chat_history.txt", ios::app);
    if (logFile.is_open()) {
        logFile << message << endl;
    }
}

// Allows to send message from the client to server
void SendMsg(SOCKET s) {
    cout << "Enter your chat name: ";
    string name;
    getline(cin, name);

    send(s, name.c_str(), name.length(), 0);

    while (true) {
        string message;
        getline(cin, message);

        if (message == "Exit") {
            send(s, message.c_str(), message.length(), 0);
            break;
        }

        if (message.find("To") == 0) {
            send(s, message.c_str(), message.length(), 0);
            LogMessage("Sent " + message);
        } else {
            LogMessage("Sent to server: " + message);
        }
    }

    closesocket(s);
}

// Recieves message from the server
void ReceiveMsg(SOCKET s) {
    char buffer[4096];
    int recvLength;
    
    while (true) {
        recvLength = recv(s, buffer, sizeof(buffer), 0);
        if (recvLength <= 0) {
            cout << "Disconnected from server" << endl;
            break;
        }
        string message(buffer, recvLength);
        cout << message << endl;
        LogMessage("Received from " + message);
    }
}

int main() {
    if (!Initialize()) {
        cout << "Initialization failed..." << endl;
        return 1;
    }

    // Creates socket for client
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Socket creation failed..." << endl;
        return 1;
    }

    // Setting up server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // Connecting the server address and client socket
    if (connect(s, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection failed..." << endl;
        return 1;
    }

    cout << "Successfully connected to server" << endl;

    // Creating threads for sending and recieving
    thread senderThread(SendMsg, s);
    thread receiverThread(ReceiveMsg, s);

    senderThread.join();
    receiverThread.join();

    return 0;
}
