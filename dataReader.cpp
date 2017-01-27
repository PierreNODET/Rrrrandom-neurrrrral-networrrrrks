#include <fstream>

#include "dataReader.h"

DataReader DataReader::instance=DataReader();

DataReader& DataReader::GetInstance()
{
    return instance;
}

std::vector<DataEntry> DataReader::ReadFile(std::string file_name, char separator, int length_predictor, int length_predicted){

  std::vector<DataEntry> data_set;

  std::ifstream file(file_name);

  std::string s;

  while (file.good()){

    getline(file,s);

    if (s.length()>2){

      size_t pos = 0;
      std::string token;

      DataEntry data_entry;

      int count_predictor=0;
      int count_predicted=0;

      while((count_predictor<length_predictor) & ((pos = s.find(separator)) != std::string::npos)){
        token = s.substr(0, pos);
        data_entry.predictor.push_back(std::stof(s));
        s.erase(0, pos + 1);
        count_predictor+=1;
      }

      while((count_predicted<length_predicted-1) & ((pos = s.find(separator)) != std::string::npos)){
        token = s.substr(0, pos);
        data_entry.predicted.push_back(std::stof(s));
        count_predicted+=1;
        s.erase(0, pos + 1);
      }

      data_entry.predicted.push_back(std::stof(s));

      data_set.push_back(data_entry);
    }
  }

  return data_set;

}
