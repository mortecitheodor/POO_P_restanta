#pragma once
#include "User.h"
#include <windows.h>
#include <vcclr.h>
namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InputForm
	/// </summary>
	public ref class InputForm : public System::Windows::Forms::Form
	{
	public:
		SOCKET connectSocket;
		User^ user;
		InputForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		InputForm(User^ us, SOCKET connect)
		{
			InitializeComponent();
			connectSocket = connect;
			user = us;
			this->CenterToScreen();
			box = gcnew TextBox();
			box->Location = System::Drawing::Point(10, 10);
			box->Size = System::Drawing::Size(100, 20);
			this->Controls->Add(box);

			but = gcnew Button();
			but->Location = System::Drawing::Point(10, 40);
			but->Size = System::Drawing::Size(75, 23);
			but->Text = "Confirm";
			but->Click += gcnew EventHandler(this, &InputForm::confirmButton_Click);
			this->Controls->Add(but);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InputForm()
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
		System::Windows::Forms::TextBox^ box;
		System::Windows::Forms::Button^ but;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

		void InitializeComponent(void)
		{
			// 
			// InputForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(128, 72);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"InputForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Save File";
			this->ResumeLayout(false);

		}
		void confirmButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::String^ fileName = this->box->Text;
			MessageBox::Show("Numele fisierului introdus este: " + fileName);
		}

#pragma endregion
	};
}
