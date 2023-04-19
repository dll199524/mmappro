//
// Created by Administrator on 2023/2/5.
//

#ifndef MMAPPRO_FILELOGGER_H
#define MMAPPRO_FILELOGGER_H

#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <jni.h>

class FileLogger {
public:
    FileLogger(const char *logPath, int maxFileSize);
    ~FileLogger();

public:
    //当前log文件
    char *logPath;
    //每次加载的大小 页大小的整数倍
    int increaseSize;
    //写入的位置
    int dataDos = 0;
    //mmap映射的内存大小
    int mmapSize = 0;
    char *mmapPtr = nullptr;
    //文件允许的最大范围
    int maxFileSize;

public:
    void mmapFile(int start, int end);
    void writeDate(const char *data, int dataLen);
    int getLogFileSize();
};


#endif //MMAPPRO_FILELOGGER_H
