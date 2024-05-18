#pragma once

namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ShareForm
	/// </summary>
	public ref class ShareForm : public System::Windows::Forms::Form
	{
	public:
		User^ user;
		SOCKET connectSocket;
		ShareForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		ShareForm(User^ us, SOCKET connect) {
			InitializeComponent();
			connectSocket = connect;
			user = us;
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ShareForm()
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ShareForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(115, 85);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Trimite";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ShareForm::sendButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(132, 41);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(162, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(39, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Introduceti email:";
			// 
			// ShareForm
			// 
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(330, 133);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ShareForm";
			this->Text = L"Share";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void sendButton_Click(Object^ sender, EventArgs^ e) {
			String^ email = textBox1->Text;
			Json::Value jsonData;
			Console::WriteLine("Email: " + email);
			jsonData["operatiune"] = "share";
			jsonData["email"] = msclr::interop::marshal_as<std::string>(email);
			std::string jsonString = jsonData.toStyledString();
			array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
			pin_ptr<unsigned char> pinnedData = &dataBytes[0];
			int dataLength = dataBytes->Length;
			send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);
			char buffer[1024];
			int bytesReceived = recv(connectSocket, buffer, 1024, 0);
			if (bytesReceived > 0) {
				buffer[bytesReceived] = '\0';
				Json::Value response;
				Json::Reader reader;
				if (reader.parse(buffer, response)) {
					int shareback = response.get("shareback", 0).asInt();
					if (shareback == 1) {
						MessageBox::Show("Fisier trimis cu succes catre " + email);
					}
					else {
						MessageBox::Show("Acest client nu exista.");
					}
				}
				else {
					MessageBox::Show("Eroare la parsarea raspunsului JSON.");
				}
			}
			else if (bytesReceived == 0) {
				MessageBox::Show("Conexiunea cu serverul a fost închisa.");
			}
			else {
				MessageBox::Show("Eroare la primirea datelor de la server.");
			}

		}
#pragma endregion
	};
}
