#!/usr/bin/env python3
from adaline import Adaline
from madaline import Madaline
from utils import create_dataset, plot_truth_table, plot_decision_boundary


def main():
    print("\nAvailable gates: AND, OR, XOR, NOR, XNOR, NAND")
    print("Type 'EXIT' to quit the program.")
    while True:
        gate = input("Enter the gate type: ").strip().upper()

        if gate == "EXIT":
            print("Exiting the program. Goodbye!")
            break

        try:
            X, y = create_dataset(gate)
        except ValueError as e:
            print(e)
            continue

        # Train the Adaline model
        model = Adaline(learning_rate=0.1, epochs=1000)
        model.fit(X, y)

        # Predict using the model
        predictions = model.predict(X)

        # Display the truth table
        plot_truth_table(gate, X, y, predictions)

        # Display the decision boundary
        if X.shape[1] == 2:  # Decision boundary only for 2D inputs
            plot_decision_boundary(X, y, model, gate)


if __name__ == "__main__":
    main()
