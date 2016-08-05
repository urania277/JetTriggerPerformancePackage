/*--------------------------------------------------------------------
LogWriter.cxx

LogWriter is responsible for the creation of "NNNN".
All necessary settings that are needed for the JTPPPlotter are written
into this file.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/LogWriter.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



LogWriter::LogWriter()
{
  if (m_debug) std::cout << "Starting constructor LogWriter()..." << std::endl;
}

LogWriter::~LogWriter()
{
  if (m_debug) std::cout << "Starting destructor LogWriter()..." << std::endl;
}
