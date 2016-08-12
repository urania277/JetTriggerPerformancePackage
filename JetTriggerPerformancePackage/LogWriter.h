/*--------------------------------------------------------------------
LogWriter.h

LogWriter is responsible for the creation of "NNNN".
All necessary settings that are needed for the JTPPPlotter are written
into this file.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/
#ifndef JetTriggerPerformancePackage_LOGWRITER_H
#define JetTriggerPerformancePackage_LOGWRITER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "TLorentzVector.h"


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>

class LogWriter: public BaseJTPP
{
    private:
    // ofstream of the actual logfile
    std::ofstream* out_logfile;

    public:
    LogWriter(std::string logName);
    virtual ~LogWriter();

    // methods
    virtual void CloseLogfile();
};

#endif // JetTriggerPerformancePackage_LOGWRITER_H
