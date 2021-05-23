import os
import io
import re
import glob

rootPath = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
includePath = os.path.join(rootPath, 'Include')
sourcePath = os.path.join(rootPath, 'Source')
outPath = os.path.join(rootPath, 'Compact')
incPattern = re.compile(r'\s*#include\s*<Eclog/(.*\.h)>')
ifPattern = re.compile(r'\s*#ifndef\s+ECLOG_CPP_(.*)_H_')
defPattern = re.compile(r'\s*#define\s+ECLOG_CPP_(.*)_H_')
endIfPattern = re.compile(r'\s*#endif\s*//\s*ECLOG_CPP_(.*)_H_')

headerSet = set([])

def isEmptyLine(line):
    return not line.strip()

class Target:
    def __init__(self, path):
        self.path = path
        self.info = None
        self.includeGuard = None
        self.headers = []
        self.lines = []
    def setInfo(self, info):
        self.info = info
    def setIncludeGuard(self, includeGuard):
        self.includeGuard = includeGuard
    def addLine(self, line):
        if isEmptyLine(line):
            if len(self.lines) > 0 and isEmptyLine(self.lines[-1]):
                return
        self.lines.append(line)
    def addHeaderFile(self, name):
        if name not in self.headers:
            self.headers.append(name)
    def write(self):
        f = io.open(self.path, 'w', newline='\n', encoding='utf-8')
        if self.info:
            f.write(self.info)
            f.write(u'\n')
        if self.includeGuard:
            f.write(u'#ifndef ' + self.includeGuard + u'\n')
            f.write(u'#define ' + self.includeGuard + u'\n')
            f.write(u'\n')
        if len(self.headers) > 0:
            for header in self.headers:
                f.write(u'#include <' + header + u'>\n')
            f.write(u'\n')
        while len(self.lines) > 0:
            if isEmptyLine(self.lines[0]):
                self.lines = self.lines[1:]
            elif isEmptyLine(self.lines[-1]):
                self.lines = self.lines[:-1]
            else:
                break
        if len(self.lines) > 0:
            for line in self.lines:
                f.write(line)
            f.write(u'\n')
        if self.includeGuard:
            f.write(u'#endif // ' + self.includeGuard + u'\n')
        f.write(u'\n')

def addHeaderFile(target, name):
    f = io.open(os.path.join(includePath, name), 'r', encoding='utf-8')
    info = True
    for line in f:
        if info:
            if line.startswith(u'//'):
                continue
            else:
                info = False
        m = ifPattern.match(line)
        if m:
            header = m.group(1)
            if header in headerSet:
                return
            else:
                headerSet.add(header)
                continue
        m = incPattern.match(line)
        if m:
            addHeaderFile(target, 'Eclog/' + m.group(1))
            continue
        if defPattern.match(line):
            continue
        if endIfPattern.match(line):
            return
        target.addLine(line)

def addSourceFile(target, name):
    f = io.open(os.path.join(sourcePath, name), 'r', encoding='utf-8')
    info = True
    for line in f:
        if info:
            if line.startswith(u'//'):
                continue
            else:
                info = False
        m = incPattern.match(line)
        if m:
            addHeaderFile(target, 'Eclog/' + m.group(1))
            continue
        target.addLine(line)

def addHeaderFiles(target):
    addHeaderFile(target, 'Eclog/Error.h')
    addHeaderFile(target, 'Eclog/UTF8Decoder.h')
    addHeaderFile(target, 'Eclog/UTF8Encoder.h')
    addHeaderFile(target, 'Eclog/Parse.h')
    addHeaderFile(target, 'Eclog/Renderer.h')
    addHeaderFile(target, 'Eclog/ObjectRenderer.h')
    addHeaderFile(target, 'Eclog/ArrayRenderer.h')
    addHeaderFile(target, 'Eclog/DynamicParsingBuffer.h')
    addHeaderFile(target, 'Eclog/InplaceParsingBuffer.h')
    addHeaderFile(target, 'Eclog/MemoryInputStream.h')
    addHeaderFile(target, 'Eclog/StdStreamInputStream.h')
    addHeaderFile(target, 'Eclog/MemoryOutputStream.h')
    addHeaderFile(target, 'Eclog/StdStreamOutputStream.h')
    addHeaderFile(target, 'Eclog/StdStringOutputStream.h')
    addHeaderFile(target, 'Eclog/Document.h')

def addSourceFiles(target):
    addSourceFile(target, 'Error.cpp')
    addSourceFile(target, 'DoubleConversion.cpp')
    addSourceFile(target, 'UTF8Decoder.cpp')
    addSourceFile(target, 'UTF8Encoder.cpp')
    addSourceFile(target, 'Null.cpp')
    addSourceFile(target, 'Parse.cpp')
    addSourceFile(target, 'Renderer.cpp')

info = (u'// Eclog-CPP\n'
        u'// Copyright (c) Vallest Systems LLC. All Rights Reserved.\n'
        u'// Licensed under the MIT License.\n'
        u'//\n'
        u'// This file is auto-generated, do not edit.\n')

headerFileTarget = Target(os.path.join(outPath, 'Eclog.h'))
sourceFileTarget = Target(os.path.join(outPath, 'Eclog.cpp'))

headerFileTarget.setInfo(info)
headerFileTarget.setIncludeGuard(u'ECLOG_CPP_H_')

sourceFileTarget.setInfo(info)
sourceFileTarget.addHeaderFile(u'Eclog.h')

addHeaderFiles(headerFileTarget)
addSourceFiles(sourceFileTarget)

headerFileTarget.write()
sourceFileTarget.write()

