#include "neuron.h"

Neuron::Neuron(float a, float b, float c):weight_pos(a),weight_neg(b),rate(c){
};

float Neuron::GetWeightPos() const {
  return weight_pos;
}

float Neuron::GetWeightNeg() const {
  return weight_neg;
}

float Neuron::GetRate() const {
  return rate;
}

void Neuron::SetWeightPos(const float a){
  weight_pos=a;
}

void Neuron::SetWeightNeg(const float a){
  weight_neg=a;
}

void Neuron::SetRate(const float a){
  rate=a;
}

float Neuron::Output(float inputPos, float inputNeg){
  return GetWeightPos()*inputPos/(1+GetWeightNeg()*inputNeg);
}
