#include <iostream>

#include "dataReader.h"
#include "neuralNet.h"

int main(){

  DataReader& data_reader = DataReader::GetInstance();
  std::vector<DataEntry> data_set = data_reader.ReadFile("train.txt",',',2,1);
  std::cout << data_set.at(0).predictor.at(0) << std::endl;
  NeuralNet nn = NeuralNet(2,10,1);
  std::cout<<nn.GetInputHiddenNegWeight()[1][1]<<std::endl;
  std::vector<DataEntry> o = nn.Output(data_set);
  std::cout<<o.at(0).predicted.at(0)<<std::endl;
  return 0;

}
