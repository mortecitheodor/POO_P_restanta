#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <msclr/marshal.h>
#include "UserConnectInterface.h"
#include "Register.h"
#include "Main.h"

using namespace System;
using namespace System::Net;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_PORT "27018"

[STAThread]
int main(array <String^>^ args) {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    addrinfo* result = nullptr;
    addrinfo* ptr = nullptr;
    addrinfo hints{};
    const char* sendbuf = "test_message";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    if (args->Length != 2) {
        Console::WriteLine("usage: {0} server-name", args[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        Console::WriteLine("WSAStartup failed with error: {0}", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    IntPtr ptrHostname = Marshal::StringToHGlobalAnsi(args[1]);
    iResult = getaddrinfo(static_cast<const char*>(ptrHostname.ToPointer()), DEFAULT_PORT, &hints, &result);
    Marshal::FreeHGlobal(ptrHostname);

    if (iResult != 0) {
        Console::WriteLine("getaddrinfo failed with error: {0}", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            Console::WriteLine("socket failed with error: {0}", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        else {
            Console::WriteLine("Socket created successfully.");
            Console::WriteLine("Family: {0}", ptr->ai_family);
            Console::WriteLine("Socket type: {0}", ptr->ai_socktype);
            Console::WriteLine("Protocol: {0}", ptr->ai_protocol);
        }


        // Connect to the server
        iResult = connect(ConnectSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        Console::WriteLine("Unable to connect to the server!");
        WSACleanup();
        return 1;
    }

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    User^ user = gcnew User();
    while (true) {
        POOP::UserConnectInterface^ loginF = gcnew POOP::UserConnectInterface(ConnectSocket);
        loginF->ShowDialog();
        if(loginF->exitVal == 1) {
            closesocket(ConnectSocket);
            WSACleanup();
            return 0;
        }
        if (loginF->switchToMain) {//se logheaza
            user = loginF->user;
            POOP::Main^ mainForm = gcnew POOP::Main(user, ConnectSocket);
            mainForm->ShowDialog();

            if (mainForm->switchToLogin == 1 && mainForm->exitVal == 0) {
                continue;
            }
            else if (mainForm->exitVal == 1 && mainForm->switchToLogin == 0) {
                closesocket(ConnectSocket);
                WSACleanup();
                return 0;
            }
        }
        else if (loginF->switchToRegister) {
            POOP::Register^ registerForm = gcnew POOP::Register(ConnectSocket);
            registerForm->ShowDialog();

            if (registerForm->switchToLogin == 1 && registerForm->exitVal == 0) {
                continue;
            }
            else if (registerForm->exitVal == 1 && registerForm->switchToLogin == 0) {
                closesocket(ConnectSocket);
                WSACleanup();
                return 0;
            }
        }
    }
    
    if (iResult == SOCKET_ERROR) {
        Console::WriteLine("send failed with error: {0}", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    Console::WriteLine("Bytes Sent: {0}", iResult);

    // Shutdown the connection for sending
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        Console::WriteLine("shutdown failed with error: {0}", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    } while (iResult > 0);

    // Cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}