from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from adaline import Adaline
from madaline import Madaline
from shapes import create_dataset, generate_shape
from helper import predict_shape, calculate_accuracy
from interactive_buttons import setup_buttons
import random
import matplotlib.pyplot as plt

# Initialize and create dataset
print("Initializing Shape Recognition System...")
X, y = create_dataset(485)  # Number of samples
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Scale features
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Define shape categories and initialize models
shapes = ['circle', 'square', 'triangle', 'pentagon', 'hexagon']
shape_models = {}

# Train models for each shape
for i, shape in enumerate(shapes):
    print(f"Training models for {shape}...")
    adaline = Adaline(learning_rate=0.00001, n_iterations=485)
    adaline.fit(X_train_scaled, y_train[:, i])
    madaline = Madaline(n_adalines=3, learning_rate=0.00001, n_iterations=485)
    madaline.fit(X_train_scaled, y_train[:, i])
    shape_models[shape] = {'adaline': adaline, 'madaline': madaline}

# Calculate and display model accuracy
accuracy = calculate_accuracy(X_test, y_test, shapes, shape_models, scaler)
print(f"\nModel Accuracy: {accuracy:.2%}")

# Define functions for button actions
def generate_shape_and_test(_):
    """Generate a random shape and predict its class."""
    random_shape = random.choice(shapes)
    test_image = generate_shape(random_shape)
    predicted_shape = predict_shape(test_image, shape_models, scaler)
    plt.imshow(test_image, cmap='gray')
    plt.title(f'Generated: {random_shape}\nPredicted: {predicted_shape}')
    plt.axis('off')
    plt.show()

def view_accuracy_and_plot(_):
    """Display current accuracy and plot training error progression."""
    print(f"\nCurrent Model Accuracy: {accuracy:.2%}")
    print("\nPlotting Error Progression for Each Shape...\n")

    # Plot error progression for each shape
    plt.figure(figsize=(15, 10))
    for i, shape in enumerate(shapes):
        adaline_errors = shape_models[shape]['adaline'].errors_
        madaline_errors = []
        for adaline in shape_models[shape]['madaline'].adalines:
            madaline_errors.append(adaline.errors_)

        # Adaline errors
        plt.subplot(len(shapes), 2, i * 2 + 1)
        plt.plot(adaline_errors, label=f'Adaline - {shape.capitalize()}')
        plt.title(f'{shape.capitalize()} - Adaline Error')
        plt.xlabel('Epochs')
        plt.ylabel('Mean Squared Error')
        plt.legend()

        # Madaline errors
        plt.subplot(len(shapes), 2, i * 2 + 2)
        for j, errors in enumerate(madaline_errors):
            plt.plot(errors, label=f'Madaline Adaline-{j + 1}')
        plt.title(f'{shape.capitalize()} - Madaline Error')
        plt.xlabel('Epochs')
        plt.ylabel('Mean Squared Error')
        plt.legend()

    plt.tight_layout()
    plt.show()

# Setup interactive buttons
setup_buttons(generate_shape_and_test, view_accuracy_and_plot)
