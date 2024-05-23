#pragma once
#include "InputForm.h"
#include "ShareForm.h"
#include <cliext/list>
#include "Save_New_File.h"


namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	/// <summary>
	/// Summary for EditFile
	/// </summary>
	public ref class EditFile : public System::Windows::Forms::Form
	{

	public:
		SOCKET connectSocket;
		User^ user;
		String^ file_Name="New File";
		EditFile(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		EditFile(User^ us, SOCKET connect)
		{
			InitializeComponent();
			connectSocket = connect;
			user = us;

		}

		EditFile(User^ us, SOCKET connect, String^ fName,String^ content)
		{
			InitializeComponent();
			connectSocket = connect;
			user = us;
			file_Name = fName;
			richTextBox->Rtf=content;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditFile()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStripStatusLabel^ statusLabel;
	private: System::Windows::Forms::ColorDialog^ colorDialog;
	private: System::Windows::Forms::FontDialog^ fontDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::ToolStripButton^ cmdItalic;
	private: System::Windows::Forms::ToolStripButton^ cmdBold;
	private: System::Windows::Forms::ToolStripButton^ cmdGreen;
	private: System::Windows::Forms::ToolStripButton^ cmdRed;
	private: System::Windows::Forms::ToolStripButton^ cmdUnderline;
	private: System::Windows::Forms::ToolStripButton^ cmdSave;
	private: System::Windows::Forms::StatusStrip^ statusStrip;
	private: System::Windows::Forms::ToolStrip^ toolStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ ctxSelectAll;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator8;
	private: System::Windows::Forms::ToolStripMenuItem^ ctxPaste;
	private: System::Windows::Forms::ToolStripMenuItem^ ctxCopy;
	private: System::Windows::Forms::ToolStripMenuItem^ ctxCut;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ ctxDelete;
	private: System::Windows::Forms::RichTextBox^ richTextBox;
	private: System::Windows::Forms::ToolStripButton^ ShareButton;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::ToolStripButton^ cmdAlignLeft;
	private: System::Windows::Forms::ToolStripButton^ cmdAlignCenter;
	private: System::Windows::Forms::ToolStripButton^ cmdAlignRight;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(EditFile::typeid));
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->fontDialog = (gcnew System::Windows::Forms::FontDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->cmdItalic = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdBold = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdGreen = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdUnderline = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->cmdRed = (gcnew System::Windows::Forms::ToolStripButton());
			this->ShareButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdAlignLeft = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdAlignCenter = (gcnew System::Windows::Forms::ToolStripButton());
			this->cmdAlignRight = (gcnew System::Windows::Forms::ToolStripButton());
			this->ctxSelectAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator8 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ctxPaste = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ctxCopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ctxCut = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ctxDelete = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->richTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->statusStrip->SuspendLayout();
			this->toolStrip->SuspendLayout();
			this->contextMenuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusLabel
			// 
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(100, 17);
			this->statusLabel->Text = L"Linia 1, Coloana 1";
			// 
			// cmdItalic
			// 
			this->cmdItalic->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdItalic->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdItalic.Image")));
			this->cmdItalic->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdItalic->Name = L"cmdItalic";
			this->cmdItalic->Size = System::Drawing::Size(23, 22);
			this->cmdItalic->Text = L"Italic";
			this->cmdItalic->Click += gcnew System::EventHandler(this, &EditFile::cmdItalic_Click);
			// 
			// cmdBold
			// 
			this->cmdBold->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdBold->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdBold.Image")));
			this->cmdBold->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdBold->Name = L"cmdBold";
			this->cmdBold->Size = System::Drawing::Size(23, 22);
			this->cmdBold->Text = L"Bold";
			this->cmdBold->Click += gcnew System::EventHandler(this, &EditFile::cmdBold_Click);
			// 
			// cmdGreen
			// 
			this->cmdGreen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdGreen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdGreen.Image")));
			this->cmdGreen->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdGreen->Name = L"cmdGreen";
			this->cmdGreen->Size = System::Drawing::Size(23, 22);
			this->cmdGreen->Text = L"Green";
			this->cmdGreen->Click += gcnew System::EventHandler(this, &EditFile::cmdGreen_Click);
			// 
			// cmdUnderline
			// 
			this->cmdUnderline->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdUnderline->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdUnderline.Image")));
			this->cmdUnderline->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdUnderline->Name = L"cmdUnderline";
			this->cmdUnderline->Size = System::Drawing::Size(23, 22);
			this->cmdUnderline->Text = L"Underline";
			this->cmdUnderline->Click += gcnew System::EventHandler(this, &EditFile::cmdUnderline_Click);
			// 
			// cmdSave
			// 
			this->cmdSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdSave.Image")));
			this->cmdSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdSave->Name = L"cmdSave";
			this->cmdSave->Size = System::Drawing::Size(23, 22);
			this->cmdSave->Text = L"Save";
			this->cmdSave->Click += gcnew System::EventHandler(this, &EditFile::cmdSave_Click);
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->statusLabel });
			this->statusStrip->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->statusStrip->Location = System::Drawing::Point(0, 539);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(784, 22);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 5;
			this->statusStrip->Text = L"statusStrip";
			// 
			// toolStrip
			// 
			this->toolStrip->BackColor = System::Drawing::SystemColors::MenuBar;
			this->toolStrip->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->cmdSave, this->cmdBold,
					this->cmdItalic, this->cmdUnderline, this->cmdGreen, this->cmdRed, this->ShareButton, this->cmdAlignLeft, this->cmdAlignCenter,
					this->cmdAlignRight
			});
			this->toolStrip->Location = System::Drawing::Point(0, 0);
			this->toolStrip->Name = L"toolStrip";
			this->toolStrip->Padding = System::Windows::Forms::Padding(10, 0, 1, 0);
			this->toolStrip->Size = System::Drawing::Size(784, 25);
			this->toolStrip->TabIndex = 4;
			this->toolStrip->Text = L"toolStrip";
			// 
			// cmdRed
			// 
			this->cmdRed->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdRed->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdRed.Image")));
			this->cmdRed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdRed->Name = L"cmdRed";
			this->cmdRed->Size = System::Drawing::Size(23, 22);
			this->cmdRed->Text = L"Red";
			this->cmdRed->Click += gcnew System::EventHandler(this, &EditFile::cmdRed_Click);
			// 
			// ShareButton
			// 
			this->ShareButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->ShareButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShareButton.Image")));
			this->ShareButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->ShareButton->Name = L"ShareButton";
			this->ShareButton->Size = System::Drawing::Size(23, 22);
			this->ShareButton->Text = L"Share";
			this->ShareButton->Click += gcnew System::EventHandler(this, &EditFile::ShareButton_Click);
			// 
			// cmdAlignLeft
			// 
			this->cmdAlignLeft->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdAlignLeft->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdAlignLeft.Image")));
			this->cmdAlignLeft->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdAlignLeft->Name = L"cmdAlignLeft";
			this->cmdAlignLeft->Size = System::Drawing::Size(23, 22);
			this->cmdAlignLeft->Text = L"Align Left";
			this->cmdAlignLeft->Click += gcnew System::EventHandler(this, &EditFile::cmdAlignLeft_Click);
			// 
			// cmdAlignCenter
			// 
			this->cmdAlignCenter->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdAlignCenter->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdAlignCenter.Image")));
			this->cmdAlignCenter->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdAlignCenter->Name = L"cmdAlignCenter";
			this->cmdAlignCenter->Size = System::Drawing::Size(23, 22);
			this->cmdAlignCenter->Text = L"Align Center";
			this->cmdAlignCenter->Click += gcnew System::EventHandler(this, &EditFile::cmdAlignCenter_Click);
			// 
			// cmdAlignRight
			// 
			this->cmdAlignRight->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdAlignRight->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdAlignRight.Image")));
			this->cmdAlignRight->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdAlignRight->Name = L"cmdAlignRight";
			this->cmdAlignRight->Size = System::Drawing::Size(23, 22);
			this->cmdAlignRight->Text = L"Align Right";
			this->cmdAlignRight->Click += gcnew System::EventHandler(this, &EditFile::cmdAlignRight_Click);
			// 
			// ctxSelectAll
			// 
			this->ctxSelectAll->Name = L"ctxSelectAll";
			this->ctxSelectAll->Size = System::Drawing::Size(67, 22);
			// 
			// toolStripSeparator8
			// 
			this->toolStripSeparator8->Name = L"toolStripSeparator8";
			this->toolStripSeparator8->Size = System::Drawing::Size(64, 6);
			// 
			// ctxPaste
			// 
			this->ctxPaste->Name = L"ctxPaste";
			this->ctxPaste->Size = System::Drawing::Size(67, 22);
			// 
			// ctxCopy
			// 
			this->ctxCopy->Name = L"ctxCopy";
			this->ctxCopy->Size = System::Drawing::Size(67, 22);
			// 
			// ctxCut
			// 
			this->ctxCut->Name = L"ctxCut";
			this->ctxCut->Size = System::Drawing::Size(67, 22);
			// 
			// contextMenuStrip
			// 
			this->contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ctxCut, this->ctxCopy,
					this->ctxPaste, this->toolStripSeparator8, this->ctxSelectAll
			});
			this->contextMenuStrip->Name = L"contextMenuStrip";
			this->contextMenuStrip->Size = System::Drawing::Size(68, 98);
			// 
			// ctxDelete
			// 
			this->ctxDelete->Name = L"ctxDelete";
			this->ctxDelete->Size = System::Drawing::Size(32, 19);
			this->ctxDelete->Text = L"Delete";
			// 
			// richTextBox
			// 
			this->richTextBox->AcceptsTab = true;
			this->richTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->richTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox->ContextMenuStrip = this->contextMenuStrip;
			this->richTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox->Location = System::Drawing::Point(0, 36);
			this->richTextBox->Name = L"richTextBox";
			this->richTextBox->ShowSelectionMargin = true;
			this->richTextBox->Size = System::Drawing::Size(784, 500);
			this->richTextBox->TabIndex = 3;
			this->richTextBox->Text = L"";
			this->richTextBox->SelectionChanged += gcnew System::EventHandler(this, &EditFile::richTextBox_SelectionChanged);
			// 
			// EditFile
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->toolStrip);
			this->Controls->Add(this->richTextBox);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(400, 300);
			this->Name = L"EditFile";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"File Editor";
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->toolStrip->ResumeLayout(false);
			this->toolStrip->PerformLayout();
			this->contextMenuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		private: void cmdSave_Click(System::Object^ sender, System::EventArgs^ e)
		{
			//salvare fisier
			if (this->file_Name == "New File") {  //daca fisierul este New File si nu este in baza de date
				
				Save_New_File^ save_file = gcnew Save_New_File(this->connectSocket,this->user,this->richTextBox->Rtf);
				save_file->ShowDialog();
				this->file_Name = save_file->return_name();


			}
			else {
				//se trimite fisierul la server pentru salvare, fisier existent in baza de date
				Json::Value jsonData;
				jsonData["operatiune"] = "save_existing_file";
				String^ file = this->file_Name;
				String^ file_content = this->richTextBox->Rtf;
				jsonData["file"] = msclr::interop::marshal_as<std::string>(file);
				jsonData["file_content"] = msclr::interop::marshal_as<std::string>(file_content);
				Console::WriteLine("Operatiune: save_existing file ");

				std::string jsonString = jsonData.toStyledString();
				array<Byte>^ dataBytes = Encoding::ASCII->GetBytes(msclr::interop::marshal_as<String^>(jsonString));
				pin_ptr<unsigned char> pinnedData = &dataBytes[0];
				int dataLength = dataBytes->Length;
				send(connectSocket, reinterpret_cast<char*>(pinnedData), dataLength, 0);

				// Raspunsul de la server
				char responseBuffer[2]; 
				int bytesReceived = recv(connectSocket, responseBuffer, sizeof(responseBuffer), 0);

				if (bytesReceived == SOCKET_ERROR) {
					std::cerr << "Eroare la primirea raspunsului de la server.\n";
				}
				else if (bytesReceived == 0) {
					std::cerr << "Conexiunea a fost inchisa de catre server.\n";
				}
				else {
					bool saveSuccess = (responseBuffer[0] == '1'); 
					if (saveSuccess) {
						MessageBox::Show("Fisierul a fost salvat!", "Succes", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					else {
						MessageBox::Show("Fisierul nu a fost salvat!", "Eroare", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}



			}
		}


		private: void richTextBox_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
		{
			toggleFontView();

			System::Text::StringBuilder^ status = gcnew System::Text::StringBuilder();
			if (richTextBox->SelectionLength > 0)
			{
				int lines = richTextBox->GetLineFromCharIndex(richTextBox->SelectionStart + richTextBox->SelectionLength) -
					richTextBox->GetLineFromCharIndex(richTextBox->SelectionStart) + 1;
				status->Append(lines)->Append(" Linia, ")->Append(richTextBox->SelectionLength)->Append(" Caractere selectate");
			}
			else
			{
				status->Append("Linia ")->Append(richTextBox->GetLineFromCharIndex(richTextBox->GetFirstCharIndexOfCurrentLine()) + 1)->Append(", Coloana ")->Append(richTextBox->SelectionStart - richTextBox->GetFirstCharIndexOfCurrentLine() + 1);
			}
			statusLabel->Text = status->ToString();
		}
		private: void toggleFontView()//starea butoanelor
		{
			if (richTextBox->SelectionFont != nullptr)
			{
				cmdBold->Checked = richTextBox->SelectionFont->Bold;
				cmdItalic->Checked = richTextBox->SelectionFont->Italic;
			}
		}
		
		private: System::Void cmdUnderline_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::Drawing::FontStyle newStyle = richTextBox->SelectionFont->Style;
			int intStyle = static_cast<int>(newStyle);
			if (richTextBox->SelectionFont->Underline)
			{
				intStyle &= ~static_cast<int>(System::Drawing::FontStyle::Underline);
			}
			else
			{
				intStyle |= static_cast<int>(System::Drawing::FontStyle::Underline);
			}
			newStyle = static_cast<System::Drawing::FontStyle>(intStyle);
			richTextBox->SelectionFont = gcnew System::Drawing::Font(richTextBox->SelectionFont, newStyle);
			toggleFontView();
		}

		private: System::Void cmdBold_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::Drawing::FontStyle newStyle = richTextBox->SelectionFont->Style;//obtin font-ul
			int intStyle = static_cast<int>(newStyle);
			if (richTextBox->SelectionFont->Bold)//daca e bold se dezactiveaza
			{
				intStyle &= ~static_cast<int>(System::Drawing::FontStyle::Bold);
			}
			else//daca nu este bold se activeaza
			{
				intStyle |= static_cast<int>(System::Drawing::FontStyle::Bold);
			}
			newStyle = static_cast<System::Drawing::FontStyle>(intStyle);
			richTextBox->SelectionFont = gcnew System::Drawing::Font(richTextBox->SelectionFont, newStyle);
			toggleFontView();
		}
		private: System::Void cmdItalic_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::Drawing::FontStyle newStyle = richTextBox->SelectionFont->Style;
			int intStyle = static_cast<int>(newStyle);
			if (richTextBox->SelectionFont->Italic)
			{
				intStyle &= ~static_cast<int>(System::Drawing::FontStyle::Italic);
			}
			else
			{
				intStyle |= static_cast<int>(System::Drawing::FontStyle::Italic);
			}
			newStyle = static_cast<System::Drawing::FontStyle>(intStyle);
			richTextBox->SelectionFont = gcnew System::Drawing::Font(richTextBox->SelectionFont, newStyle);
			toggleFontView();
		}

		private: System::Void cmdGreen_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (richTextBox->SelectionColor == System::Drawing::Color::Green)
			{
				richTextBox->SelectionColor = System::Drawing::Color::Black;
			}
			else
			{
				richTextBox->SelectionColor = System::Drawing::Color::Green;
			}
			toggleFontView();
		}

		private: System::Void cmdAlignLeft_Click(System::Object^ sender, System::EventArgs^ e)
		{
			richTextBox->SelectionAlignment = HorizontalAlignment::Left;
			toggleFontView();
		}

		private: System::Void cmdAlignCenter_Click(System::Object^ sender, System::EventArgs^ e)
		{
			richTextBox->SelectionAlignment = HorizontalAlignment::Center;
			toggleFontView();
		}

		private: System::Void cmdAlignRight_Click(System::Object^ sender, System::EventArgs^ e)
		{
			richTextBox->SelectionAlignment = HorizontalAlignment::Right;
			toggleFontView();
		}

		private: System::Void cmdRed_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (richTextBox->SelectionColor == System::Drawing::Color::Red)
			{
				richTextBox->SelectionColor = System::Drawing::Color::Black;
			}
			else
			{
				richTextBox->SelectionColor = System::Drawing::Color::Red;
			}
			toggleFontView();
		}
#pragma endregion
	private: System::Void ShareButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->file_Name != "New File") {
			ShareForm^ shareForm = gcnew ShareForm(this->user, connectSocket, this->file_Name);
			shareForm->ShowDialog();
		}
		else {
			MessageBox::Show("Eroare! Nu puteti distribui un fisier nesalvat!");
		}
	}
};
}
