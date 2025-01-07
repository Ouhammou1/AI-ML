import numpy as np

def create_dataset(gate):
    gates = {
        "AND": (np.array([[0, 0], [0, 1], [1, 0], [1, 1]]), np.array([0, 0, 0, 1])),
        "OR": (np.array([[0, 0], [0, 1], [1, 0], [1, 1]]), np.array([0, 1, 1, 1])),
        "XOR": (np.array([[0, 0], [0, 1], [1, 0], [1, 1]]), np.array([0, 1, 1, 0])),
        "XNOR": (np.array([[0, 0], [0, 1], [1, 0], [1, 1]]), np.array([1, 0, 0, 1])),
        "NOR": (np.array([[0, 0], [0, 1], [1, 0], [1, 1]]), np.array([1, 0, 0, 0])),
        "NAND": (np.array([[0, 0], [0, 1], [1, 0], [1, 1]]), np.array([1, 1, 1, 0])),
    }
    if gate not in gates:
        raise ValueError(f"Invalid gate '{gate}'. Available gates: {', '.join(gates.keys())}")
    return gates[gate]
