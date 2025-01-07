import pandas as pd
import matplotlib.pyplot as plt

def plot_combined(gate_type, X, y, predictions, model):
    fig, axs = plt.subplots(1, 3, figsize=(18, 6))

    table_data = {
        "Input A": X[:, 0],
        "Input B": X[:, 1],
        "True Output": y,
        "Predicted Output": predictions,
    }
    df = pd.DataFrame(table_data)
    axs[0].axis("tight")
    axs[0].axis("off")
    axs[0].table(cellText=df.values, colLabels=df.columns, loc="center", cellLoc="center")
    axs[0].set_title(f"Truth Table for {gate_type} Gate", fontsize=12, pad=20)

    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.1),
                         np.arange(y_min, y_max, 0.1))
    grid = np.c_[xx.ravel(), yy.ravel()]
    boundary_predictions = model.predict(grid).reshape(xx.shape)

    axs[1].contourf(xx, yy, boundary_predictions, alpha=0.8, cmap=plt.cm.Paired)
    axs[1].scatter(X[:, 0], X[:, 1], c=y, edgecolor="k", cmap=plt.cm.Paired)
    axs[1].set_title(f"Decision Boundary for {gate_type} Gate")
    axs[1].set_xlabel("Input A")
    axs[1].set_ylabel("Input B")

    axs[2].axis("off")
    try:
        img = plt.imread(f"images/{gate_type}.png")
        axs[2].imshow(img)
        axs[2].set_title(f"{gate_type} Gate Image")
    except FileNotFoundError:
        axs[2].text(0.5, 0.5, "Image not found", fontsize=12, ha="center", va="center")
        axs[2].set_title("No Image Available")

    plt.tight_layout()
    plt.show()
