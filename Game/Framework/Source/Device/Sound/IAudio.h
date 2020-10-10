#pragma once

#include<string>

class IAudio {
public:
    virtual ~IAudio() {};

    virtual unsigned short load(std::string waveBankName, std::string soundBankName,
                                const char* cueName) = 0;
    virtual void play(unsigned short index) = 0;
};