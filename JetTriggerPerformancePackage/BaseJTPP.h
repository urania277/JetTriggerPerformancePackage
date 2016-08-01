/*--------------------------------------------------------------------
BaseJTPP.h

This is JTPP's base class. m_debug in this class can switch on all
debug messages in all classes inherenting BaseJTPP

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/
#ifndef JetTriggerPerformancePackage_BaseJTPP_H
#define JetTriggerPerformancePackage_BaseJTPP_H


class BaseJTPP
{
protected:
    const bool m_debug = false;

public:
    BaseJTPP();
    ~BaseJTPP();

};

#endif // JetTriggerPerformancePackage_BaseJTPP_H
