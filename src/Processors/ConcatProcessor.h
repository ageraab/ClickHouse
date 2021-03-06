#pragma once

#include <Processors/IProcessor.h>


namespace DB
{

/** Has arbitary non zero number of inputs and one output.
  * All of them have the same structure.
  *
  * Pulls all data from first input, then all data from second input, etc...
  * Doesn't do any heavy calculations.
  * Preserves an order of data.
  */
class ConcatProcessor : public IProcessor
{
public:
    ConcatProcessor(const Block & header, size_t num_inputs)
        : IProcessor(InputPorts(num_inputs, header), OutputPorts{header}), current_input(inputs.begin())
    {
    }

    String getName() const override { return "Concat"; }

    Status prepare() override;

    OutputPort & getOutputPort() { return outputs.front(); }

private:
    InputPorts::iterator current_input;
};

}

