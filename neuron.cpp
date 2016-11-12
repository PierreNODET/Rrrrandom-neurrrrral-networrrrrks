#include "neuron.h"

Neuron::Neuron(int a, int b, int c):weight_pos(a),weight_neg(b),rate(c){
};

int Neuron::GetWeightPos() const {
  return weight_pos;
}

int Neuron::GetWeightNeg() const {
  return weight_neg;
}

int Neuron::GetRate() const {
  return rate;
}

void Neuron::SetWeightPos(const int a){
  weight_pos=a;
}

void Neuron::SetWeightNeg(const int a){
  weight_neg=a;
}

void Neuron::SetRate(const int a){
  rate=a;
}
