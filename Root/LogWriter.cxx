/*--------------------------------------------------------------------
LogWriter.cxx

LogWriter is responsible for the creation of "NNNN".
All necessary settings that are needed for the JTPPPlotter are written
into this file.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/LogWriter.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>



LogWriter::LogWriter(std::string logName):
    out_logfile(nullptr)
{
  if (m_debug) std::cout << "Starting constructor LogWriter()..." << std::endl;

  // construct out_logfile
  out_logfile = new std::ofstream(logName);

  // getting current time for header
  std::time_t now = time(0);

  // writing header in logfile
  *out_logfile << "# This is " << logName << ", created at " << now << std::endl;
  *out_logfile << "#" << std::endl;
  *out_logfile << "#All necessary settings needed for JTPPPlotter will be listed in the following" << std::endl;
  *out_logfile << "#" << std::endl;
}

LogWriter::~LogWriter()
{
  if (m_debug) std::cout << "Starting destructor LogWriter()..." << std::endl;
}

void LogWriter::CloseLogfile()
{
  if (m_debug) std::cout << "Starting CloseLogfile()..." << std::endl;

  out_logfile->close();
}
