from adaline import Adaline
from utils import create_dataset
import matplotlib.pyplot as plt
import pandas as pd

def display_table_and_graph(gate_type, X, y, predictions, model):
    """
    Display the truth table and decision boundary in the same figure.
    """
    # Create a Matplotlib figure with 2 subplots: 1 for the table and 1 for the graph
    fig, axes = plt.subplots(1, 2, figsize=(12, 6))
    fig.suptitle(f"{gate_type} Gate", fontsize=16)

    # Plot the truth table
    table_data = {
        "Input A": X[:, 0],
        "Input B": X[:, 1],
        "True Output": y,
        "Predicted Output": predictions
    }
    df = pd.DataFrame(table_data)
    axes[0].axis("tight")
    axes[0].axis("off")
    axes[0].table(cellText=df.values, colLabels=df.columns, loc="center", cellLoc="center")
    axes[0].set_title("Truth Table", fontsize=14)

    # Plot the decision boundary (if applicable)
    if X.shape[1] == 2:  # Only plot decision boundary for 2D inputs
        x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
        y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
        xx, yy = np.meshgrid(
            np.arange(x_min, x_max, 0.1),
            np.arange(y_min, y_max, 0.1)
        )
        grid = np.c_[xx.ravel(), yy.ravel()]
        predictions = model.predict(grid)
        predictions = predictions.reshape(xx.shape)

        axes[1].contourf(xx, yy, predictions, alpha=0.8)
        axes[1].scatter(X[:, 0], X[:, 1], c=y, edgecolor="k")
        axes[1].set_title("Decision Boundary", fontsize=14)
        axes[1].set_xlabel("Input A")
        axes[1].set_ylabel("Input B")
    else:
        axes[1].axis("off")
        axes[1].text(0.5, 0.5, "Decision boundary not applicable", 
                     horizontalalignment="center", verticalalignment="center", fontsize=12)

    # Show the figure
    plt.tight_layout()
    plt.show()


def main():
    print("\nAvailable gates: AND, OR, XOR, NOR, XNOR, NAND")
    print("Type 'EXIT' to quit the program.")
    while True:
        gate = input("Enter the gate type: ").strip().upper()

        if gate == "EXIT":
  


# from adaline import Adaline           
# from madaline import Madaline  
# from utils import (create_dataset, plot_truth_table,  plot_decision_boundary )

# def main():
#     print("\nAvailable gates: AND, OR, XOR, NOR, XNOR, NAND")
#     print("Type 'EXIT' to quit the program.")
#     while True:
#         gate = input("Enter the gate type: ").strip().upper()

#         if gate == "EXIT":
#             print("Exiting the program. Goodbye!")
#             break

#         try:
#             X, y = create_dataset(gate)
#         except ValueError as e:
#             print(e)
#             continue

#         # Train the Adaline model
#         model = Adaline(learning_rate=0.1, epochs=1000)
#         model.fit(X, y)

#         # Predict using the model
#         predictions = model.predict(X)

#         # Display the truth table
#         plot_truth_table(gate, X, y, predictions)

#         # Display the decision boundary
#         if X.shape[1] == 2:  # Decision boundary only for 2D inputs
#             plot_decision_boundary(X, y, model, gate)


# if __name__ == "__main__":
#     main()
