#pragma once

namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for UserConnectInterface
	/// </summary>
	public ref class UserConnectInterface : public System::Windows::Forms::Form
	{
	public:
		UserConnectInterface(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserConnectInterface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ signin_label;
	private: System::Windows::Forms::Label^ username_label;
	private: System::Windows::Forms::Label^ password_label;
	private: System::Windows::Forms::TextBox^ username_textbox;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UserConnectInterface::typeid));
			this->signin_label = (gcnew System::Windows::Forms::Label());
			this->username_label = (gcnew System::Windows::Forms::Label());
			this->password_label = (gcnew System::Windows::Forms::Label());
			this->username_textbox = (gcnew System::Windows::Forms::TextBox());
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
			// username_label
			// 
			this->username_label->AutoSize = true;
			this->username_label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->username_label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->username_label->ForeColor = System::Drawing::Color::White;
			this->username_label->Location = System::Drawing::Point(81, 218);
			this->username_label->Name = L"username_label";
			this->username_label->Size = System::Drawing::Size(87, 23);
			this->username_label->TabIndex = 1;
			this->username_label->Text = L"Username";
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
			// username_textbox
			// 
			this->username_textbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(19)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->username_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->username_textbox->ForeColor = System::Drawing::Color::White;
			this->username_textbox->Location = System::Drawing::Point(85, 240);
			this->username_textbox->Name = L"username_textbox";
			this->username_textbox->Size = System::Drawing::Size(226, 26);
			this->username_textbox->TabIndex = 3;
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
			this->Controls->Add(this->username_textbox);
			this->Controls->Add(this->password_label);
			this->Controls->Add(this->username_label);
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


};
}
