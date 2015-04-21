#include <nan.h>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <list>

#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>

using namespace std;

using namespace v8;
using namespace node;

class Worker : public NanAsyncWorker
{
  public:
    Worker::Worker(NanCallback *callback);
    Worker::~Worker();
    void Execute();
    void Notify ();
};

#pragma data_seg(".SHARED")
HHOOK hHook = 0;
bool alt = false;
bool ctrl = false;
bool shift = false;
bool winkey = false;
Worker *_worker = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.SHARED,RWS")

HMODULE GetCurrentModule()
{ // NB: XP+ solution!
  HMODULE hModule = NULL;
  GetModuleHandleEx(
    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
    (LPCTSTR)GetCurrentModule,
    &hModule);

  return hModule;
}

LRESULT WINAPI MyProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode >= 0) {

    PKBDLLHOOKSTRUCT hookStruct = (PKBDLLHOOKSTRUCT)lParam;

    if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN || wParam == WM_SYSKEYUP || wParam == WM_KEYUP) {
        int code = hookStruct->vkCode;

        if (code == VK_LMENU || code == VK_RMENU) {
            alt = (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN);
        } else if (code == VK_LSHIFT || code == VK_RSHIFT) {
            shift = (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN);
        } else if (code == VK_LCONTROL || code == VK_RCONTROL) {
            ctrl = (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN);
        }else if (code == VK_LWIN || code == VK_RWIN) {
            winkey = (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN);
        } else {
            fstream myfile;
            myfile.open ("E:\\example.txt", fstream::app|fstream::out);
            myfile << "Alt: " << alt << "\n";
            myfile << "Ctrl: " << ctrl << "\n";
            myfile << "Shift: " << shift << "\n";
            myfile << "Winkey: " << winkey << "\n";
            myfile << "Down: " << (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN) << "\n";
            myfile << MapVirtualKey(code, MAPVK_VK_TO_CHAR) << "\n";
            myfile << "\n";
            myfile.close();
            _worker->Notify();
        }
    }

  }

  // call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
  return CallNextHookEx(hHook, nCode, wParam, lParam);
}


Worker::Worker(NanCallback *callback)
  : NanAsyncWorker(callback)
{
}
Worker::~Worker() {}

void Worker::Execute() {
  HINSTANCE hInstance = GetCurrentModule();

  hHook = SetWindowsHookEx(WH_KEYBOARD_LL, &MyProc, hInstance, NULL);

  MSG message;
  while(GetMessage(&message, NULL, 0, 0) != 0) {
    TranslateMessage( &message );
    DispatchMessage( &message );
   }
}

void Worker::Notify () {
  NanScope();
  callback->Call(0, NULL);
}

NAN_METHOD(Listen) {
  NanScope();

  //Local<Object> returnObj = NanNew<Object>();

  //HINSTANCE hInstance = GetModuleHandle(NULL);

  NanCallback* dummyCallback = new NanCallback(args[0].As<Function>());
  NanAsyncWorker* workerThread = new Worker(dummyCallback);
  _worker = (Worker*)workerThread;
  NanAsyncQueueWorker(workerThread);

  NanReturnUndefined();

  /*int lastError = GetLastError();
//
//  if (lastError != 0) {
//    LPWSTR lpMsg = NULL;
//    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, lastError, 0, (LPWSTR)&lpMsg, 0, NULL);
//    char msg[1024];
//    wcstombs(msg, lpMsg, 1024);
//
//    returnObj->Set(NanNew<String>("error"), NanNew<String>(msg));
//    returnObj->Set(NanNew<String>("errorCode"), NanNew<Number>(lastError));
//  } else {
//    returnObj->Set(NanNew<String>("result"), NanNew<Number>((unsigned int)(hHook)));
//  }*/
//
//  NanReturnValue(returnObj);
}

void init(Handle<Object> exports) {
  exports->Set(NanNew<String>("listen"),
    NanNew<FunctionTemplate>(Listen)->GetFunction());
}

NODE_MODULE(keybindings, init)
