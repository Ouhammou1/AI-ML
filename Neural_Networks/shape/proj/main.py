import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from ipywidgets import Button, Output, VBox, FileUpload
from IPython.display import display, clear_output

from adaline import Adaline
from madaline import Madaline
from shape_generation import create_dataset
from helpers import predict_shape, calculate_accuracy

# Initialize system
X, y = create_dataset(485)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

shapes = ['circle', 'square', 'triangle', 'pentagon', 'hexagon']
shape_models = {shape: {'adaline': Adaline(), 'madaline': Madaline()} for shape in shapes}
for i, shape in enumerate(shapes):
    print(f"Training {shape} models...")
    shape_models[shape]['adaline'].fit(X_train_scaled, y_train[:, i])
    shape_models[shape]['madaline'].fit(X_train_scaled, y_train[:, i])

accuracy = calculate_accuracy(X_test_scaled, y_test, shape_models)
print(f"Model Accuracy: {accuracy:.2%}")

# Define widgets and interactions
output = Output()

# Define functions for interactive widgets (as in the original main code)
button1 = Button(description="Generate and Test Shape")
button2 = Button(description="View Accuracy and Errors")
button3 = Button(description="Exit")

display(VBox([button1, button2, button3]), output)
