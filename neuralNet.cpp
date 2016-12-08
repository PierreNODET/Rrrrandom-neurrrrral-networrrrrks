#include "neuralNet.h"
#include <cstdlib>
#include <ctime>

#include <iostream>

int NeuralNet::GetInputNumber() const {
  return input_number;
}

int NeuralNet::GetHiddenNumber() const {
  return hidden_number;
}

int NeuralNet::GetOutputNumber() const {
  return output_number;
}

std::vector<float> NeuralNet::GetInputNeuron () const{
  return input_neuron;
}

std::vector<float> NeuralNet::GetHiddenNeuron () const{
  return hidden_neuron;
}

std::vector<float> NeuralNet::GetOutputNeuron () const{
  return output_neuron;
}

std::vector<float> NeuralNet::GetInputRate () const{
  return input_rate;
}

std::vector<float> NeuralNet::GetHiddenRate () const{
  return hidden_rate;
}

std::vector<float> NeuralNet::GetOutputRate () const{
  return output_rate;
}

std::vector<std::vector<float>> NeuralNet::GetInputHiddenPosWeight () const{
  return input_hidden_pos_weight;
}

std::vector<std::vector<float>> NeuralNet::GetHiddenOutputPosWeight () const{
  return hidden_output_pos_weight;
}

std::vector<std::vector<float>> NeuralNet::GetInputHiddenNegWeight () const{
  return input_hidden_neg_weight;
}

std::vector<std::vector<float>> NeuralNet::GetHiddenOutputNegWeight () const{
  return hidden_output_neg_weight;
}

std::vector<DataEntry> NeuralNet::Output(std::vector<DataEntry> data_set){

  std::vector<DataEntry> output;

  for(std::vector<DataEntry>::iterator data_entry = data_set.begin(); data_entry != data_set.end();++data_entry){

    DataEntry output_line;

    for(int i=0;i<input_number;++i){

      input_neuron[i]=(*data_entry).predictor[i];

    }

    for(int j=0;j<hidden_number;j++){
      for(int i=0;i<input_number;i++){

      hidden_neuron[j]=input_neuron[i]*input_hidden_pos_weight[j][i]/(1+input_neuron[i]*input_hidden_neg_weight[j][i]);

      }
    }

    for(int j=0;j<output_number;j++){
      for(int i=0;i<hidden_number;i++){

        output_neuron[j]=hidden_neuron[i]*hidden_output_pos_weight[j][i]/(1+hidden_neuron[i]*hidden_output_neg_weight[j][i]);

      }
    }

    for(int i=0;i<output_number;i++){

      output_line.predicted.push_back(output_neuron[i]);

    }

    output.push_back(output_line);

  }

  return output;

}

NeuralNet::NeuralNet(int input_number, int hidden_number, int output_number):input_number(input_number), hidden_number(hidden_number), output_number(output_number){

  input_neuron= std::vector<float>(input_number,0);
  hidden_neuron = std::vector<float>(hidden_number,0);
  output_neuron = std::vector<float>(output_number,0);

  input_hidden_neg_weight = std::vector<std::vector<float>>(hidden_number);
  input_hidden_pos_weight = std::vector<std::vector<float>>(hidden_number);

  hidden_output_neg_weight = std::vector<std::vector<float>>(output_number);
  hidden_output_pos_weight = std::vector<std::vector<float>>(output_number);

  srand(time(NULL));

  for(int j=0;j<output_number;j++){

    for(int i=0;i<hidden_number;i++){

    hidden_output_pos_weight[j] = std::vector<float>(hidden_number);
    hidden_output_neg_weight[j] = std::vector<float>(hidden_number);
    hidden_output_pos_weight[j][i]= rand()/(double)RAND_MAX;
    hidden_output_neg_weight[j][i]= rand()/(double)RAND_MAX;

    }

  }

  for(int j=0;j<hidden_number;j++){

    for(int i=0;i<input_number;i++){

      input_hidden_pos_weight[j] = std::vector<float>(input_number);
      input_hidden_neg_weight[j] = std::vector<float>(input_number);
      input_hidden_pos_weight[j][i]= rand()/(double)RAND_MAX;
      input_hidden_neg_weight[j][i]= rand()/(double)RAND_MAX;

    }

  }

}
