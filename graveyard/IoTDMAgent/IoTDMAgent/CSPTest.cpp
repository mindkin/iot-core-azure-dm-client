/*
Copyright 2017 Microsoft
Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include "IoTDMService.h"
#include "LocalMachine\CSPs\MdmProvision.h"
#include "LocalMachine\CSPs\EnterpriseModernAppManagementCSP.h"

using namespace std;

int main(Platform::Array<Platform::String^>^ args)
{
    if (args->Length != 2)
    {
        wcout << L"Too few parameters." << endl;
        wcout << L"Usage:" << endl;
        wcout << L"CSPTest.exe 1" << endl;
        wcout << L"    Lists installed apps." << endl;
        wcout << endl;
        wcout << L"CSPTest.exe 2" << endl;
        wcout << L"    Installs hardcoded app." << endl;
        wcout << endl;
        wcout << L"CSPTest.exe 3" << endl;
        wcout << L"    Uninstalls hardcoded app." << endl;
        wcout << endl;
        wcout << L"CSPTest.exe xyz.synmc" << endl;
        wcout << L"    Applies xyz.syncml." << endl;
        wcout << endl;
        return 1;
    }

    if (args[1] == L"1")
    {
        auto ver = EnterpriseModernAppManagementCSP::GetInstalledApps();
    }
    else if (args[1] == L"2")
    {
        std::vector<std::wstring> dependencies = {
            LR"(C:\projects\AppXSample\AppPackages\AppXSample_1.0.0.0_Debug_Test\Dependencies\x86\Microsoft.NET.CoreRuntime.1.0.appx)",
            LR"(C:\projects\AppXSample\AppPackages\AppXSample_1.0.0.0_Debug_Test\Dependencies\x86\Microsoft.VCLibs.x86.Debug.14.00.appx)"
        };

        auto packageUri = LR"(C:\projects\AppXSample\AppPackages\AppXSample_1.0.0.0_Debug_Test\AppXSample_1.0.0.0_x86_x64_arm_Debug.appxbundle)";

        EnterpriseModernAppManagementCSP::InstallApp(L"0de8badf-807f-4641-9cb9-95e4f9c34fef_9nthh9tntkkay", packageUri, dependencies);
    }
    else if (args[1] == L"3")
    {
        EnterpriseModernAppManagementCSP::UninstallApp(L"0de8badf-807f-4641-9cb9-95e4f9c34fef_9nthh9tntkkay");
    }
    else
    {
        wstring fileName = args[1]->Data();
        string requestSyncML;
        ifstream syncMLStream(fileName);
        if (syncMLStream.is_open())
        {
            string line;
            while (getline(syncMLStream, line))
            {
                requestSyncML += line;
            }
            syncMLStream.close();
        }

        wstring requestSyncMLW = Utils::MultibyteToWide(requestSyncML.c_str());
        wcout << L"Submitting SyncML:" << endl;
        wcout << endl;
        wcout << requestSyncMLW << endl;
        wcout << endl;

        wstring responseSyncMLW;
        MdmProvision::RunSyncML(L"", requestSyncMLW, responseSyncMLW);
        wcout << L"Response SyncML:" << endl;
        wcout << endl;
        wcout << responseSyncMLW << endl;
        wcout << endl;
    }

    return 0;
}
