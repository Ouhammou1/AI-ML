import numpy as np

class Adaline:
    def __init__(self, learning_rate=0.01, epochs=1000):
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.weights = None
        self.bias = None

    def fit(self, X, y):
        n_samples, n_features = X.shape
        self.weights = np.zeros(n_features)
        self.bias = 0

        for _ in range(self.epochs):
            for i, x in enumerate(X):
                linear_output = np.dot(x, self.weights) + self.bias
                error = y[i] - linear_output
                self.weights += self.learning_rate * error * x
                self.bias += self.learning_rate * error

    def predict(self, X):
        linear_output = np.dot(X, self.weights) + self.bias
        return (linear_output >= 0.5).astype(int)
