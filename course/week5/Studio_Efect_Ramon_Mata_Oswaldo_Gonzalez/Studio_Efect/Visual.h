#pragma once
# include <string>
#include <iostream>
#include "Workspace.h"

using namespace std;


namespace Studio_Efect {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	

	


	/// <summary>
	/// Resumen de Visual
	/// </summary>
	public ref class Visual : public System::Windows::Forms::Form
	{
	public:
	

		Visual(void)
		{
			InitializeComponent();
			char * filename;
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~Visual()
		{
			if (components)
			{
				delete components;
			}
		}


	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fILEToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  eFFECTToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  eCOToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  tREMOLOToolStripMenuItem;

	protected: 

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Visual::typeid));
			this->axWindowsMediaPlayer1 = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fILEToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eFFECTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->eCOToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tREMOLOToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axWindowsMediaPlayer1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// axWindowsMediaPlayer1
			// 
			this->axWindowsMediaPlayer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->axWindowsMediaPlayer1->Enabled = true;
			this->axWindowsMediaPlayer1->Location = System::Drawing::Point(0, 24);
			this->axWindowsMediaPlayer1->Name = L"axWindowsMediaPlayer1";
			this->axWindowsMediaPlayer1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"axWindowsMediaPlayer1.OcxState")));
			this->axWindowsMediaPlayer1->Size = System::Drawing::Size(309, 270);
			this->axWindowsMediaPlayer1->TabIndex = 2;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fILEToolStripMenuItem, 
				this->eFFECTToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(309, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fILEToolStripMenuItem
			// 
			this->fILEToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->openToolStripMenuItem});
			this->fILEToolStripMenuItem->Name = L"fILEToolStripMenuItem";
			this->fILEToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->fILEToolStripMenuItem->Text = L"FILE";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Visual::openToolStripMenuItem_Click);
			// 
			// eFFECTToolStripMenuItem
			// 
			this->eFFECTToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->eCOToolStripMenuItem, 
				this->tREMOLOToolStripMenuItem});
			this->eFFECTToolStripMenuItem->Name = L"eFFECTToolStripMenuItem";
			this->eFFECTToolStripMenuItem->Size = System::Drawing::Size(58, 20);
			this->eFFECTToolStripMenuItem->Text = L"EFFECT";
			// 
			// eCOToolStripMenuItem
			// 
			this->eCOToolStripMenuItem->Name = L"eCOToolStripMenuItem";
			this->eCOToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->eCOToolStripMenuItem->Text = L"SLOW";
			this->eCOToolStripMenuItem->Click += gcnew System::EventHandler(this, &Visual::eCOToolStripMenuItem_Click);
			// 
			// tREMOLOToolStripMenuItem
			// 
			this->tREMOLOToolStripMenuItem->Name = L"tREMOLOToolStripMenuItem";
			this->tREMOLOToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->tREMOLOToolStripMenuItem->Text = L"TREMOLO";
			this->tREMOLOToolStripMenuItem->Click += gcnew System::EventHandler(this, &Visual::tREMOLOToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// Visual
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 17);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(309, 294);
			this->Controls->Add(this->axWindowsMediaPlayer1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Book Antiqua", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Visual";
			this->Text = L"Studio Effect Sound";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axWindowsMediaPlayer1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	public: System::Void openToolStripMenuItem_Click(System::Object^  /*sender*/, System::EventArgs^  /*e*/) {
	
	        openFileDialog1->ShowDialog();
			axWindowsMediaPlayer1->URL = openFileDialog1->FileName;
		
			CWorkspace* pWorkspace=new CWorkspace();
		     pWorkspace->filename = (char*) Marshal::StringToHGlobalAnsi(openFileDialog1->FileName).ToPointer();
			pWorkspace->LoadSLOW(pWorkspace->filename);
			pWorkspace->LoadTREMOLO(pWorkspace->filename);

			}

public: System::Void eCOToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 axWindowsMediaPlayer1->URL="slow.wav";


		 }
private: System::Void eCOToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void tREMOLOToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  axWindowsMediaPlayer1->URL="tremolo.wav";

		 }
};


}
