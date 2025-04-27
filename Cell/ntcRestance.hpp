#ifndef NTC_RESTANCE_H
#define NTC_RESTANCE_H

#include "cellConfig.hpp"

class NtcRestance {
    public:
        NtcRestance() {}
        float calcNtcRes(float volt) { 
            return kConf_1 *((kConf_2 - volt)/static_cast<float>(volt));
        }

        float getTempFromNtc(float res) {
            auto it = resToTemp.lower_bound(res); //get nearest value of restance from table
            if(it == resToTemp.end()) return resToTemp.rbegin()->second;
            if(it == resToTemp.begin()) return resToTemp.begin()->second;

            auto prev_it = std::prev(it);
            float R1 = prev_it->first;
            float T1 = prev_it->second;
            float R2 = it->first;
            float T2 = it->second;

            float temp = T1 +((res -R1)/(R2 - R1)*(T2 - T1));
            return std::round(temp*2.0f)/2.0f;
        }
};

#endif /*NTC_RESTANCE_H*/