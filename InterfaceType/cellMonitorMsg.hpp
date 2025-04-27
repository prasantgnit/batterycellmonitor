#ifndef CELL_MONITOR_MSG_H
#define CELL_MONITOR_MSG_H

#include "messageType.hpp"
#pragma pack(push, 1)  // Disable padding

struct CellMonitorMsgHeader {
    ComMsgType msgType;
    uint16_t payload_length;
};

template<typename T>
class CellMonitorMsg {
    public:
    void* GetPayloadPtr() {
        return static_cast<void*> (&payload);
    }
    T GetPayload() {
        return payload;
    }
    CellMonitorMsgHeader GetCellMonitorMsgHeader() {
        return header;
    }
    void SetCellMonitorMsgHeader(ComMsgType typ, uint16_t len) {
        header.msgType = typ;
        header.payload_length = len;
    }
    ComMsgType GetCellMonitorMsgType() {
        return header.msgType;
    }

    std::vector<uint8_t> GetSerializeData() {
        std::vector<uint8_t> data;

        // Convert header to bytes and add to the vector
        uint8_t* headerBytes = reinterpret_cast<uint8_t*>(&header);
        data.insert(data.end(), headerBytes, headerBytes + sizeof(header));

        // Convert payload to bytes and add to the vector
        uint8_t* payloadBytes = reinterpret_cast<uint8_t*>(&payload);
        data.insert(data.end(), payloadBytes, payloadBytes + sizeof(payload));

        return data;
    }

    private:
    CellMonitorMsgHeader header;
    T payload;
};
#pragma pack(pop)


#endif /*CELL_MONITOR_MSG_H*/
