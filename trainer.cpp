#include "trainer.h"

Trainer::Trainer(NeuralNet* neural_net):neural_net(neural_net){

  learning_rate=0.1;

  int input_number = neural_net->input_number;
  int hidden_number = neural_net->hidden_number;
  int output_number = neural_net->output_number;

  input_hidden_pos_weight_der = std::vector<std::vector<float>>(input_number);
  hidden_output_pos_weight_der = std::vector<std::vector<float>>(hidden_number);
  input_hidden_neg_weight_der = std::vector<std::vector<float>>(input_number);
  hidden_output_neg_weight_der = std::vector<std::vector<float>>(hidden_number);

  for(int i=0;i<input_number;i++){

    input_hidden_pos_weight_der[i] = std::vector<float>(hidden_number,0);
    input_hidden_neg_weight_der[i] = std::vector<float>(hidden_number,0);

  }

  for(int j=0;j<hidden_number;j++){

    hidden_output_pos_weight_der[j] = std::vector<float>(output_number,0);
    hidden_output_neg_weight_der[j] = std::vector<float>(output_number,0);

  }


}

void Trainer::Train(std::vector<DataEntry> data_set){

  int input_number = neural_net->GetInputNumber();
  int hidden_number = neural_net->GetHiddenNumber();
  int output_number = neural_net->GetOutputNumber();

  std::vector<float> cost = std::vector<float>(output_number,0);

  for(std::vector<DataEntry>::iterator data_entry = data_set.begin();data_entry != data_set.end();++data_entry){

    std::vector<float> output = neural_net->Output(data_entry->predictor);

    std::vector<float> u_input_hidden = neural_net->GetUInputHidden();
    std::vector<float> v_input_hidden = neural_net->GetVInputHidden();
    std::vector<float> u_hidden_output = neural_net->GetUHiddenOutput();
    std::vector<float> v_hidden_output = neural_net->GetVHiddenOutput();

    std::vector<std::vector<float>> input_hidden_pos_weight = neural_net->GetInputHiddenPosWeight();
    std::vector<std::vector<float>> hidden_output_pos_weight = neural_net->GetHiddenOutputPosWeight();
    std::vector<std::vector<float>> input_hidden_neg_weight = neural_net->GetInputHiddenNegWeight();
    std::vector<std::vector<float>> hidden_output_neg_weight = neural_net->GetHiddenOutputNegWeight();

    cost = (*Cost)(data_entry->predicted,output);

    for(int i=0;i<input_number;i++){
      for(int j=0;j<hidden_number;j++){
        for(int k=0;k<output_number;k++){

        input_hidden_pos_weight_der[i][j] += cost[k] * (neural_net->input_neuron[i])/((1+v_input_hidden[j])*(1+v_hidden_output[k]))*(hidden_output_pos_weight[j][k]-output[k]*hidden_output_neg_weight[j][k]);
        input_hidden_neg_weight_der[i][j] += cost[k] * (neural_net->hidden_neuron[j]) * (neural_net->input_neuron[i])/((1+v_input_hidden[j])*(1+v_hidden_output[k]))*(output[k]*hidden_output_neg_weight[j][k]-hidden_output_pos_weight[j][k]);

        }
      }
    }

    for(int j=0;j<hidden_number;j++){
      for(int k=0;k<output_number;k++){

        hidden_output_pos_weight_der[j][k] += cost[k] * (neural_net->hidden_neuron[j])/(1+v_hidden_output[k]);
        hidden_output_neg_weight_der[j][k] += cost[k] * (-1) * (neural_net->output_neuron[k]) * (neural_net->hidden_neuron[j])/(1+v_hidden_output[k]);

      }
    }

    for(int i=0;i<input_number;i++){
      for(int j=0;j<hidden_number;j++){

        input_hidden_pos_weight[i][j] = input_hidden_pos_weight[i][j] + learning_rate*input_hidden_pos_weight_der[i][j];
        input_hidden_neg_weight[i][j] = input_hidden_neg_weight[i][j] + learning_rate*input_hidden_neg_weight_der[i][j];

      }
    }

    for(int j=0;j<hidden_number;j++){
      for(int k=0;k<output_number;k++){

        hidden_output_pos_weight[j][k] = hidden_output_pos_weight[j][k] + learning_rate*hidden_output_pos_weight_der[j][k];
        hidden_output_neg_weight[j][k] = hidden_output_neg_weight[j][k] + learning_rate*hidden_output_neg_weight_der[j][k];

      }
    }

    neural_net->SetInputHiddenPosWeight(input_hidden_pos_weight);
    neural_net->SetInputHiddenNegWeight(input_hidden_neg_weight);
    neural_net->SetHiddenOutputPosWeight(hidden_output_pos_weight);
    neural_net->SetHiddenOutputNegWeight(hidden_output_neg_weight);
    for(int i = 0; i<input_number;i++){
      std::fill(input_hidden_pos_weight_der[i].begin(), input_hidden_pos_weight_der[i].end(), 0);
      std::fill(input_hidden_neg_weight_der[i].begin(), input_hidden_neg_weight_der[i].end(), 0);
    }
    for(int j = 0 ; j<hidden_number;j++){
      std::fill(hidden_output_pos_weight_der[j].begin(), hidden_output_pos_weight_der[j].end(), 0);
      std::fill(hidden_output_neg_weight_der[j].begin(), hidden_output_neg_weight_der[j].end(), 0);
    }

  }

}


std::vector<float> Trainer::Score(std::vector<DataEntry> data_set, std::vector<float> (*ScoreFunction)(std::vector<float> data_set,std::vector<float> output)){

  std::vector<float> score = std::vector<float>(neural_net->GetOutputNumber(),0);

  for(std::vector<DataEntry>::iterator data_entry = data_set.begin();data_entry != data_set.end();++data_entry){

    std::vector<float> output = neural_net->Output(data_entry->predictor);

    for(int k = 0; k < neural_net->GetOutputNumber(); k++){

      score[k] += ScoreFunction(data_entry->predicted,output)[k];

    }

  }

  return score;

}

void Trainer::SetCost (std::vector<float> (*Cost)(std::vector<float> data_set,std::vector<float> output)){
  this->Cost=Cost;
}
