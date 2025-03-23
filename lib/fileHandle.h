#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

#include <M5Core2.h>

extern const char *CONF_FILENAME;


String readFile();
bool writeFile(const char *content, const char *priority);
void deleteFile();

#endif //FILE_HANDLE_H