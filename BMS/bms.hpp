#ifndef BMS_H
#define BMS_H

#include "Com/socketCommunication.hpp"
#include "InterfaceType/cellMonitorMsg.hpp"



class Bms {
    public:
        Bms() : comm(Role::SERVER) {}
        void init() {
            comm.initialize();
            comm.registerCallback(
                std::bind(&Bms::handleData, this, std::placeholders::_1, std::placeholders::_2)
            );
        }

    private:
        SocketCommunication comm;
        void handleData(const std::vector<uint8_t>& data, int client_id) {
            std::cout << "Received from client " << client_id << ": ";
            CellMonitorMsgHeader header;
            if(data.size() > sizeof(CellMonitorMsgHeader)) {
                memcpy(&header, data.data(), sizeof(header));
            } else {
                std::cout << "Received wrong data" << std::endl;
                return;
            }

            switch (header.msgType) {
                case ComMsgType::kReportData:
                    if(data.size() == sizeof(CellMonitorMsg<ReportData>)) {
                        CellMonitorMsg<ReportData> msg;
                        std::memcpy(&msg, data.data(), sizeof(CellMonitorMsg<ReportData>));
                        auto payload = msg.GetPayload();
                        std::cout << "  Cell ID     : " << payload.cell_id << std::endl;
                        std::cout << "  Voltage (mV): " << payload.cell_volt << std::endl;
                        std::cout << "  Temperature : " << payload.cell_temp << "°C" << std::endl;
                    } break;

                case ComMsgType::kReportVoltAlert:
                    if(data.size() == sizeof(CellMonitorMsg<ReportVoltAlert>)) {
                        CellMonitorMsg<ReportVoltAlert> msg;
                        std::memcpy(&msg, data.data(), sizeof(CellMonitorMsg<ReportVoltAlert>));
                        auto payload = msg.GetPayload();
                        std::cout << "  Cell ID     : " << payload.cell_id << std::endl;
                        std::cout << "  Voltage (mV): " << payload.cell_volt << std::endl;
                    }
                    break;
                default:
                    std::cout << "Received wrong data" << std::endl;
            }
            std::cout << std::endl;
        }
};


#endif /*BMS_H*/



