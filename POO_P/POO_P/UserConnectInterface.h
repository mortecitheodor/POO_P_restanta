#pragma once
#include "User.h"
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <stdio.h>
#include <Windows.h>
#include <json/json.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

namespace POOP {

	using namespace System;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	public ref class UserConnectInterface : public System::Windows::Forms::Form
	{
	public:
		SOCKET connectSocket;
		UserConnectInterface(void)
		{
			InitializeComponent();
		}
		UserConnectInterface(SOCKET socket)
		{
			InitializeComponent();
			connectSocket = socket;
		}

	protected:
		~UserConnectInterface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ signin_label;
	private: System::Windows::Forms::Label^ email_label;

	private: System::Windows::Forms::Label^ password_label;
	private: System::Windows::Forms::TextBox^ email_textbox;

	private: System::Windows::Forms::Panel^ dont_mind_this;
	private: System::Windows::Forms::Panel^ dontmind2;
	private: System::Windows::Forms::TextBox^ password_textbox;
	private: System::Windows::Forms::TextBox^ dontmind3;
	private: System::Windows::Forms::TextBox^ dontmind4;
	private: System::Windows::Forms::Label^ register_label;
	private: System::Windows::Forms::Button^ signin_button;
	private: System::Windows::Forms::Button^ exit_button;

	protected:

	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UserConnectInterface::typeid));
			this->signin_label = (gcnew System::Windows::Forms::Label());
			this->email_label = (gcnew System::Windows::Forms::Label());
			this->password_label = (gcnew System::Windows::Forms::Label());
			this->email_textbox = (gcnew System::Windows::Forms::TextBox());
			this->dont_mind_this = (gcnew System::Windows::Forms::Panel());
			this->dontmind2 = (gcnew System::Windows::Forms::Panel());
			this->password_textbox = (gcnew System::Windows::Forms::TextBox());
			this->dontmind3 = (gcnew System::Windows::Forms::TextBox());
			this->dontmind4 = (gcnew System::Windows::Forms::TextBox());
			this->register_label = (gcnew System::Windows::Forms::Label());
			this->signin_button = (gcnew System::Windows::Forms::Button());
			this->exit_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// signin_label
			// 
			this->signin_label->AutoSize = true;
			this->signin_label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->signin_label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 30.25F));
			this->signin_label->ForeColor = System::Drawing::Color::White;
			this->signin_label->Location = System::Drawing::Point(75, 138);
			this->signin_label->Name = L"signin_label";
			this->signin_label->Size = System::Drawing::Size(148, 55);
			this->signin_label->TabIndex = 0;
			this->signin_label->Text = L"Sign In";
			// 
			// email_label
			// 
			this->email_label->AutoSize = true;
			this->email_label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->email_label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->email_label->ForeColor = System::Drawing::Color::White;
			this->email_label->Location = System::Drawing::Point(81, 218);
			this->email_label->Name = L"email_label";
			this->email_label->Size = System::Drawing::Size(51, 23);
			this->email_label->TabIndex = 1;
			this->email_label->Text = L"Email";
			// 
			// password_label
			// 
			this->password_label->AutoSize = true;
			this->password_label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->password_label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->password_label->ForeColor = System::Drawing::Color::White;
			this->password_label->Location = System::Drawing::Point(81, 291);
			this->password_label->Name = L"password_label";
			this->password_label->Size = System::Drawing::Size(80, 23);
			this->password_label->TabIndex = 2;
			this->password_label->Text = L"Password";
			// 
			// email_textbox
			// 
			this->email_textbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->email_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->email_textbox->ForeColor = System::Drawing::Color::White;
			this->email_textbox->Location = System::Drawing::Point(85, 240);
			this->email_textbox->Name = L"email_textbox";
			this->email_textbox->Size = System::Drawing::Size(226, 26);
			this->email_textbox->TabIndex = 3;
			// 
			// dont_mind_this
			// 
			this->dont_mind_this->BackColor = System::Drawing::Color::White;
			this->dont_mind_this->Location = System::Drawing::Point(85, 272);
			this->dont_mind_this->Name = L"dont_mind_this";
			this->dont_mind_this->Size = System::Drawing::Size(226, 2);
			this->dont_mind_this->TabIndex = 4;
			// 
			// dontmind2
			// 
			this->dontmind2->BackColor = System::Drawing::Color::White;
			this->dontmind2->Location = System::Drawing::Point(85, 349);
			this->dontmind2->Name = L"dontmind2";
			this->dontmind2->Size = System::Drawing::Size(226, 2);
			this->dontmind2->TabIndex = 6;
			// 
			// password_textbox
			// 
			this->password_textbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->password_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->password_textbox->ForeColor = System::Drawing::Color::White;
			this->password_textbox->Location = System::Drawing::Point(85, 317);
			this->password_textbox->Name = L"password_textbox";
			this->password_textbox->PasswordChar = '*';
			this->password_textbox->Size = System::Drawing::Size(226, 26);
			this->password_textbox->TabIndex = 5;
			// 
			// dontmind3
			// 
			this->dontmind3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->dontmind3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dontmind3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F));
			this->dontmind3->ForeColor = System::Drawing::Color::White;
			this->dontmind3->Location = System::Drawing::Point(85, 357);
			this->dontmind3->Name = L"dontmind3";
			this->dontmind3->Size = System::Drawing::Size(120, 15);
			this->dontmind3->TabIndex = 7;
			this->dontmind3->Text = L"Don\'t have an account\?";
			// 
			// dontmind4
			// 
			this->dontmind4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->dontmind4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dontmind4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F));
			this->dontmind4->ForeColor = System::Drawing::Color::White;
			this->dontmind4->Location = System::Drawing::Point(211, 357);
			this->dontmind4->Name = L"dontmind4";
			this->dontmind4->Size = System::Drawing::Size(24, 15);
			this->dontmind4->TabIndex = 8;
			this->dontmind4->Text = L"Click";
			// 
			// register_label
			// 
			this->register_label->AutoSize = true;
			this->register_label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->register_label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.45F));
			this->register_label->ForeColor = System::Drawing::Color::IndianRed;
			this->register_label->Location = System::Drawing::Point(241, 357);
			this->register_label->Name = L"register_label";
			this->register_label->Size = System::Drawing::Size(33, 15);
			this->register_label->TabIndex = 9;
			this->register_label->Text = L"here!";
			this->register_label->Click += gcnew System::EventHandler(this, &UserConnectInterface::register_label_Click);
			// 
			// signin_button
			// 
			this->signin_button->BackColor = System::Drawing::Color::IndianRed;
			this->signin_button->FlatAppearance->BorderSize = 0;
			this->signin_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->signin_button->Location = System::Drawing::Point(85, 388);
			this->signin_button->Name = L"signin_button";
			this->signin_button->Size = System::Drawing::Size(106, 48);
			this->signin_button->TabIndex = 10;
			this->signin_button->Text = L"Sign In";
			this->signin_button->UseVisualStyleBackColor = false;
			this->signin_button->Click += gcnew System::EventHandler(this, &UserConnectInterface::signin_button_Click);
			// 
			// exit_button
			// 
			this->exit_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->exit_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exit_button->ForeColor = System::Drawing::Color::IndianRed;
			this->exit_button->Location = System::Drawing::Point(205, 388);
			this->exit_button->Name = L"exit_button";
			this->exit_button->Size = System::Drawing::Size(106, 48);
			this->exit_button->TabIndex = 11;
			this->exit_button->Text = L"Exit";
			this->exit_button->UseVisualStyleBackColor = false;
			this->exit_button->Click += gcnew System::EventHandler(this, &UserConnectInterface::exit_button_Click);
			// 
			// UserConnectInterface
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1048, 620);
			this->Controls->Add(this->exit_button);
			this->Controls->Add(this->signin_button);
			this->Controls->Add(this->register_label);
			this->Controls->Add(this->dontmind4);
			this->Controls->Add(this->dontmind3);
			this->Controls->Add(this->dontmind2);
			this->Controls->Add(this->password_textbox);
			this->Controls->Add(this->dont_mind_this);
			this->Controls->Add(this->email_textbox);
			this->Controls->Add(this->password_label);
			this->Controls->Add(this->email_label);
			this->Controls->Add(this->signin_label);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::White;
			this->Name = L"UserConnectInterface";
			this->Text = L"UserConnectInterface";
			this->Load += gcnew System::EventHandler(this, &UserConnectInterface::UserConnectInterface_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

	private: System::Void UserConnectInterface_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	public: User^ user = nullptr;
	public: bool switchToMain = false;

	private: System::Void signin_button_Click(System::Object^ sender, System::EventArgs^ e) {
		try
		{
			String^ email = this->email_textbox->Text;
			String^ password = this->password_textbox->Text;
			//convert pentru afisare
			std::string emailStr = msclr::interop::marshal_as<std::string>(email);
			std::cout << "Email: " << emailStr << std::endl;
			std::string passwordStr = msclr::interop::marshal_as<std::string>(GetSHA256Hash(password));
			std::cout << "Password: " << passwordStr << std::endl;

			if (email->Length == 0 || password->Length == 0) {
				MessageBox::Show("Please enter username and password",
					"Username or Password Empty", MessageBoxButtons::OK);
				return;
			}
			user = gcnew User();
			user->email = email;
			//aici trimit catre server email si password
			Json::Value jsonData;
			String^ operatiune = "login";
			jsonData["operatiune"] = msclr::interop::marshal_as<std::string>(operatiune);
			jsonData["mail"] = msclr::interop::marshal_as<std::string>(email);
			jsonData["password"] = msclr::interop::marshal_as<std::string>(GetSHA256Hash(password));
			std::string jsonString = jsonData.toStyledString();


			// Convert the string to bytes
			array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
			pin_ptr<unsigned char> pinnedData = &dataBytes[0];
			int dataLength = dataBytes->Length;

			int bytesSent = send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);
			if (bytesSent == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(connectSocket);
				WSACleanup();
				return;
			}
			else
			{
				printf("Bytes sent: %d\n", bytesSent);
			}

			// Receive the response from the server
			array<Byte>^ recvBuffer = gcnew array<Byte>(sizeof(int));
			pin_ptr<Byte> pinnedRecvBuffer = &recvBuffer[0];
			int bytesReceived = recv(connectSocket, reinterpret_cast<char*>(pinnedRecvBuffer), sizeof(int), 0);
			if (bytesReceived == sizeof(int))
			{
				// Convert the received byte array to an integer
				int receivedValue = BitConverter::ToInt32(recvBuffer, 0);
				// Process the received integer
				if (receivedValue == -1)
					MessageBox::Show("Please enter username and password","Username or Password Empty", MessageBoxButtons::OK);
				else if (receivedValue == 0) {
					MessageBox::Show("Email or password is incorrect","Email or Password Error", MessageBoxButtons::OK);
				}
				else if (receivedValue == 1) {
					MessageBox::Show("Email si password corecte!",
						"mail si password corecte", MessageBoxButtons::OK);
					this->Close();
				}
			}
			else if (bytesReceived == 0)
			{
				printf("Connection closed by the server.\n");
			}
			else
			{
				printf("recv failed with error: %d\n", WSAGetLastError());
			}
		}
		catch (Exception^ ex)
		{
			// Handle the exception
			MessageBox::Show("An error occurred: " + ex->Message,
				"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	String^ GetSHA256Hash(String^ input) {
		array<Byte>^ hashBytes;
		pin_ptr<const wchar_t> str = PtrToStringChars(input);

		System::Security::Cryptography::SHA256Managed^ sha256 = gcnew System::Security::Cryptography::SHA256Managed();
		hashBytes = sha256->ComputeHash(Encoding::UTF8->GetBytes(input));

		StringBuilder^ sb = gcnew StringBuilder();
		for each (Byte b in hashBytes) {
			sb->Append(b.ToString("x2"));
		}
		return sb->ToString();
	}

	public: bool switchToRegister = false;
	private: System::Void register_label_Click(System::Object^ sender, System::EventArgs^ e) {
		this->switchToRegister = true;
		this->Close();
	}
private: System::Void exit_button_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit();
}
};
}
