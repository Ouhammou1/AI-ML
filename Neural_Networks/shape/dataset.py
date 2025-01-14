import numpy as np
import cv2
import random

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

def create_dataset(n_samples=500):
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
