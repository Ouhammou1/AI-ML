import numpy as np

class Adaline:
    def __init__(self, learning_rate=0.00001, n_iterations=20):
        self.learning_rate = learning_rate
        self.n_iterations = n_iterations
        self.errors_ = []

    def fit(self, X, y):
        self.weights = np.random.normal(0, 0.01, size=(1 + X.shape[1]))
        for epoch in range(self.n_iterations):
            net_input = self.net_input(X)
            output = self.activation(net_input)
            errors = y - output
            self.weights[1:] += self.learning_rate * (X.T.dot(errors) - 0.01 * self.weights[1:])
            self.weights[0] += self.learning_rate * errors.sum()
            self.weights = np.clip(self.weights, -1e3, 1e3)
            mse = np.mean(errors**2)
            self.errors_.append(mse)
            print(f"Epoch {epoch + 1}: Mean Error = {mse:.5f}, Weights Mean = {np.mean(self.weights):.5f}")
        return self

    def net_input(self, X):
        return np.dot(X, self.weights[1:]) + self.weights[0]

    def activation(self, X):
        return X

    def predict(self, X):
        return np.where(self.activation(self.net_input(X)) >= 0.5, 1, 0)


class Madaline:
    def __init__(self, n_adalines=3, learning_rate=0.00001, n_iterations=20):
        self.n_adalines = n_adalines
        self.adalines = [Adaline(learning_rate, n_iterations) for _ in range(self.n_adalines)]

    def fit(self, X, y):
        feature_split = np.array_split(X, self.n_adalines, axis=1)
        for i, adaline in enumerate(self.adalines):
            adaline.fit(feature_split[i], y)
        return self

    def predict(self, X):
        feature_split = np.array_split(X, self.n_adalines, axis=1)
        predictions = np.array([adaline.predict(split) for adaline, split in zip(self.adalines, feature_split)])
        return np.where(predictions.mean(axis=0) >= 0.5, 1, 0)
