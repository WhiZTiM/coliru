#include "../JuceLibraryCode/JuceHeader.h"

class Controller {
protected:
    std::vector<MidiInput*> inputs;
	std::vector<MidiOutput*> outputs;
	MidiCallback *callback;

	virtual ~Controller();
public:
	Controller(std::vector<int> inputPorts, std::vector<int> outputPorts);

	virtual void initializeController() = 0;
	virtual void sendMessage(int byte1, int byte2, int byte3);

	void setCallback(MidiCallback *callback);
	MidiCallback* getCallback();

	void addInput(MidiInput *input);
	MidiInput* getInput(int index);
	std::vector<MidiInput*> getInputs();
	void startInputs();

	void addOutput(MidiOutput *output);
	MidiOutput* getOutput(int index);
	std::vector<MidiOutput*> getOutputs();
};

Controller::Controller(std::vector<int> inputPorts, std::vector<int> outputPorts)
{
    for (size_t i = 0; i < outputPorts.size(); ++i) {
		this->addOutput(MidiOutput::openDevice(outputPorts[i]));
	}

	this->setCallback(new MidiCallback(this));

	for (size_t i = 0; i < inputPorts.size(); ++i) {
		MidiInput* input = MidiInput::openDevice(inputPorts[i], this->getCallback());
		//input->start();
		inputs.push_back(input);
	}

	for (size_t i = 0; i < inputPorts.size(); ++i) {
		MidiInput* input = inputs[i];
		input->start();
	}

	//startInputs();
}
