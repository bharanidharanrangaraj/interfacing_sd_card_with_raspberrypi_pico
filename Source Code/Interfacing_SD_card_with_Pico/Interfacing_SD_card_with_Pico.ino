#include <SPI.h>
#include <SD.h>

const int SD_CS = 17;            // GP17
const char *FNAME = "demo.txt";  // file on SD

void printMenu() {
  Serial.println();
  Serial.println(F("===== SD Menu ====="));
  Serial.println(F("1 - Create file"));
  Serial.println(F("2 - Write a line to file (append)"));
  Serial.println(F("3 - Read file"));
  Serial.println(F("4 - Delete file"));
  Serial.println(F("Enter choice and press Enter:"));
  Serial.print("> ");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) ; // wait for Serial (on some cores)
  Serial.println();
  Serial.println(F("Pico SD Menu Demo"));

  if (!SD.begin(SD_CS)) {
    Serial.println(F("SD init FAILED. Check wiring & 3.3V power."));
    while (1) delay(500);
  }
  Serial.println(F("SD initialized OK."));
  printMenu();
}

String readSerialLine() {
  // Wait for a line from Serial, return trimmed string
  while (!Serial.available()) {
    delay(10);
  }
  String s = Serial.readStringUntil('\n');
  s.trim();
  return s;
}

void createFile() {
  if (SD.exists(FNAME)) {
    Serial.println(F("File already exists."));
    return;
  }
  File f = SD.open(FNAME, FILE_WRITE); // creates file
  if (!f) {
    Serial.println(F("Create FAILED."));
    return;
  }
  f.close();
  Serial.println(F("File created."));
}

void writeFile() {
  if (!SD.exists(FNAME)) {
    Serial.println(F("File does not exist. Create it first (press 1)."));
    return;
  }
  Serial.println(F("Type the text to append and press Enter:"));
  Serial.print("> ");
  String line = readSerialLine();
  File f = SD.open(FNAME, FILE_WRITE);
  if (!f) {
    Serial.println(F("Open for write FAILED."));
    return;
  }
  f.println(line);
  f.flush();
  f.close();
  Serial.println(F("Appended to file."));
}

void readFile() {
  if (!SD.exists(FNAME)) {
    Serial.println(F("File does not exist."));
    return;
  }
  File f = SD.open(FNAME, FILE_READ);
  if (!f) {
    Serial.println(F("Open for read FAILED."));
    return;
  }
  Serial.println(F("--- File content start ---"));
  while (f.available()) {
    Serial.write(f.read());
  }
  Serial.println();
  Serial.println(F("--- File content end ---"));
  f.close();
}

void deleteFile() {
  if (!SD.exists(FNAME)) {
    Serial.println(F("File does not exist."));
    return;
  }
  if (SD.remove(FNAME)) {
    Serial.println(F("File deleted."));
  } else {
    Serial.println(F("Delete FAILED."));
  }
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.length() == 0) {
      printMenu();
      return;
    }
    char c = cmd.charAt(0);
    switch (c) {
      case '1':
        createFile();
        break;
      case '2':
        writeFile();
        break;
      case '3':
        readFile();
        break;
      case '4':
        deleteFile();
        break;
      default:
        Serial.println(F("Unknown choice."));
        break;
    }
    // show menu again
    printMenu();
  }
}