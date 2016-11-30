#ifndef NEURON_H_
#define NEURON_H_

class Neuron
{

  public:
    Neuron(float weight_pos, float weight_neg, float rate);

    float GetWeightPos () const;
    float GetWeightNeg () const;
    float GetRate () const;

    void SetWeightPos (const float weight_pos);
    void SetWeightNeg (const float weight_neg);
    void SetRate (const float rate);

    float Output(float inputPos, float inputNeg);

  private:
    float weight_pos;
    float weight_neg;
    float rate;

};

#endif // NEURON_H_
