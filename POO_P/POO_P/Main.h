#pragma once
#include "User.h"
#include "EditFile.h"
#include "DeleteFileInfoForm.h"
#include <msclr/marshal_cppstd.h>


namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		SOCKET connectSocket;
		User^ user;
		bool switchToLogin = false;
		bool exitVal = false;
	private: 
		System::Windows::Forms::Panel^ linkPanel;
		System::Windows::Forms::Label^ Files_Display_Title;
		System::Windows::Forms::Label^ UserInfo;
		System::Windows::Forms::Button^ createNewFileButton;
		System::Windows::Forms::Button^ deleteFileInfoButton;

	public:
		Main(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		Main(User^ user, SOCKET socket) {
			InitializeComponent();
            connectSocket = socket;
            UserInfo->Text = "Welcome " + user->email + " ! ";
            this->user = user;
            this->CenterToScreen();

            // Sign Out Button
            Button^ signOutButton = gcnew Button();
            UserInfo->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
            Files_Display_Title->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
            linkPanel->Font = gcnew System::Drawing::Font("Times New Roman", 14, FontStyle::Regular);
            signOutButton->Text = "Sign Out";
            signOutButton->Font = gcnew System::Drawing::Font("Arial", 10.25F, FontStyle::Bold);
            signOutButton->Size = System::Drawing::Size(100, 40);
            signOutButton->BackColor = Color::FromArgb(255, 100, 100);
            signOutButton->ForeColor = Color::White;
            int rightEdge = this->ClientSize.Width;
            int buttonWidth = signOutButton->Width;
            signOutButton->Location = Point(rightEdge - buttonWidth - 10, 10);
            signOutButton->Click += gcnew EventHandler(this, &Main::signOutButton_Click);
            this->Controls->Add(signOutButton);

            // Create New File Button
            createNewFileButton = gcnew Button();
            createNewFileButton->Text = "Create New File";
            createNewFileButton->Font = gcnew System::Drawing::Font("Arial", 10.25F, FontStyle::Bold);
            createNewFileButton->Size = System::Drawing::Size(100, 40);
            createNewFileButton->BackColor = Color::FromArgb(255, 0, 255, 0);
            createNewFileButton->ForeColor = Color::FromArgb(255, 0, 100, 0);
            createNewFileButton->Location = Point(10, 10);
            createNewFileButton->Click += gcnew EventHandler(this, &Main::createNewFileButton_Click);
            this->Controls->Add(createNewFileButton);

            // Send File Info Button
            deleteFileInfoButton = gcnew Button();
            deleteFileInfoButton->Text = "Delete File";
            deleteFileInfoButton->Font = gcnew System::Drawing::Font("Arial", 10.25F, FontStyle::Bold);
            deleteFileInfoButton->Size = System::Drawing::Size(100, 40);
			deleteFileInfoButton->BackColor = Color::FromArgb(255, 0, 255, 255);
			deleteFileInfoButton->ForeColor = Color::FromArgb(255, 255, 0, 0);
            deleteFileInfoButton->Location = Point(10, 60); // Positioned below the "Create New File" button
            deleteFileInfoButton->Click += gcnew EventHandler(this, &Main::deleteFileInfoButton_Click);
            this->Controls->Add(deleteFileInfoButton);

			const int bufferSize = 4096;
			array<Byte>^ buffer = gcnew array<Byte>(bufferSize);

			// Primirea datelor de la server
			pin_ptr<Byte> pinnedBuffer = &buffer[0];
			int bytesReceived = recv(connectSocket, reinterpret_cast<char*>(pinnedBuffer), bufferSize, 0);

			linkPanel->Controls->Clear();

			if (bytesReceived > 0)
			{
				String^ responseString = Encoding::ASCII->GetString(buffer, 0, bytesReceived);
				std::string unmanagedResponseString = msclr::interop::marshal_as<std::string>(responseString);
				Json::Value receivedJson;
				Json::CharReaderBuilder builder;
				JSONCPP_STRING errs;
				const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
				if (reader->parse(unmanagedResponseString.c_str(), unmanagedResponseString.c_str() + unmanagedResponseString.length(), &receivedJson, &errs))
				{
					Json::Value fileList = receivedJson["fisiere"];
					if (fileList.size() > 0)
					{
						int yOffset = 0;
						for (Json::Value::ArrayIndex i = 0; i < fileList.size(); ++i)
						{
							std::string fileName = fileList[i].asString();
							LinkLabel^ link = gcnew LinkLabel();
							link->Text = gcnew String(fileName.c_str());
							link->Location = Point(0, yOffset); // Set the position
							link->AutoSize = true;
							link->Font = gcnew System::Drawing::Font("Aries", 14, FontStyle::Bold); // Set font size and style
							link->LinkColor = Color::Yellow;
							link->LinkBehavior = LinkBehavior::NeverUnderline;
							link->LinkClicked += gcnew LinkLabelLinkClickedEventHandler(this, &Main::linkLabel_LinkClicked);
							linkPanel->Controls->Add(link);
							yOffset += link->Height + 5; // Adjust for next link
						}
					}
					else
					{
						LinkLabel^ messageLink = gcnew LinkLabel();
						messageLink->LinkColor = Color::White;
						messageLink->Font = gcnew System::Drawing::Font(messageLink->Font->FontFamily, 12, FontStyle::Regular);
						messageLink->Text = "Inca nu exista fisiere.";
						messageLink->AutoSize = true;
						messageLink->LinkColor = Color::Yellow;
						messageLink->LinkBehavior = LinkBehavior::NeverUnderline;
						linkPanel->Controls->Add(messageLink);
					}
				}
				else
				{
					MessageBox::Show("Eroare la parsarea datelor JSON.", "Eroare JSON", MessageBoxButtons::OK);
				}
			}
			else if (bytesReceived == 0)
			{
				MessageBox::Show("Conexiunea a fost inchisa de server.", "Conexiune Inchisa", MessageBoxButtons::OK);
			}
			else
			{
				MessageBox::Show("recv a esuat cu eroarea: " + Convert::ToString(WSAGetLastError()), "Eroare de Retea", MessageBoxButtons::OK);
			}
		}

		void Main::linkLabel_LinkClicked(Object^ sender, LinkLabelLinkClickedEventArgs^ e)
		{
			LinkLabel^ link = dynamic_cast<LinkLabel^>(sender);
			String^ fileName = link->Text; 
			Json::Value jsonData;
			String^ operatiune = "requested_file";
			String^ numeFisier = link->Text; 
			jsonData["operatiune"] = msclr::interop::marshal_as<std::string>(operatiune);
			jsonData["nume_fisier"] = msclr::interop::marshal_as<std::string>(numeFisier);
			std::string jsonString = jsonData.toStyledString();
			Console::WriteLine("Data sent to server ( JSON ): " + gcnew String(jsonString.c_str()));
			array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
			pin_ptr<unsigned char> pinnedData = &dataBytes[0];
			int dataLength = dataBytes->Length;
			send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);

			// Primeste raspunsul de la server
			const int bufferSize = 1048576; // Dimensiunea bufferului 
			array<Byte>^ recvBuffer = gcnew array<Byte>(bufferSize);
			pin_ptr<Byte> pinnedRecvBuffer = &recvBuffer[0];

			int bytesReceived = recv(connectSocket, reinterpret_cast<char*>(pinnedRecvBuffer), recvBuffer->Length, 0);

			if (bytesReceived > 0)
			{
				std::string receivedData(reinterpret_cast<char*>(pinnedRecvBuffer), bytesReceived);
				Json::Value receivedJson;
				Json::Reader reader;
				bool parsingSuccessful = reader.parse(receivedData, receivedJson);

				if (parsingSuccessful)
				{
					String^ operatiune = gcnew String(receivedJson["operatiune"].asString().c_str());
					if (operatiune == "send_file")
					{
						String^ fileContent = gcnew String(receivedJson["file_content"].asString().c_str());
						Console::WriteLine("File Content received SUCCESSFULLY from the server ");
						POOP::EditFile^ editf = gcnew POOP::EditFile(this->user, connectSocket, fileName, fileContent);
						editf->ShowDialog();
					}
					else
					{
						Console::WriteLine("Server response: " + gcnew String(receivedData.c_str()));
					}
				}
				else
				{
					Console::WriteLine("Failed to parse server response(Probably buffer too small to receive all the date from the server.");
					std::string receivedData(reinterpret_cast<char*>(pinnedRecvBuffer), bytesReceived);
					Console::WriteLine("Received data from server: " + gcnew String(receivedData.c_str()));
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

	private: void Main::createNewFileButton_Click(Object^ sender, EventArgs^ e)
	{
		// Cand se apasa "Create New File"

		POOP::EditFile^ editf = gcnew POOP::EditFile(user, connectSocket);
		editf->ShowDialog();
	}
	
	void Main::deleteFileInfoButton_Click(Object^ sender, EventArgs^ e) {
		POOP::DeleteFileInfoForm^ deleteFileInfoForm = gcnew POOP::DeleteFileInfoForm(user, connectSocket);
		deleteFileInfoForm->ShowDialog();
	}

	private: void Main::signOutButton_Click(Object ^ sender, EventArgs ^ e) {
		this->switchToLogin = 1;
		this->Close();
		Json::Value jsonData;
		String^ operatiune = "logout";
		jsonData["operatiune"] = msclr::interop::marshal_as<std::string>(operatiune);
		std::string jsonString = jsonData.toStyledString();
		array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
		pin_ptr<unsigned char> pinnedData = &dataBytes[0];
		int dataLength = dataBytes->Length;
		send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);
	}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->UserInfo = (gcnew System::Windows::Forms::Label());
			this->linkPanel = (gcnew System::Windows::Forms::Panel());
			this->Files_Display_Title = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// UserInfo
			// 
			this->UserInfo->AutoSize = true;
			this->UserInfo->BackColor = System::Drawing::Color::Transparent;
			this->UserInfo->ForeColor = System::Drawing::Color::White;
			this->UserInfo->Location = System::Drawing::Point(217, 29);
			this->UserInfo->Name = L"UserInfo";
			this->UserInfo->Size = System::Drawing::Size(35, 13);
			this->UserInfo->TabIndex = 0;
			this->UserInfo->Text = L"label1";
			// 
			// linkPanel
			// 
			this->linkPanel->BackColor = System::Drawing::Color::Transparent;
			this->linkPanel->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkPanel->Location = System::Drawing::Point(220, 106);
			this->linkPanel->Name = L"linkPanel";
			this->linkPanel->Size = System::Drawing::Size(200, 277);
			this->linkPanel->TabIndex = 1;
			// 
			// Files_Display_Title
			// 
			this->Files_Display_Title->AutoSize = true;
			this->Files_Display_Title->BackColor = System::Drawing::Color::Transparent;
			this->Files_Display_Title->ForeColor = System::Drawing::Color::White;
			this->Files_Display_Title->Location = System::Drawing::Point(217, 73);
			this->Files_Display_Title->Name = L"Files_Display_Title";
			this->Files_Display_Title->Size = System::Drawing::Size(56, 13);
			this->Files_Display_Title->TabIndex = 2;
			this->Files_Display_Title->Text = L"Your Files:";
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1002, 552);
			this->Controls->Add(this->Files_Display_Title);
			this->Controls->Add(this->linkPanel);
			this->Controls->Add(this->UserInfo);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Main";
			this->Text = L"OverLeaf";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Main::Main_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		private: System::Void Main_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			if (e->CloseReason == System::Windows::Forms::CloseReason::UserClosing && switchToLogin == false) {
				this->exitVal = 1;
			}
		}
#pragma endregion
	private: System::Void Main_Load(System::Object^ sender, System::EventArgs^ e) {
		
	}
};
}
