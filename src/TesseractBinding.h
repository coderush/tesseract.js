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

 #ifndef TESSERACTBINDING_H
 #define TESSERACTBINDING_H

 #include <baseapi.h>
 #include <v8.h>
 #include <node.h>
 #include <allheaders.h>

#define REQUIRE_ARG_NUM(num)                                          \
  if (args.Length() < (num))                                          \
    return ThrowException(Exception::Error(                           \
    String::New("At least " #num " argument(s) should be defined.")))

#define REQUIRE_STRING(VAR, pos)                          \
  if (args.Length() <= (pos) || !args[pos]->IsString())   \
    return ThrowException(Exception::TypeError(           \
    String::New("Argument " #pos " must be a string")));  \
  String::Utf8Value VAR(args[pos]->ToString());

 using namespace v8;

 class TesseractBinding : public node::ObjectWrap {
    
    public:
    static void Initialize(Handle<Object> target);

    private:
    /* Constructor. */
    TesseractBinding();
    
    /* Destructor. */
    ~TesseractBinding();

    /* Basic API's */
    static Handle<Value> New(const Arguments& args);
    static Handle<Value> Init(const Arguments& args);
    static Handle<Value> SetImage(const Arguments& args);
    static Handle<Value> ProcessImage(const Arguments& args);
    static Handle<Value> GetText(const Arguments& args);
    static Handle<Value> Close(const Arguments& args);
    static Handle<Value> End(const Arguments& args);

    tesseract::TessBaseAPI * t_api;
 };

 #endif