// Libraries required
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <map>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool Initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

// Logging the message in Chat History of the server
void LogMessage(const string &message) {
    ofstream logFile("chat_history.txt", ios::app);
    if (logFile.is_open()) {
        logFile << message << endl;
        logFile.close();
    }
}

// Gets input from the client and sends the message
void HandleClient(SOCKET clientSocket, map<string, SOCKET> &clients, const string &clientName) {
    char buffer[4096];
    int bytesReceived;
    string message;

    while (true) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << clientName << " disconnected..." << endl;
            break;
        }
        message = string(buffer, bytesReceived);

        if (message == "Exit") {
            cout << "Exiting..." << endl;
            break;
        }

        LogMessage(clientName + ": " + message);
        if (message.substr(0, 2) == "To") {
            size_t spacePos = message.find(' ', 3);
            if (spacePos != std::string::npos) {
                string recipientName = message.substr(3, spacePos - 3);
                string directMessage = message.substr(spacePos + 1);
                directMessage = clientName + ": " + directMessage;

                if (clients.find(recipientName) != clients.end()) {
                    send(clients[recipientName], directMessage.c_str(), directMessage.length(), 0);
                }else {
                    cout << "Recipient not on server..." << endl;
                }
            } else {
                LogMessage("Invalid direct message format: " + message);
            }
        } else {
            LogMessage("Invalid message format: " + message);
        }
    }

    closesocket(clientSocket);
    clients.erase(clientName);
}

int main() {
    if (!Initialize()) {
        cout << "Initialization failed..." << endl;
        return 1;
    }

    // Creates socket for listening
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        cout << "Socket creation failed..." << endl;
        return 1;
    }

    // Setting up the server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Binding the socket to address
    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Binding failed..." << endl;
        return 1;
    }

    // Listening from the socket
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listening failed..." << endl;
        return 1;
    }

    cout << "Server started listening on port 12345" << endl;

    map<string, SOCKET> clients;

    // Accepts the clients and creates a client socket for each of them
    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Client connection failed..." << endl;
            continue;
        }

        char buffer[4096];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        string clientName = string(buffer, bytesReceived);

        cout << clientName << "connected..." << endl;

        clients[clientName] = clientSocket;
        thread clientThread(HandleClient, clientSocket, ref(clients), clientName);
        clientThread.detach();
    }

    // Closing the listening socket and cleaning up
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
