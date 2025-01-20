import numpy as np
import cv2
import random

def generate_shape(shape_type, image_size=64, noise_level=0.1):
    image = np.zeros((image_size, image_size), dtype=np.uint8)
    center = (image_size // 2, image_size // 2)
    size = int(image_size * 0.3)
    # (Include all shape cases here as in the original code)
    noise = np.random.normal(0, noise_level, image.shape)
    return np.clip(image + noise * 255, 0, 255).astype(np.uint8)

def create_dataset(n_samples=485):
    X, y = [], []
    shapes = ['circle', 'square', 'triangle', 'pentagon', 'hexagon']
    for _ in range(n_samples):
        shape = random.choice(shapes)
        image = generate_shape(shape)
        X.append(image.flatten())
        y.append([1 if shape == s else 0 for s in shapes])
    return np.array(X), np.array(y)
