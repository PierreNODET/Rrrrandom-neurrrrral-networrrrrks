#ifndef TRAINER_H_
#define TRAINER_H_

#include "dataEntry.h"
#include "neuralNet.h"
#include <vector>

class Trainer {
  public:
    Trainer(NeuralNet* neural_net);

    void Train(std::vector<DataEntry> data_set);

    std::vector<float> Score(std::vector<DataEntry> data_set, std::vector<float> (*ScoreFunction)(std::vector<float> data_set,std::vector<float> output));

    void SetCost (std::vector<float> (*Cost)(std::vector<float> data_set,std::vector<float> output));

  private:
    NeuralNet* neural_net;

    float learning_rate;
    std::vector<float> (*Cost)(std::vector<float> data_set,std::vector<float> output);

    std::vector<std::vector<float>> input_hidden_pos_weight_der;
    std::vector<std::vector<float>> hidden_output_pos_weight_der;
    std::vector<std::vector<float>> input_hidden_neg_weight_der;
    std::vector<std::vector<float>> hidden_output_neg_weight_der;
};

#endif // TRAINER_H_
