#include "UserConnectInterface.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array <String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	POOP::UserConnectInterface form;
	Application::Run(%form);

}

