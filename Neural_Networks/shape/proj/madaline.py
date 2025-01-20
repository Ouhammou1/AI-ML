import numpy as np
from adaline import Adaline

class Madaline:
    def __init__(self, n_adalines=3, learning_rate=0.00001, n_iterations=485):
        self.n_adalines = n_adalines
        self.adalines = [Adaline(learning_rate, n_iterations) for _ in range(n_adalines)]

    def fit(self, X, y):
        feature_split = np.array_split(X, self.n_adalines, axis=1)
        for i, adaline in enumerate(self.adalines):
            adaline.fit(feature_split[i], y)
        return self

    def predict(self, X):
        feature_split = np.array_split(X, self.n_adalines, axis=1)
        predictions = np.array([adaline.predict(split) for adaline, split in zip(self.adalines, feature_split)])
        return np.where(predictions.mean(axis=0) >= 0.5, 1, 0)
