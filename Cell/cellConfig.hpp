#ifndef CELL_CONFIG_H
#define CELL_CONFIG_H

#include <iostream>
#include <map>

// Define the NTC resistance to temperature mapping
const std::map<float, float> resToTemp = {
    {2192.61, -40.0},
    {1255.83, -30.0},
    {743.62, -20.0},
    {454.16, -10.0},
    {285.45, 0.0},
    {184.25, 10.0},
    {121.89, 20.0},
    {82.419, 30.0},
    {57.02, 40.0},
    {40.20, 50.0}
};

constexpr float kConf_1 = 100.00;
constexpr float kConf_2 = 3300.00;
constexpr float voltage_th = 4.2;


#endif /*CELL_CONFIG_H*/
