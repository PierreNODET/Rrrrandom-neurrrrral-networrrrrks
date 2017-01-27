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

void NeuralNet::SetInputHiddenPosWeight (const std::vector<std::vector<float>> input_hidden_pos_weight){
  this->input_hidden_pos_weight=input_hidden_pos_weight;
}

void NeuralNet::SetHiddenOutputPosWeight (const std::vector<std::vector<float>> hidden_output_pos_weight){
  this->hidden_output_pos_weight=hidden_output_pos_weight;
}

void NeuralNet::SetInputHiddenNegWeight (const std::vector<std::vector<float>> input_hidden_neg_weight){
  this->input_hidden_neg_weight=input_hidden_neg_weight;
}

void NeuralNet::SetHiddenOutputNegWeight (const std::vector<std::vector<float>> hidden_output_neg_weight){
  this->hidden_output_neg_weight=hidden_output_neg_weight;
}

std::vector<float> NeuralNet::GetUInputHidden() const{
  return u_input_hidden;
}

std::vector<float> NeuralNet::GetVInputHidden() const{
  return v_input_hidden;
}

std::vector<float> NeuralNet::GetUHiddenOutput() const{
  return u_hidden_output;
}

std::vector<float> NeuralNet::GetVHiddenOutput() const{
  return v_hidden_output;
}

std::vector<DataEntry> NeuralNet::Predict(std::vector<DataEntry> data_set){

  std::vector<DataEntry> output;

  for(std::vector<DataEntry>::iterator data_entry = data_set.begin(); data_entry != data_set.end();++data_entry){

    DataEntry output_line;

    output_line.predicted = Output(data_entry->predictor);

    output.push_back(output_line);

  }

  return output;

}

std::vector<float> NeuralNet::Output(std::vector<float> input){

  std::fill(u_input_hidden.begin(), u_input_hidden.end(), 0);
  std::fill(v_input_hidden.begin(), v_input_hidden.end(), 0);
  std::fill(u_hidden_output.begin(), u_hidden_output.end(), 0);
  std::fill(v_hidden_output.begin(), v_hidden_output.end(), 0);

  for(int i=0;i<input_number;++i){

    input_neuron[i]=input[i];

  }

  for(int j=0;j<hidden_number;j++){

    for(int i=0;i<input_number;i++){

      /*hidden_neuron[j]=input_neuron[i]*input_hidden_pos_weight[j][i]  /(1+input_neuron[i]*input_hidden_neg_weight[j][i])*/
      u_input_hidden[j] += input_neuron[i]*input_hidden_pos_weight[i][j];
      v_input_hidden[j] += input_neuron[i]*input_hidden_neg_weight[i][j];

    }

    hidden_neuron[j] = u_input_hidden[j]/(1+v_input_hidden[j]);

  }

  for(int k=0;k<output_number;k++){

    for(int j=0;j<hidden_number;j++){

      /*hidden_neuron[j]=input_neuron[i]*input_hidden_pos_weight[j][i]  /(1+input_neuron[i]*input_hidden_neg_weight[j][i])*/
      u_hidden_output[k] += hidden_neuron[j]*hidden_output_pos_weight[j][k];
      v_hidden_output[k] += hidden_neuron[j]*hidden_output_neg_weight[j][k];

    }

    output_neuron[k] = u_hidden_output[k]/(1+v_hidden_output[k]);

  }

  return output_neuron;

}


NeuralNet::NeuralNet(int input_number, int hidden_number, int output_number):input_number(input_number), hidden_number(hidden_number), output_number(output_number){

  input_neuron= std::vector<float>(input_number,0);
  hidden_neuron = std::vector<float>(hidden_number,0);
  output_neuron = std::vector<float>(output_number,0);

  u_input_hidden = std::vector<float>(hidden_number,0);
  v_input_hidden = std::vector<float>(hidden_number,0);
  u_hidden_output = std::vector<float>(output_number,0);
  v_hidden_output = std::vector<float>(output_number,0);

  input_hidden_neg_weight = std::vector<std::vector<float>>(input_number);
  input_hidden_pos_weight = std::vector<std::vector<float>>(input_number);

  hidden_output_neg_weight = std::vector<std::vector<float>>(hidden_number);
  hidden_output_pos_weight = std::vector<std::vector<float>>(hidden_number);

  /*srand(time(NULL));*/
  srand(45564546);

  for(int j=0;j<hidden_number;j++){

    hidden_output_pos_weight[j] = std::vector<float>(output_number);
    hidden_output_neg_weight[j] = std::vector<float>(output_number);

    for(int k=0;k<output_number;k++){

      hidden_output_pos_weight[j][k]= rand()/(double(RAND_MAX));
      hidden_output_neg_weight[j][k]= rand()/(double(RAND_MAX));

    }

  }

  for(int i=0;i<input_number;i++){

    input_hidden_pos_weight[i] = std::vector<float>(hidden_number);
    input_hidden_neg_weight[i] = std::vector<float>(hidden_number);

    for(int j=0;j<hidden_number;j++){

      input_hidden_pos_weight[i][j]= rand()/(double(RAND_MAX));
      input_hidden_neg_weight[i][j]= rand()/(double(RAND_MAX));

    }

  }

}
