import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def create_dataset(gate):
    if gate == "XOR":
        X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        y = np.array([0, 1, 1, 0])
    elif gate == "XNOR":
        X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        y = np.array([1, 0, 0, 1])
    elif gate == "AND":
        X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        y = np.array([0, 0, 0, 1])
    elif gate == "OR":
        X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        y = np.array([0, 1, 1, 1])
    elif gate == "NOR":
        X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        y = np.array([1, 0, 0, 0])
    elif gate == "NAND":
        X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
        y = np.array([1, 1, 1, 0])
    else:
        raise ValueError("Invalid gate type")
    return X, y


def plot_truth_table(gate_type, X, y, predictions):
    table_data = {
        "Input A": X[:, 0],
        "Input B": X[:, 1],
        "True Output": y,
        "Predicted Output": predictions
    }
    df = pd.DataFrame(table_data)
    fig, ax = plt.subplots(figsize=(6, 2))
    ax.axis("tight")
    ax.axis("off")
    ax.table(cellText=df.values, colLabels=df.columns, loc="center", cellLoc="center")
    plt.title(f"Truth Table for {gate_type} Gate", fontsize=12, pad=20)
    plt.show()


def plot_decision_boundary(X, y, model, gate_type):
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.1),
                         np.arange(y_min, y_max, 0.1))
    grid = np.c_[xx.ravel(), yy.ravel()]
    predictions = model.predict(grid)
    predictions = predictions.reshape(xx.shape)

    plt.contourf(xx, yy, predictions, alpha=0.8)
    plt.scatter(X[:, 0], X[:, 1], c=y, edgecolor="k")
    plt.title(f"Decision Boundary for {gate_type} Gate")
    plt.xlabel("Input A")
    plt.ylabel("Input B")
    plt.show()
