#include "cellMonitorMsg.hpp"

int main() {
    CellMonitorMsg<ReportVoltAlert> report_v_a;

    std::cout<<sizeof(report_v_a.GetPayload())<<std::endl;
    return 0;
}