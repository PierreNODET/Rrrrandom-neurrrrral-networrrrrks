#ifndef DATAREADER_H_
#define DATAREADER_H_

#include <string>
#include <vector>

#include "dataEntry.h"

class DataReader{

  public:
    static DataReader& GetInstance();
    std::vector<DataEntry> ReadFile(std::string file_name, char separator, int length_predictor, int length_predicted);

  private:
    DataReader() {}
    static DataReader instance;

    void operator= (const DataReader&){}
    DataReader (const DataReader&){}

};


#endif // DATAREADER_H_
