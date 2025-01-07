from adaline import Adaline
from madaline import Madaline
from utils import create_dataset
from plot_utils import plot_combined


def main():
    print("\nWelcome to the Logic Gate Simulator!")
    print("Available gates: AND, OR, XOR, NOR, XNOR, NAND")
    print("Type 'EXIT' to quit the program.")

    while True:
        gate = input("\nEnter the gate type: ").strip().upper()

        if gate == "EXIT":
            print("\nExiting the program. Goodbye!")
            break

        try:
            X, y = create_dataset(gate)
        except ValueError as e:
            print(e)
            continue

        print(f"\nTraining model for {gate} gate...")

        if gate in ["XOR", "XNOR"]:
            model = Madaline(n_neurons=2, gate_type=gate)
        else:
            model = Adaline(learning_rate=0.1, epochs=1000)

        model.fit(X, y)
        predictions = model.predict(X)
        plot_combined(gate, X, y, predictions, model)


if __name__ == "__main__":
    main()
