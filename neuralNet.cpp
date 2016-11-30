#include "neuralNet.h"

int NeuralNet::GetInputNumber() const {
  return input_number;
}

int NeuralNet::GetHiddenNumber() const {
  return hidden_number;
}

int NeuralNet::GetOutputNumber() const {
  return output_number;
}

std::vector<Neuron> NeuralNet::GetInputNeuronTable () const{
  return input_neuron_table;
}

std::vector<Neuron> NeuralNet::GetHiddenNeuronTable () const{
  return hidden_neuron_table;
}

std::vector<Neuron> NeuralNet::GetOutputNeuronTable () const{
  return output_neuron_table;
}

std::vector<DataEntry> NeuralNet::Ouput(std::vector<DataEntry>){

}
