/*--------------------------------------------------------------------
ToolsJTPP.h

The ToolsJTPP contains various methods that were found to be usefull.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/


#ifndef JetTriggerPerformancePackage_TOOLSJTPP_H
#define JetTriggerPerformancePackage_TOOLSJTPP_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


//Own classes
#include <JetTriggerPerformancePackage/BaseJTPP.h>

class ToolsJTPP: public BaseJTPP
{
 public:
  ToolsJTPP();
  virtual ~ToolsJTPP();

  virtual std::string splitString(std::string name, std::string delimiter, int wordNumber);
  virtual std::string ftos(double number, int precision);
  virtual std::string rmSpaces(std::string input);
  virtual void stringToArray(std::string inputString, double *array, std::string delimiter);

  virtual int GetPosInVector(std::vector<std::string>& vec, std::string name);

};

#endif // JetTriggerPerformancePackage_TOOLSJTPP_H
