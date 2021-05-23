#include "Tests.h"
#include "UnitTesting.h"

#include <dispatch/dispatch.h>

#include <string>
#include <fstream>

#include <stdio.h>
#include <stdarg.h>

UITextView* g_tv;

void runTestCasesAsync(UITextView* tv)
{
    g_tv = tv;

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        runTestCases();
    });
}

class StreamBuf : public std::streambuf {
protected:
    int_type overflow(int_type ch)
    {
        buf_.push_back(traits_type::to_char_type(ch));
        
        if (ch == traits_type::to_int_type('\n'))
        {
            NSString* str = [NSString stringWithCString:buf_.c_str() encoding:[NSString defaultCStringEncoding]];

            dispatch_async(dispatch_get_main_queue(), ^(void){
                g_tv.text = [g_tv.text stringByAppendingString:str];
            });

            buf_.clear();
        }

        return ch;
    }

private:
    std::string buf_;
};

std::ostream& getOutStream()
{
    static StreamBuf buf;
    static std::ostream os(&buf);

    return os;
}

bool loadTextFile(const char* filename, std::string& text)
{
    std::string fullPath = std::string([[[NSBundle mainBundle] resourcePath] UTF8String]) + "/" + filename;

    std::fstream stream(fullPath, std::ios::in|std::ios::binary);

    if (!stream.is_open()) {
        return false;
    }

    stream.seekg(0, std::ios::end);

    std::streamsize size = stream.tellg();

    stream.seekg(0, std::ios::beg);

    text.resize((size_t)size);

    if (!stream.read(&text[0], (size_t)size)) {
        return false;
    }

    return true;
}

