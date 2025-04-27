#ifndef MESSAGE_TYPE_H_
#define MESSAGE_TYPE_H_

#include <iostream>

enum class ComMsgType {
    kReportData = 0xAA,
    kReportVoltAlert = 0x55,
};

#pragma pack(push, 1)  // Disable padding

struct ReportData {
    uint16_t cell_id;
    uint16_t cell_volt;
    uint16_t cell_temp;
};


struct ReportVoltAlert {
    uint16_t cell_id;
    uint16_t cell_volt;
};

#pragma pack(pop)



#endif /*MESSAGE_TYPE_H_*/