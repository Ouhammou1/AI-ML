import os
import numpy as np
import pandas as pd
from PIL import Image
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
import matplotlib.pyplot as plt
import seaborn as sns

# Constants
DATASET_DIR = "/content/dataset"
CSV_FILE = "/content/human_face_emotions.csv"
IMG_SIZE = (48, 48)
LEARNING_RATE = 0.01
EPOCHS = 2000

# Data Loading and Preprocessing
def create_csv_from_images(data_dir, csv_file, image_size=IMG_SIZE):
    data = []
    for label in os.listdir(data_dir):
        class_dir = os.path.join(data_dir, label)
        if os.path.isdir(class_dir):
            for img_file in os.listdir(class_dir):
                img_path = os.path.join(class_dir, img_file)
                try:
                    img = Image.open(img_path).convert('L').resize(image_size)
                    img_array = np.asarray(img).flatten()
                    data.append({'pixels': ' '.join(map(str, img_array)), 'emotion': label})
                except Exception as e:
                    print(f"Error processing {img_path}: {e}")
    pd.DataFrame(data).to_csv(csv_file, index=False)

def load_data(csv_file):
    try:
        df = pd.read_csv(csv_file)
        images = np.array([np.fromstring(pixels, sep=' ') for pixels in df['pixels']]).reshape(-1, *IMG_SIZE)
        labels = df['emotion'].values
        return images, labels
    except Exception as e:
        print(f"Error loading CSV: {e}")
        return None, None

def preprocess_data(images):
    return images / 255.0

# Madaline Model (Improved for stability and multi-class)
class Madaline:
    def __init__(self, input_shape, num_classes, learning_rate=LEARNING_RATE, epochs=EPOCHS):
        self.input_shape = input_shape
        self.num_classes = num_classes
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.weights = np.random.normal(0, 0.1, (np.prod(input_shape), num_classes))  # Improved initialization
        self.bias = np.zeros(num_classes)
        self.errors_ = []

    def activation(self, x):
        return np.where(x >= 0, 1, -1) # Bipolar activation

    def softmax(self,x):
        exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))
        return exp_x / np.sum(exp_x, axis=1, keepdims=True)

    def fit(self, X, y):
        X = X.reshape(X.shape[0], -1)  # Flatten input
        for epoch in range(self.epochs):
            errors_epoch = 0
            for i in range(len(X)):
                xi = X[i]
                target = y[i]
                net_input = np.dot(xi, self.weights) + self.bias
                output = self.softmax(net_input.reshape(1,-1))[0]
                error = target - output
                errors_epoch += np.sum(np.abs(error))

                self.weights += self.learning_rate * np.outer(xi, error)
                self.bias += self.learning_rate * error
            self.errors_.append(errors_epoch/len(X))

    def predict(self, X):
        X = X.reshape(X.shape[0], -1)
        net_input = np.dot(X, self.weights) + self.bias
        return self.softmax(net_input)

# Main Script
if __name__ == "__main__":
    if not os.path.exists(CSV_FILE):
        create_csv_from_images(DATASET_DIR, CSV_FILE)
    
    images, labels = load_data(CSV_FILE)
    if images is None or labels is None:
        exit()

    images = preprocess_data(images)
    label_encoder = LabelEncoder()
    labels_encoded = label_encoder.fit_transform(labels)
    num_classes = len(label_encoder.classes_)

    X_train, X_test, y_train, y_test = train_test_split(images, labels_encoded, test_size=0.2, random_state=42)

    # Reshape images for Madaline
    input_shape = X_train[0].shape

    # One-hot encode labels
    y_train_onehot = np.eye(num_classes)[y_train]
    y_test_onehot = np.eye(num_classes)[y_test]

    madaline = Madaline(input_shape=input_shape, num_classes=num_classes)
    madaline.fit(X_train, y_train_onehot)

    y_pred_madaline = madaline.predict(X_test)
    y_pred_classes = np.argmax(y_pred_madaline, axis=1)
    print("Madaline Accuracy:", accuracy_score(y_test, y_pred_classes))
    print(classification_report(y_test, y_pred_classes, target_names=label_encoder.classes_))

    cm = confusion_matrix(y_test, y_pred_classes)
    plt.figure(figsize=(10, 8))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=label_encoder.classes_, yticklabels=label_encoder.classes_)
    plt.xlabel('Predicted Label')
    plt.ylabel('True Label')
    plt.title('Confusion Matrix')
    plt.show()

    # Plot errors
    plt.plot(madaline.errors_)
    plt.title('Madaline Training Errors')
    plt.xlabel('Epochs')
    plt.ylabel('Average Error')
    plt.show()

    def predict_emotion(image_path, model, label_encoder, input_shape=IMG_SIZE):
        try:
            img = Image.open(image_path).convert('L').resize(input_shape)
            img_array = np.asarray(img).flatten() / 255.0
            prediction = model.predict(img_array.reshape(1, -1))
            predicted_class = np.argmax(prediction, axis=1)
            emotion = label_encoder.inverse_transform(predicted_class)
            return emotion[0]
        except Exception as e:
            print(f"Error processing image: {e}")
            return None

    while True:
        test_image_path = input("Enter image path for prediction (or 'exit'): ")
        if test_image_path.lower() == 'exit':
            break
        if not os.path.exists(test_image_path):
            print("File not found.")
            continue
        emotion = predict_emotion(test_image_path, madaline, label_encoder)
        if emotion:
            print(f"Predicted emotion: {emotion}")


