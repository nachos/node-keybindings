#include <nan.h>
#include <v8.h>

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

class CallbackWrapper: ObjectWrap {
  public:
    NAN_METHOD(Init);
    void Call();
};

#pragma data_seg(".SHARED")
bool alt = false;
bool ctrl = false;
bool shift = false;
bool winkey = false;
HHOOK _hHook = 0;
CallbackWrapper* _wrapper = NULL;
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
            _wrapper->Call();
        }
    }

  }

  // call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
  return CallNextHookEx(_hHook, nCode, wParam, lParam);
}

class Worker : public NanAsyncWorker
{
  public:
    Worker::Worker(NanCallback *callback) : NanAsyncWorker(callback) {
      hHook = 0;
    }

    Worker::~Worker() {}

    void Execute() {
      HINSTANCE hInstance = GetCurrentModule();

      hHook = SetWindowsHookEx(WH_KEYBOARD_LL, &MyProc, hInstance, NULL);
      _hHook = hHook;

      MSG message;
      while(GetMessage(&message, NULL, 0, 0) != 0) {
        TranslateMessage( &message );
        DispatchMessage( &message );
      }
    }

    void HandleOKCallback () {
      // Remove Hook
    }

  private:
    HHOOK hHook;
};

NAN_METHOD(CallbackWrapper::Init) {
  this->Wrap(args.This());

  NanCallback* dummyCallback = new NanCallback();
  NanAsyncWorker* workerThread = new Worker(dummyCallback);
  NanAsyncQueueWorker(workerThread);
}

void CallbackWrapper::Call() {
  HandleScope scope;

  Local<Value> callback_v = this->persistent()->Get("onKeys");
  if (!callback_v->IsFunction()) {
    return;
  }

  callback_v.As<Function>()->Call(this->persistent().As<Object>(), 0, NULL);
}

NAN_METHOD(NewEmitter) {
  NanScope();

  if (!_wrapper) {
    assert(args.IsConstructCall());
    CallbackWrapper* wrapper = new CallbackWrapper();
    wrapper->Init(args);
    _wrapper = wrapper;
  }

  NanReturnThis();
}

/*NAN_METHOD(Listen) {
  NanScope();

  //Local<Object> returnObj = NanNew<Object>();

  //HINSTANCE hInstance = GetModuleHandle(NULL);

  NanCallback* dummyCallback = new NanCallback();
  NanAsyncWorker* workerThread = new Worker(dummyCallback);
  NanAsyncQueueWorker(workerThread);

  NanReturnUndefined();
}*/

void init(Handle<Object> exports) {
  Local<FunctionTemplate> t = NanNew<FunctionTemplate>(NewEmitter);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(NanNew<String>("Emitter"));

  exports->Set(NanNew<String>("keybindings"),
      t->GetFunction());
}

NODE_MODULE(keybindings, init)
