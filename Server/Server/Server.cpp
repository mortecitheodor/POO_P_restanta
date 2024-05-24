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
#include <vcclr.h>
#include <fstream>
#include <json/reader.h>

int nrClienti = 0;

public ref class DatabaseConfig {
public:
    static initonly String^ ConnString = "Data Source=DESKTOP-OIGQPEQ;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
};

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
#define DEFAULT_PORT "27018"
char recvbuf[1048576] = "";

int Verify(User^% user, std::string mail, std::string password);

std::vector<std::string> GetUserFilesFromDatabase(int userId) {
    std::vector<std::string> fileList;

    // Create a SqlConnection using the connection string
    SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);

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
    //get user's shared files with him
    try {
        // Deschide conexiunea
        sqlConn->Open();

        // Interogare SQL pentru a selecta numele fisierelor din tabela Files care sunt partajate cu user_id-ul dat
        String^ sqlQuery = "SELECT Files.filename FROM Files "
            "INNER JOIN FileShare ON Files.id = FileShare.file_id "
            "WHERE (FileShare.shared_user_id = @userId)";

        // Comanda SQL
        SqlCommand^ command = gcnew SqlCommand(sqlQuery, sqlConn);

        // Adaugă parametrul userId la comandă
        command->Parameters->AddWithValue("@userId", userId);

        // Execută comanda și obține rezultatele
        SqlDataReader^ reader = command->ExecuteReader();

        // Citirea rezultatelor
        while (reader->Read()) {
            // Obțineți numele fișierului din rezultatul interogării
            String^ filename = reader->GetString(0);

            // Adăugați numele fișierului la fileList
            fileList.push_back(msclr::interop::marshal_as<std::string>(filename));
        }

        // Închideți conexiunea și eliberați resursele
        sqlConn->Close();
    }
    catch (SqlException^ ex) {
        // Gestionarea excepțiilor SQL
        // ex->Message conține mesajul de eroare
    }
    catch (Exception^ ex) {
        // Gestionarea altor excepții
        // ex->Message conține mesajul de eroare
    }

    return fileList;
}

// get user's file based on his email
std::vector<std::string> GetUserFilesFromDatabase(const std::string& userEmail) {
    std::vector<std::string> fileList;

    // Initialize the connection string
    //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
    // Create a SqlConnection using the connection string
    SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);

    try {
        // Open the connection
        sqlConn->Open();

        // Prepare the SQL command
        String^ sqlQuery = "SELECT filename FROM Files WHERE user_id = (SELECT id FROM Users WHERE email = @userEmail)";
        SqlCommand^ command = gcnew SqlCommand(sqlQuery, sqlConn);

        // Add the email parameter to the command
        command->Parameters->AddWithValue("@userEmail", msclr::interop::marshal_as<String^>(userEmail));

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

    // Get user's shared files with him
    try {
        // Open the connection
        sqlConn->Open();

        // SQL query to select filenames from the Files table that are shared with the given user email
        String^ sqlQuery = "SELECT Files.filename FROM Files "
            "INNER JOIN FileShare ON Files.id = FileShare.file_id "
            "WHERE FileShare.shared_user_id = (SELECT id FROM Users WHERE email = @userEmail)";

        // SQL command
        SqlCommand^ command = gcnew SqlCommand(sqlQuery, sqlConn);

        // Add the email parameter to the command
        command->Parameters->AddWithValue("@userEmail", msclr::interop::marshal_as<String^>(userEmail));

        // Execute the command and get the results
        SqlDataReader^ reader = command->ExecuteReader();

        // Read the results
        while (reader->Read()) {
            // Get the filename from the query result
            String^ filename = reader->GetString(0);

            // Add the filename to fileList
            fileList.push_back(msclr::interop::marshal_as<std::string>(filename));
        }

        // Close the reader and release resources
        reader->Close();
    }
    catch (SqlException^ ex) {
        // Handle SQL exceptions
        Console::WriteLine("A SQL error occurred: " + ex->Message);
    }
    catch (Exception^ ex) {
        // Handle other exceptions
        Console::WriteLine("An error occurred: " + ex->Message);
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
        std::cout << operatiune;
        std::string email;
        std::string password;
        std::string file;
        std::string file_content;
        std::string owner_email;
        std::string shared_email;
        std::string files_location = "D:\\proiect_POO\\POO_P_restanta-adrian\\ServerFiles";

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

            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection sqlConn(DatabaseConfig::ConnString);
            sqlConn.Open();

            String^ checkEmailQuery = "SELECT COUNT(*) FROM dbo.[users] WHERE email = @email";
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
                String^ sqlQuery = "INSERT INTO dbo.[users] " +
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
            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection sqlConn(gcnew String(DatabaseConfig::ConnString));
            sqlConn.Open();
            String^ query = "SELECT COUNT(*) FROM dbo.[users] WHERE email = @mail";
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
        else if (operatiune == "delete_file") {
            std::string filename = jsonData["filename"].asString();
            std::string userEmail = jsonData["email"].asString();
            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);
            int deleteResult = 0;

            try {
                sqlConn->Open();

                // Check if the user is the owner of the file
                String^ sqlQueryCheckOwner =
                    "SELECT COUNT(*) FROM Files "
                    "WHERE filename = @filename AND user_id = (SELECT id FROM dbo.[users] WHERE email = @userEmail)";

                SqlCommand^ commandCheckOwner = gcnew SqlCommand(sqlQueryCheckOwner, sqlConn);
                commandCheckOwner->Parameters->AddWithValue("@filename", gcnew String(filename.c_str()));
                commandCheckOwner->Parameters->AddWithValue("@userEmail", gcnew String(userEmail.c_str()));

                int isOwner = (int)commandCheckOwner->ExecuteScalar();

                if (isOwner > 0) {
                    // User is the owner, proceed to delete the file and related shares
                    std::cout << "Utilizatorul este proprietarul fisierului. Se procedeaza la stergerea fisierului si a inregistrarilor partajate." << std::endl;
                    std::string full_path = files_location + "\\" + filename + ".rtf";

                    if (std::remove(full_path.c_str()) == 0) {
                        std::cout << "Fisierul a fost sters cu succes de pe server." << std::endl;
                    }
                    else {
                        std::cerr << "Fisierul nu a fost gasit sau nu a putut fi sters." << std::endl;
                    }

                    String^ sqlQueryDeleteShares = "DELETE FROM FileShare WHERE file_id = (SELECT id FROM Files WHERE filename = @filename)";
                    SqlCommand^ commandDeleteShares = gcnew SqlCommand(sqlQueryDeleteShares, sqlConn);
                    commandDeleteShares->Parameters->AddWithValue("@filename", gcnew String(filename.c_str()));
                    commandDeleteShares->ExecuteNonQuery();

                    String^ sqlQueryDeleteFile = "DELETE FROM Files WHERE filename = @filename AND user_id = (SELECT id FROM dbo.[users] WHERE email = @userEmail)";
                    SqlCommand^ commandDeleteFile = gcnew SqlCommand(sqlQueryDeleteFile, sqlConn);
                    commandDeleteFile->Parameters->AddWithValue("@filename", gcnew String(filename.c_str()));
                    commandDeleteFile->Parameters->AddWithValue("@userEmail", gcnew String(userEmail.c_str()));
                    commandDeleteFile->ExecuteNonQuery();

                    deleteResult = 1; // File and related shares deleted successfully
                }
            }
            catch (Exception^ e) {
                Console::WriteLine("A aparut o eroare: " + e->Message);
            }
            finally {
                if (sqlConn->State == ConnectionState::Open) {
                    sqlConn->Close();
                }
            }

            send(AcceptSocket, reinterpret_cast<char*>(&deleteResult), sizeof(deleteResult), 0);
        }
        else if (operatiune == "requested_file") {

            file = jsonData["nume_fisier"].asString();

            // Conectează-te la baza de date și caută calea completă a fișierului
            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);

            String^ filepath;
            try {
                // Deschide conexiunea la baza de date
                sqlConn->Open();

                // Pregătește interogarea SQL
                String^ sqlQuery = "SELECT filepath FROM Files WHERE filename = @filename";
                SqlCommand^ command = gcnew SqlCommand(sqlQuery, sqlConn);
                command->Parameters->AddWithValue("@filename", gcnew String(file.c_str()));

                // Execută interogarea și citește rezultatele
                SqlDataReader^ reader = command->ExecuteReader();
                if (reader->Read()) {
                    filepath = reader->GetString(0); // Obține calea completă a fișierului
                }
                else {
                    std::cerr << "File not found in database" << std::endl;
                    int fileNotFound = -1;
                    send(AcceptSocket, reinterpret_cast<char*>(&fileNotFound), sizeof(fileNotFound), 0);
                    reader->Close();
                    sqlConn->Close();
                    return -1;
                }

                reader->Close();
                sqlConn->Close();
            }
            catch (Exception^ e) {
                std::cerr << "Database error: " << msclr::interop::marshal_as<std::string>(e->Message) << std::endl;
                int dbError = -1;
                send(AcceptSocket, reinterpret_cast<char*>(&dbError), sizeof(dbError), 0);
                return -1;
            }

            // Adaugă extensia ".rtf" la filepath
            filepath += "\\" + gcnew String(file.c_str()) + ".rtf";

            // Deschide fișierul folosind calea completă
            std::ifstream inFile(msclr::interop::marshal_as<std::string>(filepath));
            if (!inFile) {
                std::cerr << "Unable to open file: " << msclr::interop::marshal_as<std::string>(filepath) << std::endl;
                int fileError = -1;
                send(AcceptSocket, reinterpret_cast<char*>(&fileError), sizeof(fileError), 0);
                return -1;
            }

            // Citește conținutul fișierului
            std::string fileContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

            //inchidem fisierul dupa ce am citit din el
            inFile.close();

            // Trimite conținutul fișierului către client
            Json::Value response;
            response["operatiune"] = "send_file";
            response["file_content"] = fileContent;

            // Convert the JSON object to a string
            std::string responseString = response.toStyledString();

            // Convert the string to bytes for sending
            array<Byte>^ responseBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(responseString));
            pin_ptr<Byte> pinnedResponseData = &responseBytes[0];
            int responseDataLength = responseBytes->Length;

            // Send the JSON string to the client
            int bytesSentResponse = send(AcceptSocket, reinterpret_cast<char*>(pinnedResponseData), responseDataLength, 0);

            // Check if the data was sent successfully
            if (bytesSentResponse == SOCKET_ERROR) {
                std::cerr << std::endl << "Error sending file content." << std::endl;
            }
            else {
                std::cout << std::endl << "File content sent successfully." << std::endl;
            }

        }
        else if (operatiune == "make_share") {

            file = jsonData["shared_file"].asString();
            owner_email = jsonData["owner_email"].asString();
            shared_email = jsonData["shared_email"].asString();
            std::cout << std::endl << "Operatiune: " << operatiune << std::endl << "Owner's Email: " << owner_email << std::endl << "Shared file: " << file << std::endl << "Share with: " << shared_email << std::endl;
            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);

            try {
                sqlConn->Open();

                // Fetch file_id
                String^ sqlQueryFile = "SELECT id FROM Files WHERE filename = @filename";
                SqlCommand^ commandFile = gcnew SqlCommand(sqlQueryFile, sqlConn);
                commandFile->Parameters->AddWithValue("@filename", gcnew String(file.c_str()));
                int file_id = (int)commandFile->ExecuteScalar();

                // Fetch owner_user_id
                String^ sqlQueryOwner = "SELECT id FROM dbo.[users] WHERE email = @owner_email";
                SqlCommand^ commandOwner = gcnew SqlCommand(sqlQueryOwner, sqlConn);
                commandOwner->Parameters->AddWithValue("@owner_email", gcnew String(owner_email.c_str()));
                int owner_user_id = (int)commandOwner->ExecuteScalar();

                // Fetch shared_user_id
                String^ sqlQueryShared = "SELECT id FROM dbo.[users] WHERE email = @shared_email";
                SqlCommand^ commandShared = gcnew SqlCommand(sqlQueryShared, sqlConn);
                commandShared->Parameters->AddWithValue("@shared_email", gcnew String(shared_email.c_str()));
                int shared_user_id = (int)commandShared->ExecuteScalar();

                // Insert into FileShare table
                String^ sqlInsert = "INSERT INTO FileShare (file_id, owner_user_id, shared_user_id) VALUES (@file_id, @owner_user_id, @shared_user_id)";
                SqlCommand^ commandInsert = gcnew SqlCommand(sqlInsert, sqlConn);
                commandInsert->Parameters->AddWithValue("@file_id", file_id);
                commandInsert->Parameters->AddWithValue("@owner_user_id", owner_user_id);
                commandInsert->Parameters->AddWithValue("@shared_user_id", shared_user_id);
                commandInsert->ExecuteNonQuery();

                std::cout << "File shared successfully." << std::endl;
            }
            catch (Exception^ e) {
                Console::WriteLine("An error occurred: " + e->Message);
            }
            finally {
                if (sqlConn->State == ConnectionState::Open) {
                    sqlConn->Close();
                }
            }
        }
        else if (operatiune == "save_existing_file") {
            file = jsonData["file"].asString();
            file_content = jsonData["file_content"].asString();
            file += ".rtf";
            files_location = files_location + "\\" + file;
            bool saveSuccess = true;

            std::ofstream outfile(files_location);

            if (outfile.is_open()) {
                outfile.write(file_content.c_str(), file_content.size());

                outfile.close();
            }
            else {
                std::cerr << "Eroare: Nu se poate deschide fisierul!\n";
                saveSuccess = false;
            }


            // Formează răspunsul
            std::string response = (saveSuccess) ? "1" : "0";

            // Trimite răspunsul la client
            int bytesSent = send(AcceptSocket, response.c_str(), response.size(), 0);
            if (bytesSent == SOCKET_ERROR) {
                std::cerr << "Eroare la trimiterea răspunsului la client.\n";
                // Poți trata eroarea aici, de exemplu, prin închiderea conexiunii sau alte acțiuni necesare
            }

        }
        else if (operatiune == "verifying_file_name") {
            file = jsonData["file"].asString();

            // Convertim std::string la System::String^
            String^ fileStr = gcnew String(file.c_str());

            // Connection string
            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);

            try {
                sqlConn->Open();

                // Query pentru verificarea numelui fișierului
                String^ sqlQueryFile = "SELECT COUNT(*) FROM Files WHERE filename = @filename";
                SqlCommand^ commandFile = gcnew SqlCommand(sqlQueryFile, sqlConn);
                commandFile->Parameters->AddWithValue("@filename", fileStr);

                int count = (int)commandFile->ExecuteScalar();

                if (count > 0) {
                    std::cout << std::endl << "Fisierul exista in baza de date." << std::endl;
                }
                else {
                    std::cout << std::endl << "Fisierul NU exista in baza de date." << std::endl;
                }
                int response = (count > 0) ? 0 : 1;

                // Trimiterea răspunsului înapoi la client
                send(AcceptSocket, (char*)&response, sizeof(response), 0);
            }
            finally {
                if (sqlConn->State == ConnectionState::Open) {
                    sqlConn->Close();
                }
            }


        }
        else if (operatiune == "saving_new_file") {

            file = jsonData["file"].asString();
            file_content = jsonData["content"].asString();
            email = jsonData["email"].asString();

            // Convertim std::string la System::String^
            String^ fileStr = gcnew String(file.c_str());
            String^ fileContentStr = gcnew String(file_content.c_str());
            String^ emailStr = gcnew String(email.c_str());
            String^ fileLocationStr = gcnew String(files_location.c_str());

            // Connection string
            //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
            SqlConnection^ sqlConn = gcnew SqlConnection(DatabaseConfig::ConnString);

            try {
                sqlConn->Open();

                // Obține user_id din tabelul users folosind adresa de email
                String^ sqlQueryUser = "SELECT id FROM dbo.[users] WHERE email = @user_email";
                SqlCommand^ commandUser = gcnew SqlCommand(sqlQueryUser, sqlConn);
                commandUser->Parameters->AddWithValue("@user_email", emailStr);

                int user_id = (int)commandUser->ExecuteScalar();

                // Introduce datele în tabelul Files
                String^ sqlInsertFile = "INSERT INTO Files (filename, filepath, user_id) VALUES (@filename, @filepath, @user_id)";
                SqlCommand^ commandInsertFile = gcnew SqlCommand(sqlInsertFile, sqlConn);
                commandInsertFile->Parameters->AddWithValue("@filename", fileStr);
                commandInsertFile->Parameters->AddWithValue("@filepath", fileLocationStr);
                commandInsertFile->Parameters->AddWithValue("@user_id", user_id);

                commandInsertFile->ExecuteNonQuery();

                std::cout << std::endl << "Datele au fost inserate cu succes in tabel" << std::endl;
            }
            catch (Exception^ ex) {
                std::cout << "A aparut o eroare: " << std::endl;
            }
            finally {
                if (sqlConn->State == ConnectionState::Open) {
                    sqlConn->Close();
                }
            }
            file += ".rtf";
            files_location = files_location + "\\" + file;
            bool saveSuccess = true;

            std::ofstream outfile(files_location);

            if (outfile.is_open()) {
                outfile.write(file_content.c_str(), file_content.size());

                outfile.close();
            }
            else {
                std::cerr << "Eroare: Nu se poate deschide fisierul!\n";
                saveSuccess = false;
            }
        }
        else if (operatiune == "request_list") {
            // Utilizatorul este verificat, acum obtinem lista de fisiere
            email = jsonData["email"].asString();
            std::vector<std::string> fileList = GetUserFilesFromDatabase(email);
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
        //String^ connString = "Data Source=DESKTOP-5AS8UAM\\SQLEXPRESS;Initial Catalog=pooP;Integrated Security=True;Encrypt=True;TrustServerCertificate=True;";
        SqlConnection sqlConn(gcnew String(DatabaseConfig::ConnString));
        sqlConn.Open();

        // Retrieve the user from the database for the given email
        String^ sqlQuery = "SELECT id, name, email, password FROM dbo.[users] WHERE email=@mail;";
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