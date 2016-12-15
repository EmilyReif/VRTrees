#include "lsystemgenerator.h"
#include <iostream>


lsystemGenerator::lsystemGenerator(std::string start, std::map<char, std::string> rules)
{
    m_startAxiom = start;
    m_lang = "";
    m_rules = rules;
}

void lsystemGenerator::run(int iterations)
{
    std::string curr = m_startAxiom;
    for (int i =0; i < iterations; i++) {
        int size = curr.size();
        for (int j = 0; j < size; j++) {
            if(m_rules.count(curr[j])) {
                std::string buff = m_rules.find(curr[j])->second;
                curr.replace(j, 1, buff);
                j += buff.size() -1;
            }
        }
    }
    m_lang = curr;
}

std::string lsystemGenerator::getGenString()
{
    return m_lang;
}
