#ifndef NEURALNET_H_
#define NEURALNET_H_

#include "dataEntry.h"
#include <vector>

class NeuralNet
{

  public:
    NeuralNet(int input_number, int hidden_number, int output_number);

    int GetInputNumber () const;
    int GetHiddenNumber () const;
    int GetOutputNumber () const;

    std::vector<float> GetInputNeuron () const;
    std::vector<float> GetHiddenNeuron () const;
    std::vector<float> GetOutputNeuron () const;

    std::vector<float> GetInputRate () const;
    std::vector<float> GetHiddenRate () const;
    std::vector<float> GetOutputRate () const;

    std::vector<std::vector<float>> GetInputHiddenPosWeight () const;
    std::vector<std::vector<float>> GetHiddenOutputPosWeight () const;
    std::vector<std::vector<float>> GetInputHiddenNegWeight () const;
    std::vector<std::vector<float>> GetHiddenOutputNegWeight () const;

    std::vector<DataEntry> Output(std::vector<DataEntry>);

  private:
    const int input_number;
    const int hidden_number;
    const int output_number;

    std::vector<float> input_neuron;
    std::vector<float> hidden_neuron;
    std::vector<float> output_neuron;

    std::vector<float> input_rate;
    std::vector<float> hidden_rate;
    std::vector<float> output_rate;

    std::vector<std::vector<float>> input_hidden_pos_weight;
    std::vector<std::vector<float>> hidden_output_pos_weight;
    std::vector<std::vector<float>> input_hidden_neg_weight;
    std::vector<std::vector<float>> hidden_output_neg_weight;

};

#endif // NEURALNET_H_
