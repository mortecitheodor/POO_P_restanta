#pragma once
#include "User.h"
#include "EditFile.h"

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
	private: System::Windows::Forms::Panel^ linkPanel;
	public:

	public:

	public:
	private: System::Windows::Forms::Label^ UserInfo;
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
			this->CenterToScreen();
			Button^ signOutButton = gcnew Button();

			// Set properties for the button
			signOutButton->Text = "Sign Out";
			signOutButton->Font = gcnew System::Drawing::Font("Arial", 10.25F, FontStyle::Bold);
			signOutButton->Size = System::Drawing::Size(100, 40);
			signOutButton->BackColor = Color::FromArgb(255, 100, 100);
			signOutButton->ForeColor = Color::White;
			int rightEdge = this->ClientSize.Width; // Get the width of the form's client area
			int buttonWidth = signOutButton->Width; // Get the width of the button
			signOutButton->Location = Point(rightEdge - buttonWidth - 10, 10);
			signOutButton->Click += gcnew EventHandler(this, &Main::signOutButton_Click);
			this->Controls->Add(signOutButton);

			Button^ writeButton = gcnew Button();
			writeButton->Text = "Create new file";
			writeButton->Font = gcnew System::Drawing::Font("Arial", 10.25F, FontStyle::Bold);
			writeButton->Size = System::Drawing::Size(100, 40);
			writeButton->BackColor = Color::FromArgb(255, 0, 255, 0);
			writeButton->ForeColor = Color::FromArgb(255, 0, 100, 0);
			writeButton->Location = Point(10, 10);
			writeButton->Click += gcnew EventHandler(this, &Main::writeButton_Click);
			this->Controls->Add(writeButton);

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
							link->Font = gcnew System::Drawing::Font(link->Font->FontFamily, 12, FontStyle::Regular); // Set font size to 12
							link->LinkColor = Color::Green;
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
		POOP::EditFile^ editf = gcnew POOP::EditFile(user, connectSocket);
		editf->ShowDialog();
	}
	private: void Main::writeButton_Click(Object^ sender, EventArgs^ e) {
		POOP::EditFile^ editf = gcnew POOP::EditFile(user, connectSocket);
		editf->ShowDialog();
	}
	private: void Main::signOutButton_Click(Object ^ sender, EventArgs ^ e) {
		this->switchToLogin = 1;
		this->Close();
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
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Main::Main_FormClosing);
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->UserInfo = (gcnew System::Windows::Forms::Label());
			this->linkPanel = (gcnew System::Windows::Forms::Panel());
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
			this->linkPanel->Location = System::Drawing::Point(220, 59);
			this->linkPanel->Name = L"linkPanel";
			this->linkPanel->Size = System::Drawing::Size(200, 277);
			this->linkPanel->TabIndex = 1;
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(559, 370);
			this->Controls->Add(this->linkPanel);
			this->Controls->Add(this->UserInfo);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Main";
			this->Text = L"Main";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		private: System::Void Main_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			if (e->CloseReason == System::Windows::Forms::CloseReason::UserClosing && switchToLogin == false) {
				this->exitVal = 1;
			}
		}
#pragma endregion
	};
}
