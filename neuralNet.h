#ifndef NEURALNET_H_
#define NEURALNET_H_

#include "dataEntry.h"
#include <vector>

class NeuralNet {
  public:
    NeuralNet(int input_number, int hidden_number, int output_number);

    friend class Trainer;

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

    void SetInputHiddenPosWeight (const std::vector<std::vector<float>> input_hidden_pos_weight);
    void SetHiddenOutputPosWeight (const std::vector<std::vector<float>> hidden_output_pos_weight);
    void SetInputHiddenNegWeight (const std::vector<std::vector<float>> input_hidden_neg_weight);
    void SetHiddenOutputNegWeight (const std::vector<std::vector<float>> hidden_output_neg_weight);

    std::vector<float> GetUInputHidden() const;
    std::vector<float> GetVInputHidden() const;
    std::vector<float> GetUHiddenOutput() const;
    std::vector<float> GetVHiddenOutput() const;

    std::vector<DataEntry> Predict(std::vector<DataEntry>);

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

    std::vector<float> u_input_hidden;
    std::vector<float> v_input_hidden;
    std::vector<float> u_hidden_output;
    std::vector<float> v_hidden_output;

    std::vector<float> Output(std::vector<float>);
};

#endif // NEURALNET_H_
