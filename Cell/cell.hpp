#ifndef CELL_H
#define CELL_H

#include "Logger/logger.hpp"
#include "Com/socketCommunication.hpp"
#include <iostream>
#include "ntcRestance.hpp"
#include "InterfaceType/cellMonitorMsg.hpp"



class Cell {
    public:
        Cell(std::shared_ptr<Logger> logger, uint16_t id) : cell_id(id), logger(logger),
        comm(Role::CLIENT)
        {}
        void init() {
            comm.initialize();
        }
        void processData(float volt, uint16_t curr) {
            cell_voltage = volt;
            cell_current = curr;
            res = ntc_res.calcNtcRes(cell_voltage);
            temp = ntc_res.getTempFromNtc(res);
            notify();
        }


    private:
        const uint16_t cell_id;
        float cell_voltage;
        uint16_t cell_current;
        float res;
        float temp;
        NtcRestance ntc_res;
        SocketCommunication comm;
        std::shared_ptr<Logger> logger;

        void notify() {
            if(cell_voltage >= voltage_th) {
                ReportVoltAlert report_v_alert;
                report_v_alert.cell_id = cell_id;
                report_v_alert.cell_volt = cell_voltage;

                CellMonitorMsg<ReportVoltAlert> msg_report_v_alert;
                msg_report_v_alert.SetCellMonitorMsgHeader(ComMsgType::kReportVoltAlert, sizeof(report_v_alert));
                memcpy(msg_report_v_alert.GetPayloadPtr(), &report_v_alert, sizeof(ReportVoltAlert));
                comm.sendData(msg_report_v_alert.GetSerializeData());
            }


            ReportData report_data;
            report_data.cell_id = cell_id;
            report_data.cell_volt = cell_voltage;
            report_data.cell_temp = temp;

            CellMonitorMsg<ReportData> msg_report_data;
            msg_report_data.SetCellMonitorMsgHeader(ComMsgType::kReportData, sizeof(report_data));
            memcpy(msg_report_data.GetPayloadPtr(), &report_data, sizeof(ReportData));
            comm.sendData(msg_report_data.GetSerializeData());
        }
};

#endif //CELL_H