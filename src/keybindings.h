#include <nan.h>

using namespace std;

using namespace v8;
using namespace node;

class Worker : public NanAsyncWorker
{
    public:
        NanCallback *_callback;
}