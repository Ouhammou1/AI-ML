import numpy as np

class Adaline:
    def __init__(self, learning_rate=0.00001, n_iterations=485):
        self.learning_rate = learning_rate
        self.n_iterations = n_iterations
        self.errors_ = []

    def fit(self, X, y):
        self.weights = np.random.normal(0, 0.01, size=(1 + X.shape[1]))
        for epoch in range(self.n_iterations):
            net_input = self.net_input(X)
            output = self.activation(net_input)
            errors = y - output
            self.weights[1:] += self.learning_rate * X.T.dot(errors)
            self.weights[0] += self.learning_rate * errors.sum()
            mse = np.mean(errors**2)
            self.errors_.append(mse)
            if mse < self.learning_rate:
                print(f"Early stopping at epoch {epoch + 1}")
                break
            print(f"Epoch {epoch + 1}: Mean Error = {mse:.5f}, Weights Mean = {np.mean(self.weights):.5f}")
        return self

    def net_input(self, X):
        return np.dot(X, self.weights[1:]) + self.weights[0]

    def activation(self, X):
        return X

    def predict(self, X):
        return np.where(self.activation(self.net_input(X)) >= 0.5, 1, 0)
