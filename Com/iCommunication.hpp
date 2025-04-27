#ifndef ICOMMUNUCATION_H_
#define ICOMMUNUCATION_H_

#include <vector>
#include <memory>

class ICommunication {
public:
    ICommunication() {}

    virtual ~ICommunication() = default;

    virtual void initialize() = 0;

    virtual bool sendData(const std::vector<uint8_t>& data) = 0;

    virtual std::vector<uint8_t> receiveData() = 0;

    virtual void deInit() = 0;
};


#endif /*ICOMMUNUCATION_H_*/