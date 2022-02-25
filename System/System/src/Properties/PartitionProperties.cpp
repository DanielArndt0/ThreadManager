#include "Properties/PartitionProperties.h"

System::Properties::EEProperties::EEProperties() {}

System::Properties::EEProperties::EEProperties(char name, unsigned long addr_start, unsigned long addr_final) : __name__(name), __start__(addr_start), __final__(addr_final) {}

char System::Properties::EEProperties::getName() { return __name__; }

unsigned long System::Properties::EEProperties::getSize() { return __final__ - __start__; }

unsigned long System::Properties::EEProperties::getStartAddr() { return __start__; }

unsigned long System::Properties::EEProperties::getEndAddr() { return __final__; }

//unsigned char *System::Properties::EEProperties::getData() { return __data__; }
