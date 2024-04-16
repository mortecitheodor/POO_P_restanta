#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "User.h"
#include <json/json.h>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>

int nrClienti = 0;

using namespace System::Data;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Windows::Forms;
using namespace System::Data::SqlClient;
using namespace System::Text;
using SocketEmailPair = std::pair<SOCKET, std::string>;

std::vector<SocketEmailPair> Clienti_Conectati;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
char recvbuf[2000] = "";

int Verify(User^% user, std::string mail, std::string password);

std::vector<std::string> GetUserFilesFromDatabase(int userId) {
    std::vector<std::string> fileList;

    // Initialize the connection string
    String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";

    // Create a SqlConnection using the connection string
    SqlConnection^ sqlConn = gcnew SqlConnection(connString);

    try {
        // Open the connection
        sqlConn->Open();

        // Prepare the SQL command
        String^ sqlQuery = "SELECT filename FROM Files WHERE user_id = @userId";
        SqlCommand^ command = gcnew SqlCommand(sqlQuery, sqlConn);

        // Add the user ID parameter to the command
        command->Parameters->AddWithValue("@userId", userId);

        // Execute the command and receive the data
        SqlDataReader^ reader = command->ExecuteReader();

        // Read each row in the result set
        while (reader->Read()) {
            // Get the filename from the current row
            String^ filename = reader->GetString(0);

            // Add the filename to the fileList
            fileList.push_back(msclr::interop::marshal_as<std::string>(filename));
        }

        // Close the reader when done
        reader->Close();
    }
    catch (Exception^ e) {
        // Handle any exceptions that occur
        Console::WriteLine("An error occurred: " + e->Message);
    }
    finally {
        // Ensure the connection is closed even if an error occurs
        if (sqlConn->State == ConnectionState::Open) {
            sqlConn->Close();
        }
    }

    return fileList;
}

DWORD WINAPI ProcessClient(LPVOID lpParameter)
{
    SOCKET AcceptSocket = (SOCKET)lpParameter;
    // Send and receive data.
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    int verificare = 0;
    do {
        // Receive a message from the client
        ZeroMemory(recvbuf, sizeof(recvbuf));//seteaza un bloc de memorie pe 0
        int bytesReceived = recv(AcceptSocket, recvbuf, DEFAULT_BUFLEN, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            Clienti_Conectati.pop_back();
            WSACleanup();
            return 0;
        }
        else if (bytesReceived == 0)
        {
            // Clientul a inchis conexiunea
            printf("Client disconnected\n");
            break;
        }
        array<Byte>^ byteData = gcnew array<Byte>(bytesReceived);
        Marshal::Copy(IntPtr((void*)recvbuf), byteData, 0, bytesReceived);
        String^ receivedData = Encoding::ASCII->GetString(byteData);
        Console::WriteLine("Received Data: " + receivedData);

        Json::Value jsonData;
        Json::Reader jsonReader;
        if (!jsonReader.parse(msclr::interop::marshal_as<std::string>(receivedData), jsonData))
        {
            printf("Failed to parse JSON data\n");
            return 0;
        }
        std::string operatiune = jsonData["operatiune"].asString();
        std::cout<<operatiune;
        std::string email;
        std::string password;
        if (operatiune == "login")
        {
            email = jsonData["mail"].asString();
            password = jsonData["password"].asString();
            //verificare cont in baza de date
            std::cout << "pass: " << password << std::endl;
            std::cout << "mail: " << email << std::endl;
            User^ user = gcnew User;
            verificare = Verify(user, email, password);
            printf("verify=%d\n", verificare);
            if (send(AcceptSocket, reinterpret_cast<char*>(&verificare), sizeof(verificare), 0) == SOCKET_ERROR) {
                std::cerr << "Eroare la conexiunea cu baza de date!" << std::endl;
            }
            else {
                std::cout << "Data sent successfully: " << verificare << std::endl;
            }
            if (verificare == 1)
            {
                Clienti_Conectati.emplace_back(AcceptSocket, email);
                //informatii despre socket
                char ipAddress[INET_ADDRSTRLEN];
                sockaddr_in socketAddress;
                int addressLength = sizeof(socketAddress);

                //adresa IP si port
                if (getpeername(AcceptSocket, (sockaddr*)&socketAddress, &addressLength) == 0) {
                    inet_ntop(AF_INET, &(socketAddress.sin_addr), ipAddress, INET_ADDRSTRLEN);
                    unsigned short port = ntohs(socketAddress.sin_port);

                    //informatiile in consola
                    std::cout << "Adresa IP: " << ipAddress << std::endl;
                    std::cout << "Portul: " << port << std::endl;
                }
                else {
                    std::cerr << "Eroare la obtinerea informatiilor despre socket." << std::endl;
                }

                // Utilizatorul este verificat, acum obtinem lista de fisiere
                std::vector<std::string> fileList = GetUserFilesFromDatabase(user->id);
                Json::Value response;
                response["operatiune"] = "lista";
                for (const auto& fileName : fileList)
                {
                    response["fisiere"].append(fileName);
                }

                // Convert the JSON object to a styled string
                std::string responseString = response.toStyledString();

                // Convert the string to bytes for sending
                array<Byte>^ responseBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(responseString));
                pin_ptr<unsigned char> pinnedResponseData = &responseBytes[0];
                int responseDataLength = responseBytes->Length;

                // Send the JSON string to the server
                int bytesSentResponse = send(AcceptSocket, reinterpret_cast<char*>(pinnedResponseData), responseDataLength, 0);

                // Check if the data was sent successfully
                if (bytesSentResponse == SOCKET_ERROR)
                {
                    // Handle the error
                    Console::WriteLine("Error sending file list.");
                }
                else {
                    Console::WriteLine("File list sent successfully.");
                }
                // load in form
                //bytesReceived = recv(AcceptSocket, recvbuf, DEFAULT_BUFLEN, 0);
            }
        }
        else if (operatiune == "register")
        {
            std::string email = jsonData["mail"].asString();
            System::String^ mail = gcnew System::String(email.c_str());

            std::string password = jsonData["password"].asString();
            System::String^ parola = gcnew System::String(password.c_str());

            std::string name = jsonData["name"].asString();
            System::String^ nume = gcnew System::String(name.c_str());

            String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection sqlConn(connString);
            sqlConn.Open();

            String^ checkEmailQuery = "SELECT COUNT(*) FROM dbo.[user] WHERE email = @email";
            SqlCommand checkEmailCommand(checkEmailQuery, % sqlConn);
            checkEmailCommand.Parameters->AddWithValue("@email", mail);

            int emailCount = (int)checkEmailCommand.ExecuteScalar();

            int inregistrare;

            if (emailCount > 0)
            {
                // Adresa de email exista deja în baza de date
                inregistrare = 0;
            }
            else
            {
                // Adresa de email nu exista, se poate adauga noul utilizator
                String^ sqlQuery = "INSERT INTO dbo.[user] " +
                    "(name, email, password) VALUES " +
                    "(@name, @email, @password);";

                SqlCommand command(sqlQuery, % sqlConn);
                command.Parameters->AddWithValue("@name", nume);
                command.Parameters->AddWithValue("@email", mail);
                command.Parameters->AddWithValue("@password", parola);

                command.ExecuteNonQuery();
                inregistrare = 1;
            }

            if (send(AcceptSocket, reinterpret_cast<char*>(&inregistrare), sizeof(inregistrare), 0) == SOCKET_ERROR)
            {
                std::cerr << "Failed to send data" << std::endl;
            }
            else
            {
                if (inregistrare == 1)
                {
                    std::cout << "Register successful!\n Data sent successfully: " << inregistrare << std::endl;
                }
                else
                {
                    std::cout << "Email already exists. Registration failed.\n Data sent successfully: " << inregistrare << std::endl;
                }
            }
        }
        else if (operatiune == "logout") {
            auto it = std::find_if(Clienti_Conectati.begin(), Clienti_Conectati.end(),
                [AcceptSocket](const SocketEmailPair& pair) {
                    return pair.first == AcceptSocket;
                });
            if (it != Clienti_Conectati.end()) {
                Clienti_Conectati.erase(it);
            }
            verificare = 0;
            continue;
        } 
        else if (operatiune == "share") {
            email = jsonData["email"].asString();
            std::cout << std::endl;
            std::cout << "Email pentru partajare: " << email << std::endl;

            String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection sqlConn(gcnew String(connString));
            sqlConn.Open();
            String^ query = "SELECT COUNT(*) FROM dbo.[user] WHERE email = @mail";
            SqlCommand^ command = gcnew SqlCommand(query, % sqlConn);
            command->Parameters->AddWithValue("@mail", gcnew String(email.c_str()));

            int userExists = (int)command->ExecuteScalar();
            sqlConn.Close();

            Json::Value response;
            response["shareback"] = userExists > 0 ? 1 : 0;
            std::cout << userExists;
            std::string responseString = response.toStyledString();

            array<Byte>^ responseBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(responseString));
            pin_ptr<Byte> pinnedData = &responseBytes[0];
            send(AcceptSocket, reinterpret_cast<char*>(pinnedData), responseBytes->Length, 0);
            
        }

    } while (1);
        
    auto it = std::find_if(Clienti_Conectati.begin(), Clienti_Conectati.end(),
        [AcceptSocket](const SocketEmailPair& pair) {
            return pair.first == AcceptSocket;
        });
    if (it != Clienti_Conectati.end()) {
        Clienti_Conectati.erase(it);
    }

    closesocket(AcceptSocket);
    return 0;
}

int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET AcceptSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    std::cout << "Waiting for connection..." << std::endl;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address a-nd port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // Setup the TCP listening socket
    bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    freeaddrinfo(result);

    listen(ListenSocket, SOMAXCONN);
    // Accept a client socket
    for (nrClienti = 1; 1; nrClienti++)
    {
        AcceptSocket = SOCKET_ERROR;

        while (AcceptSocket == SOCKET_ERROR)
        {
            //ast conexiuni pana gaseste una valida
            AcceptSocket = accept(ListenSocket, NULL, NULL);
        }
        printf("Client Connected.\n");

        DWORD dwThreadId;
        CreateThread(NULL, 0, ProcessClient, (LPVOID)AcceptSocket, 0, &dwThreadId);
    }

    //No longer need the listening socket
    closesocket(ListenSocket);
    
    // shutdown the connection since we're done
    shutdown(AcceptSocket, SD_SEND);

    WSACleanup();

    return 0;
}

int Verify(User^% user, std::string mail, std::string password) {
    if (mail.empty() || password.empty()) {
        return -1;
    }
    try {
        String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
        SqlConnection sqlConn(gcnew String(connString));
        sqlConn.Open();

        // Retrieve the user from the database for the given email
        String^ sqlQuery = "SELECT id, name, email, password FROM dbo.[user] WHERE email=@mail;";
        SqlCommand command(sqlQuery, % sqlConn);

        command.Parameters->Add("@mail", SqlDbType::NVarChar, 50)->Value = gcnew String(mail.c_str());

        SqlDataReader^ reader = command.ExecuteReader();

        bool userFound = false;
        while (reader->Read()) {
            String^ storedPassword = reader->GetString(3); // Assuming the password is in the fourth column
            String^ recpass = gcnew String(password.c_str());

            // Compare the stored hashed password with the hashed version of the input password
            if (storedPassword == recpass) {
                user->id = reader->GetInt32(0);
                user->name = reader->GetString(1);
                user->email = reader->GetString(2);
                user->password = storedPassword;

                Console::WriteLine("User ID: " + user->id);
                Console::WriteLine("Name: " + user->name);
                Console::WriteLine("Email: " + user->email);
                Console::WriteLine("Password: " + user->password);

                Console::WriteLine("Utilizator gasit in baza de date!");
                userFound = true;
                break; // Exit the loop after finding the user
            }
        }

        reader->Close(); // Close the SqlDataReader
        sqlConn.Close(); // Close the SqlConnection

        if (userFound) {
            return 1;
        }
        else {
            Console::WriteLine("Email or password is incorrect!");
            return 0;
        }
    }
    catch (Exception^ e) {
        Console::WriteLine("Exception: " + e->Message);
        return 0;
    }
}
