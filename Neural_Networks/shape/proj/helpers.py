import numpy as np
import cv2
from sklearn.preprocessing import StandardScaler

def preprocess_image(image_array):
    # Add feature extraction logic here (as in original code)
    return processed_image, features

def predict_shape(image, models):
    processed_image, features = preprocess_image(image)
    # (Prediction logic from the original code)
    return predicted_shape

def calculate_accuracy(X_test, y_test, models):
    correct = 0
    for i in range(len(X_test)):
        actual_shape = shapes[np.argmax(y_test[i])]
        predicted_shape = predict_shape(X_test[i].reshape(64, 64), models)
        if actual_shape == predicted_shape:
            correct += 1
    return correct / len(X_test)
