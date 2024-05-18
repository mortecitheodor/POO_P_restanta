#pragma once
#include "User.h"
#include <Windows.h>
#include <json/json.h>
#include <msclr/marshal_cppstd.h>
#include <winsock2.h>
#include <stdio.h>
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
#define DEFAULT_BUFLEN 1024

	/// <summary>
	/// Summary for Register
	/// </summary>
	public ref class Register : public System::Windows::Forms::Form
	{
	public:
		SOCKET connectSocket;
		User^ user;
		bool switchToLogin = false;
		bool exitVal = false;
		Register(SOCKET socket)
		{
			InitializeComponent();
			connectSocket = socket;
			this->CenterToScreen();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Register()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonBack;
	protected:
	private: System::Windows::Forms::Button^ buttonConfirm;
	private: System::Windows::Forms::TextBox^ textBoxCPassword;
	private: System::Windows::Forms::TextBox^ textBoxPassword;
	private: System::Windows::Forms::TextBox^ textBoxEmail;
	private: System::Windows::Forms::TextBox^ textBoxName;
	private: System::Windows::Forms::Label^ labelCPassword;
	private: System::Windows::Forms::Label^ labelPassword;
	private: System::Windows::Forms::Label^ labelEmail;
	private: System::Windows::Forms::Label^ labelName;
	private: System::Windows::Forms::Label^ label1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Register::typeid));
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			this->buttonConfirm = (gcnew System::Windows::Forms::Button());
			this->textBoxCPassword = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEmail = (gcnew System::Windows::Forms::TextBox());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->labelCPassword = (gcnew System::Windows::Forms::Label());
			this->labelPassword = (gcnew System::Windows::Forms::Label());
			this->labelEmail = (gcnew System::Windows::Forms::Label());
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonBack
			// 
			this->buttonBack->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->buttonBack->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->buttonBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonBack->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F));
			this->buttonBack->ForeColor = System::Drawing::Color::IndianRed;
			this->buttonBack->Location = System::Drawing::Point(540, 395);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(153, 55);
			this->buttonBack->TabIndex = 19;
			this->buttonBack->Text = L"Back";
			this->buttonBack->UseVisualStyleBackColor = false;
			this->buttonBack->Click += gcnew System::EventHandler(this, &Register::buttonBack_Click);
			// 
			// buttonConfirm
			// 
			this->buttonConfirm->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->buttonConfirm->BackColor = System::Drawing::Color::IndianRed;
			this->buttonConfirm->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonConfirm->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F));
			this->buttonConfirm->ForeColor = System::Drawing::Color::White;
			this->buttonConfirm->Location = System::Drawing::Point(355, 395);
			this->buttonConfirm->Name = L"buttonConfirm";
			this->buttonConfirm->Size = System::Drawing::Size(153, 55);
			this->buttonConfirm->TabIndex = 18;
			this->buttonConfirm->Text = L"Confirm";
			this->buttonConfirm->UseVisualStyleBackColor = false;
			this->buttonConfirm->Click += gcnew System::EventHandler(this, &Register::buttonConfirm_Click);
			// 
			// textBoxCPassword
			// 
			this->textBoxCPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBoxCPassword->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->textBoxCPassword->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxCPassword->ForeColor = System::Drawing::Color::White;
			this->textBoxCPassword->Location = System::Drawing::Point(355, 334);
			this->textBoxCPassword->Name = L"textBoxCPassword";
			this->textBoxCPassword->PasswordChar = '*';
			this->textBoxCPassword->Size = System::Drawing::Size(371, 16);
			this->textBoxCPassword->TabIndex = 12;
			// 
			// textBoxPassword
			// 
			this->textBoxPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBoxPassword->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->textBoxPassword->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxPassword->ForeColor = System::Drawing::Color::White;
			this->textBoxPassword->Location = System::Drawing::Point(355, 279);
			this->textBoxPassword->Name = L"textBoxPassword";
			this->textBoxPassword->PasswordChar = '*';
			this->textBoxPassword->Size = System::Drawing::Size(371, 16);
			this->textBoxPassword->TabIndex = 13;
			// 
			// textBoxEmail
			// 
			this->textBoxEmail->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBoxEmail->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->textBoxEmail->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxEmail->ForeColor = System::Drawing::Color::White;
			this->textBoxEmail->Location = System::Drawing::Point(355, 239);
			this->textBoxEmail->Name = L"textBoxEmail";
			this->textBoxEmail->Size = System::Drawing::Size(371, 16);
			this->textBoxEmail->TabIndex = 16;
			// 
			// textBoxName
			// 
			this->textBoxName->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBoxName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->textBoxName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBoxName->ForeColor = System::Drawing::Color::White;
			this->textBoxName->Location = System::Drawing::Point(355, 184);
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(371, 16);
			this->textBoxName->TabIndex = 17;
			// 
			// labelCPassword
			// 
			this->labelCPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelCPassword->AutoSize = true;
			this->labelCPassword->BackColor = System::Drawing::Color::Transparent;
			this->labelCPassword->Location = System::Drawing::Point(199, 334);
			this->labelCPassword->Name = L"labelCPassword";
			this->labelCPassword->Size = System::Drawing::Size(117, 15);
			this->labelCPassword->TabIndex = 6;
			this->labelCPassword->Text = L"Confirm Password(*)";
			// 
			// labelPassword
			// 
			this->labelPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelPassword->AutoSize = true;
			this->labelPassword->BackColor = System::Drawing::Color::Transparent;
			this->labelPassword->Location = System::Drawing::Point(246, 282);
			this->labelPassword->Name = L"labelPassword";
			this->labelPassword->Size = System::Drawing::Size(70, 15);
			this->labelPassword->TabIndex = 7;
			this->labelPassword->Text = L"Password(*)";
			// 
			// labelEmail
			// 
			this->labelEmail->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelEmail->AutoSize = true;
			this->labelEmail->BackColor = System::Drawing::Color::Transparent;
			this->labelEmail->Location = System::Drawing::Point(264, 239);
			this->labelEmail->Name = L"labelEmail";
			this->labelEmail->Size = System::Drawing::Size(49, 15);
			this->labelEmail->TabIndex = 10;
			this->labelEmail->Text = L"Email(*)";
			// 
			// labelName
			// 
			this->labelName->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelName->AutoSize = true;
			this->labelName->BackColor = System::Drawing::Color::Transparent;
			this->labelName->Location = System::Drawing::Point(264, 184);
			this->labelName->Name = L"labelName";
			this->labelName->Size = System::Drawing::Size(52, 15);
			this->labelName->TabIndex = 11;
			this->labelName->Text = L"Name(*)";
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(237, 61);
			this->label1->Margin = System::Windows::Forms::Padding(7, 0, 7, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(605, 184);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Register";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Register
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1002, 552);
			this->Controls->Add(this->buttonBack);
			this->Controls->Add(this->buttonConfirm);
			this->Controls->Add(this->textBoxCPassword);
			this->Controls->Add(this->textBoxPassword);
			this->Controls->Add(this->textBoxEmail);
			this->Controls->Add(this->textBoxName);
			this->Controls->Add(this->labelCPassword);
			this->Controls->Add(this->labelPassword);
			this->Controls->Add(this->labelEmail);
			this->Controls->Add(this->labelName);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->ForeColor = System::Drawing::Color::Transparent;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Register";
			this->Text = L"Register";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Register::Register_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Register_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		if (e->CloseReason == System::Windows::Forms::CloseReason::UserClosing && switchToLogin == false) {
			this->exitVal = 1;
		}
	}
	private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		this->switchToLogin = true;
		this->Close();
	}

	private: System::Void buttonConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
		try
		{
			String^ name = this->textBoxName->Text;
			String^ operatiune = "register";
			String^ email = this->textBoxEmail->Text;
			String^ password = this->textBoxPassword->Text;
			String^ cpassword = this->textBoxCPassword->Text;

			if (password != cpassword) {
				MessageBox::Show("Confirmation password is not equal with password","Password do not match", MessageBoxButtons::OK);
				return;
			}
			Console::WriteLine("Nume: " + name);
			Console::WriteLine("Email: " + email);
			Console::WriteLine("Parola: " + password);

			//aici trimit catre server email si password
			Json::Value jsonData;
			jsonData["operatiune"] = msclr::interop::marshal_as<std::string>(operatiune);
			jsonData["name"] = msclr::interop::marshal_as<std::string>(name);
			jsonData["mail"] = msclr::interop::marshal_as<std::string>(email);
			jsonData["password"] = msclr::interop::marshal_as<std::string>(GetSHA256Hash(password));

			user = gcnew User();
			user->email = email;
			std::string jsonString = jsonData.toStyledString();


			// Convert the string to bytes
			array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
			pin_ptr<unsigned char> pinnedData = &dataBytes[0];
			int dataLength = dataBytes->Length;

			int bytesSent = send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);
			if (bytesSent == SOCKET_ERROR)
			{
				closesocket(connectSocket);
				WSACleanup();
				return;
			}
			else
			{
				// Receive the response from the server
				array<Byte>^ recvBuffer = gcnew array<Byte>(sizeof(int));
				pin_ptr<Byte> pinnedRecvBuffer = &recvBuffer[0];
				int bytesReceived = recv(connectSocket, reinterpret_cast<char*>(pinnedRecvBuffer), sizeof(int), 0);
				if (bytesReceived == sizeof(int))
				{
					// Convert the received byte array to an integer
					int receivedValue = BitConverter::ToInt32(recvBuffer, 0);

					// Process the received integer
					if (receivedValue == 1) {
						MessageBox::Show("Inregistrare realizata cu succes!", "Succes", MessageBoxButtons::OK, MessageBoxIcon::Information);
						this->switchToLogin = true;
						this->Close();
					}
					else if (receivedValue == 0) {
						MessageBox::Show("Adresa de email exista deja în baza de date!", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
				else if (bytesReceived == 0)
				{
					// Connection closed by the server
					printf("Connection closed by the server.\n");
				}
				else
				{
					// Error occurred while receiving
					printf("recv failed with error: %d\n", WSAGetLastError());
				}
			}
		}
		catch (Exception^ ex)
		{
			// Handle the exception
			MessageBox::Show("An error occurred: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	String^ GetSHA256Hash(String^ input) {
		array<Byte>^ hashBytes;
		pin_ptr<const wchar_t> str = PtrToStringChars(input);

		// Hash the input password
		System::Security::Cryptography::SHA256Managed^ sha256 = gcnew System::Security::Cryptography::SHA256Managed();
		hashBytes = sha256->ComputeHash(Encoding::UTF8->GetBytes(input));

		// Convert the hashed bytes to a hexadecimal string
		StringBuilder^ sb = gcnew StringBuilder();
		for each (Byte b in hashBytes) {
			sb->Append(b.ToString("x2"));
		}
		return sb->ToString();
	}

};
}
