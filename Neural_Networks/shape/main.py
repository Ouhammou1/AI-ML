import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from ipywidgets import Button, Output, VBox
from IPython.display import display, clear_output

from models import Adaline, Madaline
from dataset import create_dataset, generate_shape

# Initialize dataset
print("Initializing Shape Recognition System...")
X, y = create_dataset(500)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

shapes = ['circle', 'square', 'triangle', 'pentagon', 'hexagon']
shape_models = {}

# Train models
for i, shape in enumerate(shapes):
    print(f"Training models for {shape}...")
    adaline = Adaline(learning_rate=0.00001, n_iterations=20)
    adaline.fit(X_train_scaled, y_train[:, i])
    madaline = Madaline(n_adalines=3, learning_rate=0.00001, n_iterations=20)
    madaline.fit(X_train_scaled, y_train[:, i])
    shape_models[shape] = {'adaline': adaline, 'madaline': madaline}

accuracy = np.mean([
    shape_models[shape]['adaline'].errors_[-1]
    for shape in shapes
])

output = Output()

def generate_shape_and_test(_):
    with output:
        clear_output(wait=True)
        random_shape = random.choice(shapes)
        test_image = generate_shape(random_shape)
        predicted_shape = predict_shape(test_image, shape_models)
        plt.imshow(test_image, cmap='gray')
        plt.title(f'Generated: {random_shape}\nPredicted: {predicted_shape}')
        plt.axis('off')
        plt.show()

def view_accuracy_and_plot(_):
    with output:
        clear_output(wait=True)
        print(f"\nCurrent Model Accuracy: {accuracy:.2%}")
        plt.figure(figsize=(10, 5))
        for shape in shapes:
            errors = shape_models[shape]['adaline'].errors_
            plt.plot(errors, label=f'{shape.capitalize()}')
        plt.xlabel("Epochs")
        plt.ylabel("Mean Squared Error")
        plt.legend()
        plt.title("Error Progression")
        plt.show()

def exit_program(_):
    with output:
        clear_output(wait=True)
        print("Thank you for using the Shape Recognition System!")

button1 = Button(description="Generate and Test Random Shape")
button1.on_click(generate_shape_and_test)

button2 = Button(description="View Model Accuracy and Errors")
button2.on_click(view_accuracy_and_plot)

button3 = Button(description="Exit")
button3.on_click(exit_program)

display(VBox([button1, button2, button3]), output)
