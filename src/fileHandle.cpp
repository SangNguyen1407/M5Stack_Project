#include "../lib/fileHandle.h"


File openFile(){
  bool success = SPIFFS.begin(true);
  File file = SPIFFS.open(CONF_FILENAME, FILE_READ);
  return file;
}

File closeFile(File file){
  if (file){
    file.close();
  }
}

void deleteFile(){
  bool success = SPIFFS.begin(true);
  if (success){
    SPIFFS.remove(CONF_FILENAME);
  }
}

String readFile(){
  String sData = "";
  bool success = SPIFFS.begin(true);
  File file = SPIFFS.open(CONF_FILENAME, FILE_READ);

  if (success && file){
    if (file.available()){
      sData = file.readStringUntil('\n');
      file.close();
    } 
    else{
      M5.Lcd.drawString("file not available", 10, 90, 2);
    }
  }
  else{
    M5.Lcd.drawString("not open file", 10, 90, 2);
  }
  return sData;
}

bool writeFile(const char *content){
  bool success = SPIFFS.begin(true);
  File file = SPIFFS.open(CONF_FILENAME, FILE_WRITE);

  if (success && file){
    if (file.available()){
      file.println(content);
      file.close();
    }
  }

  return true;
}