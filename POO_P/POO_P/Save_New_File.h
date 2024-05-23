#pragma once

namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Save_New_File
	/// </summary>
	public ref class Save_New_File : public System::Windows::Forms::Form
	{
	private: String^ new_file_name;

	public:
		void Set_New_Name(String^ value) {
			this->new_file_name = value;
		}
		String^ return_name() {
			return new_file_name;
		}
		SOCKET connectSocket;
		User^ user;
		String^ name;
		String^ file_content;

		Save_New_File(void)
		{
			InitializeComponent();
			this->CenterToScreen();


		}

		Save_New_File(SOCKET received_socket, User^ received_user, String^ recv_file_content)
		{
			InitializeComponent();
			this->CenterToScreen();
			this->connectSocket = received_socket;
			this->user = received_user;
			this->file_content = recv_file_content;
			this->new_file_name = nullptr;

		}

	protected:
		~Save_New_File()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;

	private:
		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(150, 50);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(233, 21);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Introduceti numele fisierului:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(154, 90);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(200, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(200, 140);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 30);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Save";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Save_New_File::button1_Click);
			// 
			// Save_New_File
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(500, 250);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"Save_New_File";
			this->Text = L"Save Your File";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(textBox1->Text))
		{
			MessageBox::Show("Trebuie sa introduceti numele fisierului!", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else
		{
			name = textBox1->Text;

			Json::Value jsonData;
			jsonData["operatiune"] = "verifying_file_name";
			String^ file = this->name;
			jsonData["file"] = msclr::interop::marshal_as<std::string>(file);
			Console::WriteLine("Operatiune: verifying_file_name");

			std::string jsonString = jsonData.toStyledString();
			array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
			pin_ptr<unsigned char> pinnedData = &dataBytes[0];
			int dataLength = dataBytes->Length;
			send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);

			int response;
			int bytesReceived = recv(connectSocket, (char*)&response, sizeof(response), 0);

			if (bytesReceived > 0) {
				if (response == 1) {
					std::cout << "Fisierul nu exista in baza de date." << std::endl;

					Json::Value jsonData;
					jsonData["operatiune"] = "saving_new_file";
					String^ file = this->name;
					String^ email = this->user->email;
					String^ content = this->file_content;
					jsonData["file"] = msclr::interop::marshal_as<std::string>(file);
					jsonData["email"] = msclr::interop::marshal_as<std::string>(email);
					jsonData["content"] = msclr::interop::marshal_as<std::string>(content);

					std::string jsonString = jsonData.toStyledString();
					array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
					pin_ptr<unsigned char> pinnedData = &dataBytes[0];
					int dataLength = dataBytes->Length;
					send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);


					Console::WriteLine("Operatiune: saving_new_file");
					MessageBox::Show("Fisierul a fost salvat!", "Succes", MessageBoxButtons::OK, MessageBoxIcon::Information);
					Set_New_Name(this->name);
					this->Close();
				}
				else if (response == 0) {
					std::cout << "Fisierul exista in baza de date." << std::endl;
				}
				else {
					std::cerr << "A aparut o eroare la server." << std::endl;
				}
			}
			else {
				std::cerr << "Nu s-a primit niciun raspuns de la server." << std::endl;
			}

		}
	}
	};
}
