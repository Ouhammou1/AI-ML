import numpy as np

def predict_shape(image, models, scaler):
    image_scaled = scaler.transform([image.flatten()])
    predictions = {}
    for shape, model in models.items():
        adaline_pred = model['adaline'].predict(image_scaled)[0]
        madaline_pred = model['madaline'].predict(image_scaled)[0]
        predictions[shape] = (adaline_pred + madaline_pred) / 2
    return max(predictions.items(), key=lambda x: x[1])[0]

def calculate_accuracy(X_test, y_test, shapes, shape_models, scaler):
    correct = 0
    total = len(X_test)
    for i in range(total):
        actual_shape = shapes[np.argmax(y_test[i])]
        predicted_shape = predict_shape(X_test[i].reshape(64, 64), shape_models, scaler)
        if actual_shape == predicted_shape:
            correct += 1
    return correct / total
