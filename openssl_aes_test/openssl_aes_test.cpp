// openssl_aes_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <mscoree.h>
#include <metahost.h>
#include <chrono>


#pragma comment(lib, "mscoree.lib")

using namespace std;

class doDotNet {
public:

	// Initialize the CLR
	ICLRMetaHost* pMetaHost = NULL;
	ICLRRuntimeInfo* pRuntimeInfo = NULL;
	ICLRRuntimeHost* pClrRuntimeHost = NULL;

	void SetupCallManagedCode_Framework() {

		HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pMetaHost);
		if (SUCCEEDED(hr)) {

			hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)&pRuntimeInfo);

			if (SUCCEEDED(hr)) {
				hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&pClrRuntimeHost);
				if (SUCCEEDED(hr)) {
					pClrRuntimeHost->Start();
				}
			}
		}
	}

	void DoStuff() {

		DWORD dwReturnValue;

		HRESULT hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(
			L"C:\\Users\\jeff\\Source\\Repos\\RunProgramStub\\TestCallToNetFromNative\\bin\\Debug\\TestCallToNetFromNative.dll",
			L"TestCallToNetFromNative.Class1",
			L"pwzMethodName",
			L"lOwer tExt", &dwReturnValue);

		if (SUCCEEDED(hr)) {
			std::cout << "Hello World!\n";
			std::cout << dwReturnValue << "\n";
			// Method executed successfully
			// You can check the return value here if needed
		}
		else {
			std::cout << "Operation failed. HRESULT: 0x" << std::hex << hr << std::endl;

			// Extract the severity, facility, and error code
			int severity = (hr >> 31) & 0x1;
			int facility = (hr >> 16) & 0x7FF;
			int error = hr & 0xFFFF;

			std::cout << "Severity: " << severity << std::endl;
			std::cout << "Facility: " << facility << std::endl;
			std::cout << "Error code: " << error << std::endl;
		}
	}

	void CloseCallManagedCode_Framework() {
		// Cleanup
		pClrRuntimeHost->Stop();

		// Release COM objects
		if (pMetaHost)
			pMetaHost->Release();
		if (pRuntimeInfo)
			pRuntimeInfo->Release();
		if (pClrRuntimeHost) {
			pClrRuntimeHost->Release();
		}
	}


};





void CallManagedCode_Framework() {
	// Initialize the CLR
	ICLRMetaHost* pMetaHost = NULL;
	ICLRRuntimeInfo* pRuntimeInfo = NULL;
	ICLRRuntimeHost* pClrRuntimeHost = NULL;


	HRESULT hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pMetaHost);
	if (SUCCEEDED(hr)) {

		hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)&pRuntimeInfo);

		if (SUCCEEDED(hr)) {
			hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&pClrRuntimeHost);
			if (SUCCEEDED(hr)) {
				pClrRuntimeHost->Start();
				// Load and execute your managed code
				DWORD dwReturnValue;

				hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(
					L"C:\\Users\\jeff\\Source\\Repos\\RunProgramStub\\TestCallToNetFromNative\\bin\\Debug\\TestCallToNetFromNative.dll",
					L"TestCallToNetFromNative.Class1",
					L"pwzMethodName",
					L"lOwer tExt", &dwReturnValue);

				if (SUCCEEDED(hr)) {
					std::cout << "Hello World!\n";
					std::cout << dwReturnValue << "\n";
					// Method executed successfully
					// You can check the return value here if needed
				}
				else {
					std::cout << "Operation failed. HRESULT: 0x" << std::hex << hr << std::endl;

					// Extract the severity, facility, and error code
					int severity = (hr >> 31) & 0x1;
					int facility = (hr >> 16) & 0x7FF;
					int error = hr & 0xFFFF;

					std::cout << "Severity: " << severity << std::endl;
					std::cout << "Facility: " << facility << std::endl;
					std::cout << "Error code: " << error << std::endl;
				}

				// Cleanup
				pClrRuntimeHost->Stop();

				// Don't forget error handling and cleanup
			}
		}
	}

	// Release COM objects
	if (pMetaHost)
		pMetaHost->Release();
	if (pRuntimeInfo)
		pRuntimeInfo->Release();
	if (pClrRuntimeHost) {
		pClrRuntimeHost->Release();
	}
}

typedef void(*ManagedFunction)();

//void testNetCore() {
//	HMODULE hMod = LoadLibrary(TEXT("C:\\Users\\jeff\\Source\\Repos\\RunProgramStub\\TestCallToNetFromNativeNet\\bin\\Debug\\net6.0\\TestCallToNetFromNativeNet.dll")); // Load your .NET Core DLL here
//	if (hMod != NULL) {
//		ManagedFunction func = (ManagedFunction)GetProcAddress(hMod, "TestCallToNetFromNativeNet.Class1.ManagedFunction");
//		if (func != NULL) {
//			func(); // Call the managed function
//		}
//		else {
//			printf("Function not found.\n");
//		}
//		FreeLibrary(hMod);
//	}
//	else {
//		printf("Failed to load library.\n");
//	}
//}


int main()
{
	/*testNetCore();
	return 0;*/

	// Initialize COM

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr)) {
		// Call managed code

		doDotNet x;



		x.SetupCallManagedCode_Framework();

		auto start = std::chrono::high_resolution_clock::now();

		x.DoStuff();
		//CallManagedCode_Framework();


		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::cout << "CoInitializeEx took " << duration << " nanoseconds" << std::endl;
		std::cout << "CoInitializeEx took " << duration / 1000000 << " ms" << std::endl;
		std::cout << "CoInitializeEx took " << duration / 1000000 / 1000 << " secs" << std::endl;

		x.CloseCallManagedCode_Framework();

		// Uninitialize COM
		CoUninitialize();




	}

	std::cout << "Done!\n";

	return 0;


}