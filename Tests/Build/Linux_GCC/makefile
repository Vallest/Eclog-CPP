CPPFLAGS=-g -c -ansi -Wall -std=c++98 -I../../Source -I../../../Include

Tests: DoubleConversion.o Error.o Parse.o UTF8Decoder.o UTF8Encoder.o Renderer.o Null.o cstringTests.o DebugAllocator.o DebugObject.o DocumentTests.o DoubleConversionTests.o Main.o NumberTests.o ParseTests.o PODArrayTests.o ByteArrayTests.o ParsingBufferTests.o UnitTesting.o UTF8EncodingTests.o VectorTests.o RendererTests.o dtoa.o
	@ mkdir -p ../../Bin/
	g++ -g -o ../../Bin/Tests DoubleConversion.o Error.o Parse.o UTF8Decoder.o UTF8Encoder.o Renderer.o Null.o cstringTests.o DebugAllocator.o DebugObject.o DocumentTests.o DoubleConversionTests.o Main.o NumberTests.o ParseTests.o PODArrayTests.o ByteArrayTests.o ParsingBufferTests.o UnitTesting.o UTF8EncodingTests.o VectorTests.o RendererTests.o dtoa.o

DoubleConversion.o:
	g++ $(CPPFLAGS) ../../../Source/DoubleConversion.cpp

Error.o:
	g++ $(CPPFLAGS) ../../../Source/Error.cpp

Parse.o:
	g++ $(CPPFLAGS) ../../../Source/Parse.cpp

UTF8Decoder.o:
	g++ $(CPPFLAGS) ../../../Source/UTF8Decoder.cpp

UTF8Encoder.o:
	g++ $(CPPFLAGS) ../../../Source/UTF8Encoder.cpp

Renderer.o:
	g++ $(CPPFLAGS) ../../../Source/Renderer.cpp

Null.o:
	g++ $(CPPFLAGS) ../../../Source/Null.cpp

cstringTests.o:
	g++ $(CPPFLAGS) ../../Source/cstringTests.cpp

DebugAllocator.o:
	g++ $(CPPFLAGS) ../../Source/DebugAllocator.cpp

DebugObject.o:
	g++ $(CPPFLAGS) ../../Source/DebugObject.cpp

DocumentTests.o:
	g++ $(CPPFLAGS) ../../Source/DocumentTests.cpp

DoubleConversionTests.o:
	g++ $(CPPFLAGS) ../../Source/DoubleConversionTests.cpp

Main.o:
	g++ $(CPPFLAGS) ../../Source/Main.cpp

NumberTests.o:
	g++ $(CPPFLAGS) ../../Source/NumberTests.cpp

ParseTests.o:
	g++ $(CPPFLAGS) ../../Source/ParseTests.cpp

PODArrayTests.o:
	g++ $(CPPFLAGS) ../../Source/PODArrayTests.cpp

ByteArrayTests.o:
	g++ $(CPPFLAGS) ../../Source/ByteArrayTests.cpp

ParsingBufferTests.o:
	g++ $(CPPFLAGS) ../../Source/ParsingBufferTests.cpp

UnitTesting.o:
	g++ $(CPPFLAGS) ../../Source/UnitTesting.cpp

UTF8EncodingTests.o:
	g++ $(CPPFLAGS) ../../Source/UTF8EncodingTests.cpp

VectorTests.o:
	g++ $(CPPFLAGS) ../../Source/VectorTests.cpp

RendererTests.o:
	g++ $(CPPFLAGS) ../../Source/RendererTests.cpp

dtoa.o:
	gcc -g -c -D IEEE_8087 ../../Source/dtoa.c

.PHONY: clean

clean:
	rm -f *.o ../../Bin/Tests
