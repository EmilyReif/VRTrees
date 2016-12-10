#ifndef LSYSTEMGENERATOR_H
#define LSYSTEMGENERATOR_H

#include "stdlib.h"
#include <string>
#include <map>

class lsystemGenerator
{
public:
    lsystemGenerator(std::string start, std::map<char, std::string> rules);
    void run(int iterations);
    std::string getGenString();
private:
    std::string m_startAxiom;
    std::string m_lang;
    std::map<char, std::string> m_rules;
};

#endif // LSYSTEMGENERATOR_H
