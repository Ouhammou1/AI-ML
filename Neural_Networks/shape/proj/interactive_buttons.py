from ipywidgets import Button, Output, VBox
from IPython.display import display, clear_output

def setup_buttons(generate_shape_and_test, view_accuracy_and_plot):
    output = Output()

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

    display(VBox([button1, button2, button3]), output)
