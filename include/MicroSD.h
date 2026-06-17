//
// Created by destin on 6/17/26.
//

#pragma once

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define PIN_MICROSD_CS 5

class MicroSD
{
public:
    void begin();
    void listDir(fs::FS& fs, const char* dirname, uint8_t levels);
    void createDir(fs::FS& fs, const char* path);
    void removeDir(fs::FS& fs, const char* path);
    void readFile(fs::FS& fs, const char* path);
    void writeFile(fs::FS& fs, const char* path, const char* message);
    void appendFile(fs::FS& fs, const char* path, const char* message);
    void renameFile(fs::FS& fs, const char* path1, const char* path2);
    void deleteFile(fs::FS& fs, const char* path);
};
