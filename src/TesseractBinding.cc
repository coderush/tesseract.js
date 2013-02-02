/*
 * Copyright (c) 2013 Sumit Ranjan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <v8.h>
#include <node.h>
#include <stdio.h>
#include "TesseractBinding.h"

using namespace v8;

void TesseractBinding::Initialize(Handle<Object> target) {

  	Local<FunctionTemplate> constructor_template = FunctionTemplate::New(New);
    constructor_template->SetClassName(String::NewSymbol("TesseractBinding"));
    constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
    Local<ObjectTemplate> proto = constructor_template->PrototypeTemplate();
    proto->Set(String::NewSymbol("close"),
               FunctionTemplate::New(Close)->GetFunction());
    proto->Set(String::NewSymbol("end"),
               FunctionTemplate::New(End)->GetFunction());
    proto->Set(String::NewSymbol("init"),
               FunctionTemplate::New(Init)->GetFunction());
    proto->Set(String::NewSymbol("setImage"),
               FunctionTemplate::New(SetImage)->GetFunction());
    proto->Set(String::NewSymbol("processImage"),
               FunctionTemplate::New(ProcessImage)->GetFunction());
    proto->Set(String::NewSymbol("getText"),
               FunctionTemplate::New(GetText)->GetFunction());
    target->Set(String::NewSymbol("TesseractBinding"),
                Persistent<Function>::New(constructor_template->GetFunction()));


}

TesseractBinding::TesseractBinding() {
   t_api = new tesseract::TessBaseAPI();
};


TesseractBinding::~TesseractBinding() {
   t_api->Clear();
   t_api->End();
};

Handle<Value> TesseractBinding::New(const Arguments& args) {
	HandleScope scope;
	TesseractBinding* obj = new TesseractBinding();
    obj->Wrap(args.This());
    return args.This();
}

Handle<Value> TesseractBinding::Init(const Arguments& args) {
  HandleScope scope;
  REQUIRE_STRING(arg_lang, 0);
  char *lang;
  if (arg_lang.length()) {
    lang = strdup(*arg_lang);
  } else {
    lang = (char *) "eng";
  }
  TesseractBinding* obj = ObjectWrap::Unwrap<TesseractBinding>(args.This());
  int ret = obj->t_api->Init(NULL, lang);
  return scope.Close(Integer::New(ret));
}

Handle<Value> TesseractBinding::SetImage(const Arguments& args) {
HandleScope scope;
REQUIRE_ARG_NUM(1);
PIX* pix;
if (args[0]->IsString()) {
   pix = pixRead(strdup(*(String::Utf8Value(args[0]))));
} else {
   	return ThrowException(Exception::Error(
   	String::New("Please enter a valid image location.")));
}
if (pix == NULL) {
	return ThrowException(Exception::Error(
	String::New("Error retrieve image from the given location.")));
}
TesseractBinding* obj = ObjectWrap::Unwrap<TesseractBinding>(args.This());
obj->t_api->SetImage(pix);
return scope.Close(Null());
}

Handle<Value> TesseractBinding::ProcessImage(const Arguments& args) {
  HandleScope scope;
  TesseractBinding* obj = ObjectWrap::Unwrap<TesseractBinding>(args.This());
  obj->t_api->Recognize(NULL);
  return scope.Close(Null());
}

Handle<Value> TesseractBinding::GetText(const Arguments& args) {
  HandleScope scope;
  TesseractBinding* obj = ObjectWrap::Unwrap<TesseractBinding>(args.This());
  char *text = obj->t_api->GetUTF8Text();
  return scope.Close(String::New(text));
}

Handle<Value> TesseractBinding::Close(const Arguments& args) {
  HandleScope scope;
  TesseractBinding* obj = ObjectWrap::Unwrap<TesseractBinding>(args.This());
  obj->t_api->Clear();
  return scope.Close(Null());
}

Handle<Value> TesseractBinding::End(const Arguments& args) {
  HandleScope scope;
  TesseractBinding* obj = ObjectWrap::Unwrap<TesseractBinding>(args.This());
  obj->t_api->End();
  return scope.Close(Null());
}
