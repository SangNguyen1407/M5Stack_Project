#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

#include <M5Core2.h>

extern const char *CONF_FILENAME;
//extern File CONF_FILE;

File openFile();
String readFile();
bool writeFile(const char *content);

#endif //FILE_HANDLE_H