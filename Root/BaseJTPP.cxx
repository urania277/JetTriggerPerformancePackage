/*--------------------------------------------------------------------
BaseJTPP.cxx

This is JTPP's base class.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/
#include <JetTriggerPerformancePackage/BaseJTPP.h>
#include <iostream>

BaseJTPP::BaseJTPP()
{
    if (m_debug) std::cout << "Starting constructor BaseJTPP()..." << std::endl;
}

BaseJTPP::~BaseJTPP()
{
    if (m_debug) std::cout << "Starting destructor BaseJTPP()..." << std::endl;
}
