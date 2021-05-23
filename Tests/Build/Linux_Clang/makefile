CPPFLAGS=-g -c -ansi -Wall -std=c++98 -I../../Source -I../../../Include

Tests: DoubleConversion.o Error.o Parse.o UTF8Decoder.o UTF8Encoder.o Renderer.o Null.o cstringTests.o DebugAllocator.o DebugObject.o DocumentTests.o DoubleConversionTests.o Main.o NumberTests.o ParseTests.o PODArrayTests.o ByteArrayTests.o ParsingBufferTests.o UnitTesting.o UTF8EncodingTests.o VectorTests.o RendererTests.o dtoa.o
	@ mkdir -p ../../Bin/
	clang -g -lstdc++ -lm -o ../../Bin/Tests DoubleConversion.o Error.o Parse.o UTF8Decoder.o UTF8Encoder.o Renderer.o Null.o cstringTests.o DebugAllocator.o DebugObject.o DocumentTests.o DoubleConversionTests.o Main.o NumberTests.o ParseTests.o PODArrayTests.o ByteArrayTests.o ParsingBufferTests.o UnitTesting.o UTF8EncodingTests.o VectorTests.o RendererTests.o dtoa.o

DoubleConversion.o:
	clang $(CPPFLAGS) ../../../Source/DoubleConversion.cpp

Error.o:
	clang $(CPPFLAGS) ../../../Source/Error.cpp

Parse.o:
	clang $(CPPFLAGS) ../../../Source/Parse.cpp

UTF8Decoder.o:
	clang $(CPPFLAGS) ../../../Source/UTF8Decoder.cpp

UTF8Encoder.o:
	clang $(CPPFLAGS) ../../../Source/UTF8Encoder.cpp

Renderer.o:
	clang $(CPPFLAGS) ../../../Source/Renderer.cpp

Null.o:
	clang $(CPPFLAGS) ../../../Source/Null.cpp

cstringTests.o:
	clang $(CPPFLAGS) ../../Source/cstringTests.cpp

DebugAllocator.o:
	clang $(CPPFLAGS) ../../Source/DebugAllocator.cpp

DebugObject.o:
	clang $(CPPFLAGS) ../../Source/DebugObject.cpp

DocumentTests.o:
	clang $(CPPFLAGS) ../../Source/DocumentTests.cpp

DoubleConversionTests.o:
	clang $(CPPFLAGS) ../../Source/DoubleConversionTests.cpp

Main.o:
	clang $(CPPFLAGS) ../../Source/Main.cpp

NumberTests.o:
	clang $(CPPFLAGS) ../../Source/NumberTests.cpp

ParseTests.o:
	clang $(CPPFLAGS) ../../Source/ParseTests.cpp

PODArrayTests.o:
	clang $(CPPFLAGS) ../../Source/PODArrayTests.cpp

ByteArrayTests.o:
	clang $(CPPFLAGS) ../../Source/ByteArrayTests.cpp

ParsingBufferTests.o:
	clang $(CPPFLAGS) ../../Source/ParsingBufferTests.cpp

UnitTesting.o:
	clang $(CPPFLAGS) ../../Source/UnitTesting.cpp

UTF8EncodingTests.o:
	clang $(CPPFLAGS) ../../Source/UTF8EncodingTests.cpp

VectorTests.o:
	clang $(CPPFLAGS) ../../Source/VectorTests.cpp

RendererTests.o:
	clang $(CPPFLAGS) ../../Source/RendererTests.cpp

dtoa.o:
	clang -g -c -D IEEE_8087 ../../Source/dtoa.c

.PHONY: clean

clean:
	rm -f *.o ../../Bin/Tests
