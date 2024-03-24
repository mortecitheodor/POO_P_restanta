#pragma once
#include "InputForm.h"

namespace POOP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EditFile
	/// </summary>
	public ref class EditFile : public System::Windows::Forms::Form
	{

	public:
		SOCKET connectSocket;
		User^ user;
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
	protected:
	private: System::Windows::Forms::ColorDialog^ colorDialog;
	private: System::Windows::Forms::FontDialog^ fontDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::ToolStripButton^ cmdItalic;
	private: System::Windows::Forms::ToolStripButton^ cmdBold;
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
			this->cmdSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->ShareButton = (gcnew System::Windows::Forms::ToolStripButton());
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
			this->cmdItalic->Size = System::Drawing::Size(23, 20);
			this->cmdItalic->Text = L"Italic";
			this->cmdItalic->Click += gcnew System::EventHandler(this, &EditFile::cmdItalic_Click);
			// 
			// cmdBold
			// 
			this->cmdBold->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdBold->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdBold.Image")));
			this->cmdBold->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdBold->Name = L"cmdBold";
			this->cmdBold->Size = System::Drawing::Size(23, 20);
			this->cmdBold->Text = L"Bold";
			this->cmdBold->Click += gcnew System::EventHandler(this, &EditFile::cmdBold_Click);
			// 
			// cmdSave
			// 
			this->cmdSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->cmdSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cmdSave.Image")));
			this->cmdSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cmdSave->Name = L"cmdSave";
			this->cmdSave->Size = System::Drawing::Size(23, 20);
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
			this->toolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->cmdSave, this->cmdBold,
					this->cmdItalic, this->ShareButton
			});
			this->toolStrip->Location = System::Drawing::Point(0, 0);
			this->toolStrip->Name = L"toolStrip";
			this->toolStrip->Padding = System::Windows::Forms::Padding(5);
			this->toolStrip->Size = System::Drawing::Size(784, 33);
			this->toolStrip->TabIndex = 4;
			this->toolStrip->Text = L"toolStrip";
			// 
			// ShareButton
			// 
			this->ShareButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->ShareButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShareButton.Image")));
			this->ShareButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->ShareButton->Name = L"ShareButton";
			this->ShareButton->Size = System::Drawing::Size(23, 20);
			this->ShareButton->Text = L"toolStripButton1";
			this->ShareButton->ToolTipText = L"Share";
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
			this->Text = L"EditFile";
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->toolStrip->ResumeLayout(false);
			this->toolStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		private: void cmdSave_Click(System::Object^ sender, System::EventArgs^ e)
		{
			// Codul pentru salvarea documentului
			POOP::InputForm^ in = gcnew POOP::InputForm(user, connectSocket);
			in->ShowDialog();
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
		private: void toggleFontView()
		{
			if (richTextBox->SelectionFont != nullptr)
			{
				cmdBold->Checked = richTextBox->SelectionFont->Bold;

				cmdItalic->Checked = richTextBox->SelectionFont->Italic;
			}
		}
		private: System::Void cmdBold_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::Drawing::FontStyle newStyle = richTextBox->SelectionFont->Style;
			int intStyle = static_cast<int>(newStyle);
			if (richTextBox->SelectionFont->Bold)
			{
				intStyle &= ~static_cast<int>(System::Drawing::FontStyle::Bold);
			}
			else
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
			newStyle = static_cast<System::Drawing::FontStyle>(intStyle); // Update the FontStyle with the new intStyle
			richTextBox->SelectionFont = gcnew System::Drawing::Font(richTextBox->SelectionFont, newStyle);
			toggleFontView();
		}
#pragma endregion
};
}
