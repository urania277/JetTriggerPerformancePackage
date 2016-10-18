/*--------------------------------------------------------------------
ToolsJTPP.cxx

The ToolsJTPP contains various methods that were found to be usefull.

created by Edgar Kellermann (edgar.kellermann@cern.ch)
--------------------------------------------------------------------*/

#include <JetTriggerPerformancePackage/ToolsJTPP.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


ToolsJTPP::ToolsJTPP()
{
  if (m_debug) std::cout << "Starting constructor ToolsJTPP()..." << std::endl;
}

ToolsJTPP::~ToolsJTPP()
{
  if (m_debug) std::cout << "Starting destructor ToolsJTPP()..." << std::endl;
}


std::string ToolsJTPP::splitString(std::string name, std::string delimiter, int wordNumber)
{

  if(m_debug) std::cout << "Starting splitString()..." << std::endl;

  std::string s = name;
  size_t pos = 0;
  int counter = 0;
  std::string token;

  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);

    if(counter == wordNumber) return token;

    s.erase(0, pos + delimiter.length());
    counter++;
  }
  if (counter == (wordNumber)) return s;

  return "String TOO SHORT";
}


std::string ToolsJTPP::ftos(double number, int precision)
{
  std::stringstream ss;
  ss << std::setprecision(precision);
  ss << number;
  return ss.str();
}

std::string ToolsJTPP::rmSpaces(std::string input)
{
    if(m_debug) std::cout << "Starting rmSpaces()..." << std::endl;

    input.erase(std::remove(input.begin(),input.end(),' '),input.end());
    return input;
}

// This function is splitting the inputString into an float array
void ToolsJTPP::stringToArray(std::string inputString, double *array, std::string delimiter)
{
    if(m_debug) std::cout << "Starting ToolsJTPP::stringToArray(std::string inputString, int *array, std::string delimiter)..." << std::endl;

    std::string cleanedString, stringPiece;
    cleanedString = this->rmSpaces(inputString);

    int NArraySize = std::count(cleanedString.begin(), cleanedString.end(),',') + 1;

    for (int n =0; n < NArraySize; n++){
        stringPiece = this->splitString(cleanedString,delimiter,n);
        array[n] = std::stod(stringPiece);
    }
}

int ToolsJTPP::GetPosInVector(std::vector<std::string>& vec, std::string name)
{
    // returns the position in the vector (starting with 0)
    // returns -1 if it could not find name in vec

    int pos = -1;

    // crosscheck if vec has some content
    if (vec.size() == 0) return pos;

    for (unsigned int n=0; n < vec.size(); n++){
	if (vec.at(n).compare(name) == 0) pos = n;
    }

    return pos;
}
