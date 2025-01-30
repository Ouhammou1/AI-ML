!pip install gradio numpy scikit-learn pillow

import numpy as np
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.metrics import accuracy_score, confusion_matrix
from PIL import Image
import gradio as gr

# Load and preprocess dataset
digits = load_digits()
X = digits.data  # 64 features (8x8 images flattened)
y = digits.target.reshape(-1, 1)  # Labels (0-9)

# Normalize the input
scaler = StandardScaler()
X = scaler.fit_transform(X)

# One-hot encode the labels for Madaline
encoder = OneHotEncoder(sparse_output=False)
y_onehot = encoder.fit_transform(y)

# Train-test split
X_train, X_test, y_train, y_test = train_test_split(X, y_onehot, test_size=0.2, random_state=42)

# Adaline Class
class Adaline:
    def __init__(self, input_dim, lr=0.01, epochs=50):
        self.lr = lr
        self.epochs = epochs
        self.weights = np.random.randn(input_dim)
        self.bias = 0

    def activation(self, x):
        return np.dot(x, self.weights) + self.bias

    def train(self, X, y):
        for epoch in range(self.epochs):
            for i in range(len(X)):
                y_pred = self.activation(X[i])
                error = y[i] - y_pred
                self.weights += self.lr * error * X[i]
                self.bias += self.lr * error

    def predict(self, X):
        return np.array([1 if self.activation(x) > 0 else 0 for x in X])

# Madaline Class
class Madaline:
    def __init__(self, input_dim, output_dim, lr=0.01, epochs=50):
        self.lr = lr
        self.epochs = epochs
        self.weights = np.random.randn(output_dim, input_dim)
        self.biases = np.zeros(output_dim)

    def activation(self, x):
        return np.dot(self.weights, x) + self.biases

    def train(self, X, y):
        for epoch in range(self.epochs):
            for i in range(len(X)):
                outputs = self.activation(X[i])
                outputs = np.where(outputs > 0, 1, 0)  # Step function
                errors = y[i] - outputs
                for j in range(len(errors)):
                    self.weights[j] += self.lr * errors[j] * X[i]
                    self.biases[j] += self.lr * errors[j]

    def predict(self, X):
        predictions = []
        for x in X:
            outputs = self.activation(x)
            outputs = np.where(outputs > 0, 1, 0)  # Step function
            predictions.append(outputs)
        return np.array(predictions)

# Step 1: Feature Extraction using Adaline
adaline_units = []
num_features = X_train.shape[1]
num_adaline_units = 10  # Number of features to extract
feature_outputs_train = np.zeros((X_train.shape[0], num_adaline_units))
feature_outputs_test = np.zeros((X_test.shape[0], num_adaline_units))

# Train Adaline units
for i in range(num_adaline_units):
    adaline = Adaline(input_dim=num_features, lr=0.01, epochs=50)
    adaline.train(X_train, y_train[:, i])  # Train on each one-hot encoded digit
    feature_outputs_train[:, i] = adaline.predict(X_train)
    feature_outputs_test[:, i] = adaline.predict(X_test)
    adaline_units.append(adaline)

# Step 2: Final Classification using Madaline
madaline = Madaline(input_dim=num_adaline_units, output_dim=10, lr=0.01, epochs=50)
madaline.train(feature_outputs_train, y_train)

# Step 3: Evaluate the Model
# Predict on test set
y_pred_onehot = madaline.predict(feature_outputs_test)

# Convert one-hot predictions to class labels
y_pred = np.argmax(y_pred_onehot, axis=1)
y_true = np.argmax(y_test, axis=1)

# Accuracy and Confusion Matrix
accuracy = accuracy_score(y_true, y_pred)
conf_matrix = confusion_matrix(y_true, y_pred)

print("Accuracy:", accuracy)
print("Confusion Matrix:\n", conf_matrix)

# Gradio Interface for Digit Recognition
def predict_digit_from_gradio(canvas_image):
    # Ensure the input is a NumPy array
    try:
        canvas_image = Image.fromarray(canvas_image.astype("uint8"))
    except AttributeError:
        return "Invalid input. Please draw a digit."

    # Resize and preprocess the image
    canvas_image = canvas_image.resize((8, 8)).convert("L")  # Resize and convert to grayscale
    img_array = np.array(canvas_image)
    img_array = img_array / 255.0  # Normalize pixel values
    img_flattened = img_array.flatten()
    img_flattened = scaler.transform([img_flattened])[0]

    # Perform feature extraction and prediction
    try:
        features = np.array([adaline.activation(img_flattened) for adaline in adaline_units])
        output = madaline.activation(features)
        predicted_digit = np.argmax(output)
        confidence = max(output) / sum(output) * 100  # Calculate confidence percentage
        return f"Predicted Digit: {predicted_digit} ({confidence:.2f}% confidence)"
    except Exception as e:
        return f"Error in prediction: {str(e)}"

# Define the Gradio Interface
interface = gr.Interface(
    fn=predict_digit_from_gradio,
    inputs=gr.Image(type="numpy", label="Draw a digit (280x280)"),
    outputs="text",
    title="Digit Recognizer",
    description="Draw a digit on the canvas, and the model will predict it.",
)

# Launch the Interface
interface.launch(share=True)
