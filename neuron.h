#ifndef NEURON_H_
#define NEURON_H_

class Neuron
{

  public:
    Neuron(int weight_pos, int weight_neg, int rate);

    int GetWeightPos () const;
    int GetWeightNeg () const;
    int GetRate () const;

    void SetWeightPos (const int weight_pos);
    void SetWeightNeg (const int weight_neg);
    void SetRate (const int rate);

    float Output(float inputPos, float inputNeg);

  private:
    int weight_pos;
    int weight_neg;
    int rate;

};

#endif // NEURON_H_
