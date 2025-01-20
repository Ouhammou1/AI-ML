import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import cv2
import random
from ipywidgets import Button, Output, VBox
from IPython.display import display, clear_output

# ----------------------------
# Adaline Class
# ----------------------------

class Adaline:
    def __init__(self, learning_rate=0.00001, n_iterations=485):
        self.learning_rate = learning_rate
        self.n_iterations = n_iterations
        self.errors_ = []  # Track the Mean Squared Error (MSE) for each epoch

    def fit(self, X, y):
        # Initialize weights with small random values
        self.weights = np.random.normal(0, 0.01, size=(1 + X.shape[1]))
        for epoch in range(self.n_iterations):
            # Calculate net input
            net_input = self.net_input(X)

            # Activation function (identity for Adaline)
            output = self.activation(net_input)

            # Calculate errors
            errors = y - output

            # Update weights
            self.weights[1:] += self.learning_rate * X.T.dot(errors)  # Feature weights
            self.weights[0] += self.learning_rate * errors.sum()      # Bias term

            # Calculate Mean Squared Error (MSE)
            mse = np.mean(errors**2)
            self.errors_.append(mse)  # Store the MSE for this epoch

            # Early stopping if MSE is very small
            if mse < self.learning_rate:  # Adjust this threshold as needed
                print(f"Early stopping at epoch {epoch + 1}")
                break;

            # Log the progress
            print(f"Epoch {epoch + 1}: Mean Error = {mse:.5f}, Weights Mean = {np.mean(self.weights):.5f}")

        return self

    def net_input(self, X):
        # Calculate the linear combination of weights and inputs
        return np.dot(X, self.weights[1:]) + self.weights[0]

    def activation(self, X):
        # Linear activation function (identity function for Adaline)
        return X

    def predict(self, X):
        # Make binary predictions based on a threshold
        return np.where(self.activation(self.net_input(X)) >= 0.5, 1, 0)

# ----------------------------
# Madaline Class
# ----------------------------
class Madaline:
    def __init__(self, n_adalines=3, learning_rate=0.00001, n_iterations=485):
        self.n_adalines = n_adalines
        self.adalines = [Adaline(learning_rate, n_iterations) for _ in range(n_adalines)]

    def fit(self, X, y):
        feature_split = np.array_split(X, self.n_adalines, axis=1)
        for i, adaline in enumerate(self.adalines):
            adaline.fit(feature_split[i], y)
        return self

    def predict(self, X):
        feature_split = np.array_split(X, self.n_adalines, axis=1)
        predictions = np.array([adaline.predict(split) for adaline, split in zip(self.adalines, feature_split)])
        return np.where(predictions.mean(axis=0) >= 0.5, 1, 0)

# ----------------------------
# Shape Generation
# ----------------------------
def generate_shape(shape_type, image_size=64, noise_level=0.1):
    """Generate a simple shape image with noise."""
    image = np.zeros((image_size, image_size), dtype=np.uint8)
    center = (image_size // 2, image_size // 2)
    size = int(image_size * 0.3)

    if shape_type == 'circle':
        cv2.circle(image, center, size, 255, -1)
    elif shape_type == 'square':
        top_left = (center[0] - size, center[1] - size)
        bottom_right = (center[0] + size, center[1] + size)
        cv2.rectangle(image, top_left, bottom_right, 255, -1)
    elif shape_type == 'triangle':
        points = np.array([
            [center[0], center[1] - size],
            [center[0] - size, center[1] + size],
            [center[0] + size, center[1] + size]
        ], np.int32)
        cv2.fillPoly(image, [points], 255)
    elif shape_type == 'pentagon':
        points = np.array([
            [center[0], center[1] - size],
            [center[0] - size, center[1] - size // 2],
            [center[0] - size // 2, center[1] + size],
            [center[0] + size // 2, center[1] + size],
            [center[0] + size, center[1] - size // 2]
        ], np.int32)
        cv2.fillPoly(image, [points], 255)
    elif shape_type == 'hexagon':
        points = np.array([
            [center[0] - size, center[1]],
            [center[0] - size // 2, center[1] - size],
            [center[0] + size // 2, center[1] - size],
            [center[0] + size, center[1]],
            [center[0] + size // 2, center[1] + size],
            [center[0] - size // 2, center[1] + size]
        ], np.int32)
        cv2.fillPoly(image, [points], 255)

    noise = np.random.normal(0, noise_level, image.shape)
    noisy_image = image + noise * 255
    return np.clip(noisy_image, 0, 255).astype(np.uint8)

def create_dataset(n_samples=485):
    """Create a dataset of shapes."""
    X = []
    y = []
    shapes = ['circle', 'square', 'triangle', 'pentagon', 'hexagon']
    for _ in range(n_samples):
        shape = random.choice(shapes)
        image = generate_shape(shape)
        X.append(image.flatten())
        y.append([1 if shape == s else 0 for s in shapes])
    return np.array(X), np.array(y)

# ----------------------------
# Helper Functions
# ----------------------------

def predict_shape(image, models):
    """Predict the shape using improved feature extraction."""
    processed_image, circularity = preprocess_image(image)
    image_scaled = scaler.transform([processed_image.flatten()])

    predictions = {}
    for shape, model in models.items():
        adaline_pred = float(model['adaline'].predict(image_scaled)[0])
        madaline_pred = float(model['madaline'].predict(image_scaled)[0])
        base_prob = (adaline_pred + madaline_pred) / 2

        # Adjust probabilities based on circularity
        if shape == 'circle' and circularity > 0.9:
            base_prob = max(base_prob, 0.9)
        elif shape == 'square' and circularity > 0.9:
            base_prob *= 0.1

        predictions[shape] = base_prob

    # Normalize probabilities
    total = sum(predictions.values())
    if total > 0:
        predictions = {k: v/total for k, v in predictions.items()}

    return max(predictions.items(), key=lambda x: x[1])[0]

def calculate_accuracy():
    """Calculate the accuracy of the models."""
    correct = 0
    total = len(X_test)
    for i in range(total):
        actual_shape = shapes[np.argmax(y_test[i])]
        predicted_shape = predict_shape(X_test[i].reshape(64, 64), shape_models)
        if actual_shape == predicted_shape:
            correct += 1
    return correct / total
from ipywidgets import FileUpload
from PIL import Image
import io

# Widget for uploading an image
upload = FileUpload(accept='image/*', multiple=False)
est_image_scaled = scaler.transform([processed_image.flatten()])


def enhance_image_preprocessing(image_array):
    """
    Enhanced image preprocessing with better feature extraction
    """
    # Ensure proper image scaling
    image_array = cv2.normalize(image_array, None, 0, 255, cv2.NORM_MINMAX)
    
    # Apply Gaussian blur to reduce noise
    blurred = cv2.GaussianBlur(image_array, (5, 5), 0)
    
    # Use adaptive thresholding for better binarization
    binary = cv2.adaptiveThreshold(
        blurred,
        255,
        cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
        cv2.THRESH_BINARY_INV,
        11,
        2
    )
    
    # Clean up the binary image
    kernel = np.ones((3,3), np.uint8)
    binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)
    binary = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel)
    
    # Find contours
    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    if not contours:
        return image_array, {
            'circularity': 0,
            'corners': 0,
            'aspect_ratio': 1,
            'convexity': 0
        }
    
    # Get the largest contour
    largest_contour = max(contours, key=cv2.contourArea)
    
    # Calculate shape features
    area = cv2.contourArea(largest_contour)
    perimeter = cv2.arcLength(largest_contour, True)
    hull = cv2.convexHull(largest_contour)
    hull_area = cv2.contourArea(hull)
    
    # Calculate shape metrics
    circularity = 4 * np.pi * area / (perimeter * perimeter) if perimeter > 0 else 0
    convexity = area / hull_area if hull_area > 0 else 0
    
    # Approximate the contour to count corners
    epsilon = 0.04 * perimeter
    approx = cv2.approxPolyDP(largest_contour, epsilon, True)
    corners = len(approx)
    
    # Calculate aspect ratio
    x, y, w, h = cv2.boundingRect(largest_contour)
    aspect_ratio = float(w)/h if h > 0 else 1
    
    # Create feature image
    feature_image = np.zeros_like(binary)
    cv2.drawContours(feature_image, [largest_contour], -1, 255, -1)
    
    features = {
        'circularity': circularity,
        'corners': corners,
        'aspect_ratio': aspect_ratio,
        'convexity': convexity
    }
    
    return feature_image, features

def improved_predict_shape(image, models):
    """
    Improved shape prediction using multiple features
    """
    processed_image, features = enhance_image_preprocessing(image)
    image_scaled = scaler.transform([processed_image.flatten()])
    
    predictions = {}
    for shape, model in models.items():
        # Get base predictions from both models
        adaline_pred = float(model['adaline'].predict(image_scaled)[0])
        madaline_pred = float(model['madaline'].predict(image_scaled)[0])
        base_prob = (adaline_pred + madaline_pred) / 2
        
        # Apply feature-based adjustments
        if shape == 'circle':
            if features['circularity'] > 0.9 and features['corners'] <= 8:
                base_prob *= 1.5
            elif features['circularity'] < 0.5:
                base_prob *= 0.5
                
        elif shape == 'square':
            if features['corners'] == 4 and 0.95 <= features['aspect_ratio'] <= 1.05:
                base_prob *= 1.5
            elif features['corners'] != 4:
                base_prob *= 0.5
                
        elif shape == 'triangle':
            if features['corners'] == 3:
                base_prob *= 1.5
            elif features['corners'] > 4:
                base_prob *= 0.3
                
        elif shape == 'pentagon':
            if features['corners'] == 5:
                base_prob *= 1.5
            elif features['corners'] < 4 or features['corners'] > 6:
                base_prob *= 0.3
                
        elif shape == 'hexagon':
            if features['corners'] == 6:
                base_prob *= 1.5
            elif features['corners'] < 5 or features['corners'] > 7:
                base_prob *= 0.3
        
        predictions[shape] = max(0, min(1, base_prob))  # Clamp between 0 and 1
    
    # Normalize probabilities
    total = sum(predictions.values())
    if total > 0:
        predictions = {k: v/total for k, v in predictions.items()}
    
    return predictions

def improved_image_upload_handler(change):
    with output:
        clear_output(wait=True)
        if upload.value:
            uploaded_file = list(upload.value.values())[0]
            content = uploaded_file['content']
            
            # Open and convert to grayscale
            image = Image.open(io.BytesIO(content)).convert('L')
            original_size = image.size
            
            # Resize and convert to numpy array
            resized_image = image.resize((64, 64))
            test_image = np.array(resized_image)
            
            # Get predictions with improved method
            shape_probabilities = improved_predict_shape(test_image, shape_models)
            
            # Process image for display
            processed_image, features = enhance_image_preprocessing(test_image)
            
            # Get predicted shape and confidence
            predicted_shape = max(shape_probabilities.items(), key=lambda x: x[1])[0]
            confidence = shape_probabilities[predicted_shape] * 100
            
            # Display results
            plt.figure(figsize=(15, 5))
            
            # Original image
            plt.subplot(1, 3, 1)
            plt.imshow(np.array(image), cmap='gray')
            plt.title(f"Original Image\nSize: {original_size}")
            plt.axis('off')
            
            # Processed image
            plt.subplot(1, 3, 2)
            plt.imshow(processed_image, cmap='gray')
            plt.title("Processed Image")
            plt.axis('off')
            
            # Feature visualization
            plt.subplot(1, 3, 3)
            plt.axis('off')
            plt.title("Shape Analysis")
            
            # Display shape probabilities and features
            info_text = f"Predicted: {predicted_shape.capitalize()}\n"
            info_text += f"Confidence: {confidence:.2f}%\n\n"
            info_text += "Shape Probabilities:\n"
            for shape, prob in shape_probabilities.items():
                info_text += f"{shape.capitalize()}: {prob*100:.1f}%\n"
            info_text += "\nShape Features:\n"
            for feature, value in features.items():
                info_text += f"{feature}: {value:.2f}\n"
            
            plt.text(0.1, 0.9, info_text, transform=plt.gca().transAxes, 
                    verticalalignment='top', fontfamily='monospace')
            
            plt.tight_layout()
            plt.show()
# ----------------------------
# Main Program
# ----------------------------
print("Initializing Shape Recognition System...")
X, y = create_dataset(485)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

shapes = ['circle', 'square', 'triangle', 'pentagon', 'hexagon']
shape_models = {}

for i, shape in enumerate(shapes):
    print(f"Training models for {shape}...")
    adaline = Adaline(learning_rate=0.00001, n_iterations=485)
    adaline.fit(X_train_scaled, y_train[:, i])
    madaline = Madaline(n_adalines=3, learning_rate=0.00001, n_iterations=485)
    madaline.fit(X_train_scaled, y_train[:, i])
    shape_models[shape] = {'adaline': adaline, 'madaline': madaline}

accuracy = calculate_accuracy()
print(f"\nModel Accuracy: {accuracy:.2%}")

# ----------------------------
# Interactive Buttons for Colab
# ----------------------------
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

# Upload and output widgets
upload = FileUpload(accept='image/*', multiple=False)
upload.observe(on_image_upload, names='value')

display(VBox([button1, button2, upload, button3]), output)

