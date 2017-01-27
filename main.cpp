#include <iostream>

#include "dataReader.h"
#include "neuralNet.h"
#include "trainer.h"

#include <unistd.h>
#include <cmath>

#include <string>
#include <fstream>

/*std::vector<float> MSE(std::vector<float> data_set,std::vector<float> output){
  std::vector<float> mse;
  for (unsigned int i = 0;i<data_set.size();i++){
    mse[i]=0.5*pow((data_set[i]-output[i]),2);
  }
  return mse;
};*/

std::vector<float> MSE(std::vector<float> data_set,std::vector<float> output){
  std::vector<float> mse = std::vector<float>(data_set.size(),0);
  for (unsigned int i = 0;i<data_set.size();i++){
    mse[i]=0.5*pow((data_set[i]-output[i]),2);
  }
  return mse;
};

std::vector<float> MSEDeriv(std::vector<float> data_set,std::vector<float> output){
  std::vector<float> mse = std::vector<float>(data_set.size(),0);
  for (unsigned int i = 0;i<data_set.size();i++){
    mse[i]= (data_set[i]-output[i]);
  }
  return mse;
};

int main(){

  /*std::cout<<MSE({5},{1})[0]<<std::endl;*/

  DataReader& data_reader = DataReader::GetInstance();
  int predictor_number = 2;
  std::vector<DataEntry> data_set = data_reader.ReadFile("train.txt",',',predictor_number,1);
  std::vector<DataEntry> test_set = data_reader.ReadFile("test.txt",',',predictor_number,1);
  NeuralNet nn = NeuralNet(predictor_number,10,1);

  /*std::cout << data_set.at(0).predictor.at(0) << std::endl;
  for (int i = 0; i<2;i++){
    for(int j=0;j<10;j++){
      std::cout<<nn.GetInputHiddenPosWeight()[i][j]<<" ";
      std::cout<<nn.GetInputHiddenNegWeight()[i][j]<<" ";
      std::cout<<std::endl;
    }
  }
  std::cout<<std::endl;
  for (int j = 0; j<10;j++){
    for(int k=0;k<1;k++){
      std::cout<<nn.GetHiddenOutputPosWeight()[j][k]<<" ";
      std::cout<<nn.GetHiddenOutputNegWeight()[j][k]<<" ";
      std::cout<<std::endl;
    }
  }
  std::vector<DataEntry> res = nn.Predict(data_set);
  std::cout << res.at(0).predicted.at(0) << std::endl;

  std::cout << std::endl;
  std::vector<DataEntry> o = nn.Predict(data_set);
  std::cout<<o.at(0).predicted.at(0)<<std::endl;*/
  Trainer t = Trainer(&nn);
  t.SetCost(MSEDeriv);
  int i=0;
  while (i<20000){
    std::cout<<t.Score(data_set,MSE).at(0)<<" - "<<t.Score(test_set,MSE).at(0)<<" - "<< i <<std::endl;
    t.Train(data_set);
    /*for (int i = 0; i<2;i++){
      for(int j=0;j<10;j++){
        std::cout<<nn.GetInputHiddenPosWeight()[i][j]<<" ";
      }
    }*/
    i++;
  }

  /*for (int i = 0; i<predictor_number;i++){
    for(int j=0;j<4;j++){
      std::cout<<nn.GetInputHiddenPosWeight()[i][j]<<" ";
      std::cout<<nn.GetInputHiddenNegWeight()[i][j]<<" ";
      std::cout<<std::endl;
    }
  }

  for (int j = 0; j<4;j++){
    for(int k=0;k<1;k++){
      std::cout<<nn.GetHiddenOutputPosWeight()[j][k]<<" ";
      std::cout<<nn.GetHiddenOutputNegWeight()[j][k]<<" ";
      std::cout<<std::endl;
    }
  }*/

  /*std::cout<<data_set.size()<<std::endl;
  int j=0;
  for(std::vector<DataEntry>::iterator data_entry = data_set.begin(); data_entry != data_set.end();++data_entry){
    std::cout<<data_entry->predictor.at(1)<<" "<<j++<<" ";
  }*/
  std::cout<<data_set.size()<<std::endl;
  int j=0;
  std::vector<DataEntry> res = nn.Predict(test_set);
  std::ofstream fichier("res.txt", std::ios::out | std::ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    if(fichier){
      for(std::vector<DataEntry>::iterator data_entry = res.begin(); data_entry != res.end();++data_entry){
        fichier<<data_entry->predicted.at(0)<<std::endl;
      }
    }
  fichier.close();

  return 0;

}
