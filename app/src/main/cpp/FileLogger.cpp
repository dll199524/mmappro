//
// Created by Administrator on 2023/2/5.
//

#include "FileLogger.h"
// 默认最小的增长大小
static int DEFAULT_INCREASE_SIZE = getpagesize() * 128;
//文件真实大小所占字节数
static int DEFAULT_POSITION_SIZE = sizeof(int);
//默认映射多少次
static int REMMAP_TIMES = 4;

FileLogger::FileLogger(const char *logPath, int maxFileSize) {

    this->logPath = (char *) (malloc(strlen(logPath) + 1));
    memcpy(this->logPath, logPath, strlen(logPath) + 1);

    increaseSize = maxFileSize / REMMAP_TIMES;
    // 最小加载 0.5M
    if (increaseSize < DEFAULT_INCREASE_SIZE)
        increaseSize = DEFAULT_INCREASE_SIZE;
    else if (increaseSize % getpagesize() != 0)
        increaseSize = (increaseSize / getpagesize() + 1) * getpagesize();

    int fileSize = getLogFileSize();
    // 是一个空文件 当前映射大小
    if (fileSize <= 0) {
        mmapSize = fileSize;
        mmapFile(0, mmapSize);
    } else {
        // 不是空文件，里面有数据
        mmapSize = fileSize;
        mmapFile(0, fileSize);
        //读取文件大小
        memcpy(&dataDos, mmapPtr + (mmapSize - DEFAULT_POSITION_SIZE - 1), DEFAULT_POSITION_SIZE);
        if (dataDos > maxFileSize) {
            if (mmapPtr != NULL) munmap(mmapPtr, mmapSize);
        }
    }
}


void FileLogger::writeDate(const char *data, int dataLen) {
    //大小不够重新映射内存
    if (dataDos + dataLen + DEFAULT_POSITION_SIZE > mmapSize) {
        if (dataDos + dataLen + DEFAULT_POSITION_SIZE > maxFileSize) {
            int maxMmapSize = dataDos + dataLen + DEFAULT_POSITION_SIZE;
            if (maxMmapSize % getpagesize() != 0) {
                maxMmapSize = ((maxMmapSize % getpagesize() + 1)) * getpagesize();
                increaseSize = maxMmapSize - mmapSize;
            }
        }
        if (mmapPtr != nullptr) munmap(mmapPtr, mmapSize);
        mmapSize += increaseSize;
        mmapFile(0, mmapSize);
    }

    //数据写入映射区域文件
    memcpy(mmapPtr + dataDos, data, dataLen);
    dataDos += dataLen;
    // 把文件的真实大小写入最后四个字节（最后面四个字节永远存放真实内容大小）
    memcpy(mmapPtr + (mmapSize - DEFAULT_POSITION_SIZE - 1), &dataDos, DEFAULT_POSITION_SIZE);
}

void FileLogger::mmapFile(int start, int end) {
    //O_RDWR可读可写 O_CREAT没有这个文件创建这个文件 S_IRWXU可读可写可执行
    int logfd = open(logPath, O_RDWR | O_CREAT, S_IRWXU);
    ftruncate(logfd, mmapSize);
    int size = end - start;
    mmapPtr = (char *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, logfd, start);
    close(logfd);
}

int FileLogger::getLogFileSize() {
    FILE *fp = fopen(logPath, "r");
    if (fp == NULL) return 0;
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

FileLogger::~FileLogger() {
    if (logPath != nullptr) free(logPath);
    if (mmapPtr != nullptr) munmap(mmapPtr, mmapSize);
}