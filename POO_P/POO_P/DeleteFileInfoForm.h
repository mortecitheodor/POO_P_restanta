#pragma once
#include "User.h"
#include <msclr/marshal_cppstd.h>
#include <string>
#include <json/json.h>

namespace POOP {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class DeleteFileInfoForm : public System::Windows::Forms::Form {
    public:
        SOCKET connectSocket;
        User^ user;

    public:
        DeleteFileInfoForm(User^ user, SOCKET socket) {
            InitializeComponent();
            connectSocket = socket;
            this->user = user;
            this->CenterToScreen();
        }

    protected:
        ~DeleteFileInfoForm() {
            if (components) {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Button^ button1;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->textBox1 = (gcnew System::Windows::Forms::TextBox());
               this->button1 = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->Location = System::Drawing::Point(13, 13);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(54, 13);
               this->label1->TabIndex = 0;
               this->label1->Text = L"Filename:";
               // 
               // textBox1
               // 
               this->textBox1->Location = System::Drawing::Point(74, 10);
               this->textBox1->Name = L"textBox1";
               this->textBox1->Size = System::Drawing::Size(198, 20);
               this->textBox1->TabIndex = 1;
               // 
               // button1
               // 
               this->button1->Location = System::Drawing::Point(197, 36);
               this->button1->Name = L"button1";
               this->button1->Size = System::Drawing::Size(75, 23);
               this->button1->TabIndex = 2;
               this->button1->Text = L"Send";
               this->button1->UseVisualStyleBackColor = true;
               this->button1->Click += gcnew System::EventHandler(this, &DeleteFileInfoForm::button1_Click);
               // 
               // DeleteFileInfoForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(284, 71);
               this->Controls->Add(this->button1);
               this->Controls->Add(this->textBox1);
               this->Controls->Add(this->label1);
               this->Name = L"DeleteFileInfoForm";
               this->Text = L"File Info";
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion
    private:
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
            // Collect data
            msclr::interop::marshal_context context;
            std::string filename = context.marshal_as<std::string>(textBox1->Text);
            std::string userEmail = context.marshal_as<std::string>(user->email);

            // Create JSON object with operation name "delete_file"
            Json::Value root;
            root["operatiune"] = "delete_file"; // Operation name
            root["filename"] = filename;
            root["email"] = userEmail;
            Json::StreamWriterBuilder writer;
            std::string jsonString = Json::writeString(writer, root);

            // Send JSON data to server
            send(connectSocket, jsonString.c_str(), jsonString.size(), 0);

            // Receive the result from the server
            int deleteResult = 0;
            int bytesReceived = recv(connectSocket, reinterpret_cast<char*>(&deleteResult), sizeof(deleteResult), 0);

            if (bytesReceived == sizeof(deleteResult)) {
                if (deleteResult == 1) {
                    MessageBox::Show("File deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    MessageBox::Show("Failed to delete file. You are not the owner or you don't have access.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            else {
                MessageBox::Show("Failed to receive response from server.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }

            this->Close();
        }
    };
}