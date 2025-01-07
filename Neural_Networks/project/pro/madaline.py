import numpy as np

class Madaline:
    def __init__(self, n_neurons=2, learning_rate=0.1, epochs=1000, gate_type="XOR"):
        self.weights = []
        self.biases = []
        self.n_neurons = n_neurons
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.gate_type = gate_type

    def fit(self, X, y):
        n_features = X.shape[1]
        self.weights = np.random.uniform(-1, 1, size=(self.n_neurons, n_features))
        self.biases = np.random.uniform(-1, 1, size=self.n_neurons)

        for _ in range(self.epochs):
            for i, x in enumerate(X):
                neuron_outputs = np.dot(self.weights, x) + self.biases
                neuron_activations = (neuron_outputs >= 0).astype(int)

                if self.gate_type == "XOR":
                    predicted_output = (neuron_activations[0] ^ neuron_activations[1]).astype(int)
                elif self.gate_type == "XNOR":
                    predicted_output = (neuron_activations[0] == neuron_activations[1]).astype(int)
                else:
                    raise ValueError("Invalid gate type for Madaline")

                error = y[i] - predicted_output
                if error != 0:
                    for j in range(self.n_neurons):
                        self.weights[j] += self.learning_rate * error * x
                        self.biases[j] += self.learning_rate * error

    def predict(self, X):
        neuron_outputs = np.dot(X, self.weights.T) + self.biases
        neuron_activations = (neuron_outputs >= 0).astype(int)

        if self.gate_type == "XOR":
            return (neuron_activations[:, 0] ^ neuron_activations[:, 1]).astype(int)
        elif self.gate_type == "XNOR":
            return (neuron_activations[:, 0] == neuron_activations[:, 1]).astype(int)
        else:
            raise ValueError("Invalid gate type for Madaline")
