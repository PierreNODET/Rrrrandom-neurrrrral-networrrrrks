#ifndef NEURALNET_H_
#define NEURALNET_H_

#include "neuron.h"
#include <vector>

class NeuralNet
{

  public:
    NeuralNet(int input_number, int hidden_number, int output_number);

    int GetInputNumber () const;
    int GetHiddenNumber () const;
    int GetOutputNumber () const;

    std::vector<Neuron> GetInputNeuronTable () const;
    std::vector<Neuron> GetHiddenNeuronTable () const;
    std::vector<Neuron> GetOutputNeuronTable () const;

    float Ouput(float input[][]);

  private:
    const int input_number;
    const int hidden_number;
    const int output_number;

    std::vector<Neuron> input_neuron_table;
    std::vector<Neuron> hidden_neuron_table;
    std::vector<Neuron> output_neuron_table;

};

#endif // NEURALNET_H_
