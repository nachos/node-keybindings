#include <v8.h>
#include <nan.h>

using namespace v8;
using namespace node;

class Emitter: ObjectWrap {
  public:
    NAN_METHOD(Init) {
      this->Wrap(args.This());
    }

    static NAN_METHOD(Ping) {
      NanScope();

      Handle<Value> argv[1] = {
          NanNew<String>("ping")
        };

      Isolate *isolate = Isolate::GetCurrent();
      MakeCallback(isolate, args.This(), "emit", 1, argv);

      NanReturnUndefined();
    }
};

NAN_METHOD(NewEmitter) {
  NanScope();

  assert(args.IsConstructCall());
  Emitter* emitter = new Emitter();
  emitter->Init(args);

  NanReturnThis();
}

void init(Handle<Object> exports) {
  NanScope();

  Local<FunctionTemplate> t = NanNew<FunctionTemplate>(NewEmitter);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(NanNew<String>("Emitter"));
  NODE_SET_PROTOTYPE_METHOD(t, "ping", Emitter::Ping);

  exports->Set(NanNew<String>("Emitter"),
      t->GetFunction());
}

NODE_MODULE(hello, init)