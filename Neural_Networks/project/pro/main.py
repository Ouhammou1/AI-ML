
from adaline import Adaline
from utils import create_dataset, plot_truth_table, plot_decision_boundary
import matplotlib.pyplot as plt

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

        print(f"\nTraining Adaline model for {gate} gate...")

        # Train the Adaline model
        model = Adaline(learning_rate=0.1, epochs=1000)
        model.fit(X, y)

        # Predict using the model
        predictions = model.predict(X)

        # Display the truth table
        print(f"\nTruth Table for {gate} Gate:")
        plot_truth_table(gate, X, y, predictions)

        # Display the decision boundary (if applicable)
        if X.shape[1] == 2:  # Decision boundary only for 2D inputs
            print(f"\nPlotting Decision Boundary for {gate} Gate...")
            plot_decision_boundary(X, y, model, gate)

        # Ensure both plots are displayed simultaneously
        plt.show(block=False)  # Non-blocking mode to show both plots
        input("\nPress Enter to continue...")
        plt.close("all")  # Close all open plots before the next iteration

if __name__ == "__main__":
    main()



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
