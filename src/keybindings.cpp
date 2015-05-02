#include <nan.h>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <list>

#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>

using namespace std;

using namespace v8;
using namespace node;

void ReadKeyboard( BYTE* keys )
{
  for (int x = 0; x < 256; x++) {
    keys[x] = ((char) (GetAsyncKeyState(x) >> 8));
  }
}

NAN_METHOD(GetKeyboardState) {
  NanScope();

  Local<Object> returnObj = NanNew<Object>();

  BYTE keys[256];
  ReadKeyboard(keys);


  int lastError = GetLastError();

  if (lastError != 0) {
    LPWSTR lpMsg = NULL;
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, lastError, 0, (LPWSTR)&lpMsg, 0, NULL);
    char msg[1024];
    wcstombs(msg, lpMsg, 1024);

    returnObj->Set(NanNew<String>("error"), NanNew<String>(msg));
    returnObj->Set(NanNew<String>("errorCode"), NanNew<Number>(lastError));
  } else {
    Local<Array> returnValue = NanNew<Array>();

    for (int x = 0; x < 256; x++) {
        returnValue->Set(x, keys[x] ? NanTrue() : NanFalse());
    }

    returnObj->Set(NanNew<String>("keys"), returnValue);
  }

  NanReturnValue(returnObj);
}

void init(Handle<Object> exports) {
  exports->Set(NanNew<String>("getKeyboardState"),
    NanNew<FunctionTemplate>(GetKeyboardState)->GetFunction());
}

NODE_MODULE(keybindings, init)
