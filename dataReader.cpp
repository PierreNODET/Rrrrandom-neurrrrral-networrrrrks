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

  std::string data;

  while (getline(file,data,separator)){

    DataEntry data_entry;

    int count_predictor=0;
    int count_predicted=0;

    while(count_predictor<length_predictor){
      data_entry.predictor.push_back(std::stof(data));
      count_predictor+=1;
    }

    while(count_predicted<length_predicted){
      data_entry.predicted.push_back(std::stof(data));
      count_predicted+=1;
    }

    data_set.push_back(data_entry);

  }

  return data_set;

}
