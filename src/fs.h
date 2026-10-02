// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include <tic80_types.h>
#include <string.h>

typedef struct FileSystem FileSystem;

typedef enum
{
	FS_FILE_NOT_ADDED,
	FS_FILE_ADDED,
	FS_FILE_EXISTS,
} AddResult;

typedef enum
{
	FS_FILE_NOT_DOWNLOADED,
	FS_FILE_DOWNLOADED,
} GetResult;

typedef bool(*ListCallback)(const char* name, const char* info, s32 id, void* data, bool dir);
typedef void(*AddCallback)(const char*, AddResult, void*);
typedef void(*GetCallback)(GetResult, void*);
typedef void(*OpenCallback)(const char* name, const void* buffer, size_t size, void* data);

typedef struct FileSystem FileSystem;

FileSystem* createFileSystem(const char* path);

void fsEnumFiles(FileSystem* fs, ListCallback callback, void* data);
void fsAddFile(FileSystem* fs, AddCallback callback, void* data);
void fsGetFile(FileSystem* fs, GetCallback callback, const char* name, void* data);
bool fsDeleteFile(FileSystem* fs, const char* name);
bool fsDeleteDir(FileSystem* fs, const char* name);
bool fsSaveFile(FileSystem* fs, const char* name, const void* data, size_t size, bool overwrite);
bool fsSaveRootFile(FileSystem* fs, const char* name, const void* data, size_t size, bool overwrite);
void* fsLoadFile(FileSystem* fs, const char* name, s32* size);
void* fsLoadFileByHash(FileSystem* fs, const char* hash, s32* size);
void* fsLoadRootFile(FileSystem* fs, const char* name, s32* size);
void fsMakeDir(FileSystem* fs, const char* name);
bool fsExistsFile(FileSystem* fs, const char* name);
u64 fsMDate(FileSystem* fs, const char* name);

void fsBasename(const char *path, char* out);
void fsFilename(const char *path, char* out);
bool fsExists(const char* name);
void* fsReadFile(const char* path, s32* size);
bool fsWriteFile(const char* path, const void* data, s32 size);
bool fsCopyFile(const char* src, const char* dst);
void fsGetFileData(GetCallback callback, const char* name, void* buffer, size_t size, u32 mode, void* data);
void fsOpenFileData(OpenCallback callback, void* data);
void fsOpenWorkingFolder(FileSystem* fs);
bool fsIsDir(FileSystem* fs, const char* dir);
bool fsIsInPublicDir(FileSystem* fs);
bool fsChangeDir(FileSystem* fs, const char* dir);
void fsGetDir(FileSystem* fs, char* out);
void fsDirBack(FileSystem* fs);
void fsHomeDir(FileSystem* fs);