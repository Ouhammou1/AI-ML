!pip install streamlit
import numpy as np
import cv2
import os
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import streamlit as st

# Adaline Class for Binary Classification
class Adaline:
    def __init__(self, input_size, learning_rate=0.01, epochs=100):
        self.weights = np.zeros(input_size + 1)  # Includes bias
        self.learning_rate = learning_rate
        self.epochs = epochs

    def predict(self, X):
        X_with_bias = np.c_[np.ones((X.shape[0], 1)), X]
        linear_output = np.dot(X_with_bias, self.weights)
        return np.where(linear_output >= 0.0, 1, 0)

    def train(self, X, y):
        X_with_bias = np.c_[np.ones((X.shape[0], 1)), X]

        for _ in range(self.epochs):
            for xi, target in zip(X_with_bias, y):
                output = np.dot(xi, self.weights)
                error = target - output
                self.weights += self.learning_rate * error * xi

        print("Training complete. Weights:", self.weights)

# Image Preprocessing Function
def preprocess_image(image_path, target_size=(48, 48)):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    image = cv2.resize(image, target_size)
    return image.flatten() / 255.0  # Normalize pixel values to [0, 1]

# Load Dataset
def load_dataset(data_dir):
    images = []
    labels = []
    for label in os.listdir(data_dir):
        label_dir = os.path.join(data_dir, label)
        if os.path.isdir(label_dir):
            for img_file in os.listdir(label_dir):
                img_path = os.path.join(label_dir, img_file)
                images.append(preprocess_image(img_path))
                labels.append(label)
    return np.array(images), np.array(labels)

# Main Program
def main():
    st.title("Emotion Detection using Adaline")
    st.write("Upload an image to detect whether the person is 'happy' or 'sad'.")

    # Dataset Path
    data_dir = "/content/dataset"  # Replace with your dataset path
    X, y = load_dataset(data_dir)

    # Encode Labels
    label_encoder = LabelEncoder()
    y_encoded = label_encoder.fit_transform(y)  # Converts labels to integers (e.g., "happy" -> 0, "sad" -> 1)

    # Split Data
    X_train, X_test, y_train, y_test = train_test_split(X, y_encoded, test_size=0.2, random_state=42)

    # Train Adaline Model
    adaline = Adaline(input_size=X_train.shape[1])
    adaline.train(X_train, y_train)

    # Evaluate on Test Data
    y_pred = adaline.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    st.write(f"Model Accuracy: {accuracy * 100:.2f}%")

    # Image Upload for Prediction
    uploaded_file = st.file_uploader("Upload an image (JPG/PNG)", type=["jpg", "png"])
    if uploaded_file is not None:
        # Save and preprocess the uploaded image
        with open("uploaded_image.jpg", "wb") as f:
            f.write(uploaded_file.getbuffer())
        input_image = preprocess_image("uploaded_image.jpg")

        # Predict Emotion
        prediction = adaline.predict(np.expand_dims(input_image, axis=0))[0]
        emotion = label_encoder.inverse_transform([prediction])[0]
        st.write(f"The predicted emotion is: **{emotion}**")

        # Display Uploaded Image
        st.image("uploaded_image.jpg", caption="Uploaded Image", use_column_width=True)

if __name__ == "__main__":
    main()
