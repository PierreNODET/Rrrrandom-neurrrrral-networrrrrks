#include <iostream>

#include "dataReader.h"

int main(){

  DataReader& data_reader = DataReader::GetInstance();
  std::vector<DataEntry> data_set = data_reader.ReadFile("train.txt",',',2,1);
  std::cout << data_set.at(0).predictor.at(0) << std::endl;
  return 0;

}
