import tkinter as tk
from tkinter import ttk

class DivideComboPopUp:
    def __init__(self, combination_obj):
        self.combination_obj = combination_obj

        self.buy_legs = self.combination_obj.buy_legs
        self.sell_legs = self.combination_obj.sell_legs
        self.all_legs = self.buy_legs + self.sell_legs

        self.sub_combos = []  # Store multiple sub-combos
        self.popup = None

    def create_pop_up(self):
        self.popup = tk.Toplevel()
        self.popup.title("Divide Combination into Sub-Combos")
        self.popup.geometry("700x400")

        frame = ttk.Frame(self.popup, padding=10)
        frame.pack(fill="both", expand=True)

        # Create table for displaying all legs
        ttk.Label(frame, text="Available Legs").grid(row=0, column=0, padx=10, pady=10, sticky="w")
        self.legs_listbox = tk.Listbox(frame, selectmode=tk.MULTIPLE, height=15 , width= 30)
        self.legs_listbox.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")

        # Populate legs table with alternating row colors
        for idx, leg in enumerate(self.all_legs):
            display_string = self.format_leg_display_string(leg)
            self.legs_listbox.insert(tk.END, display_string)
            if idx % 2 == 0:
                self.legs_listbox.itemconfig(idx, bg="lightblue")
            else:
                self.legs_listbox.itemconfig(idx, bg="white")

        # Create table for selected sub-combo legs
        ttk.Label(frame, text="Sub-Combo Creator").grid(row=0, column=1, padx=10, pady=10, sticky="w")
        self.subcombo_table = tk.Listbox(frame, height=15 , width= 70)
        self.subcombo_table.grid(row=1, column=1, padx=10, pady=10, sticky="nsew")

        # Add sub-combo button
        add_subcombo_button = ttk.Button(frame, text="Add Sub-Combo", command=self.add_subcombo)
        add_subcombo_button.grid(row=2, column=0, padx=10, pady=10, sticky="ew")

        # Remove sub-combo button
        remove_subcombo_button = ttk.Button(frame, text="Remove Sub-Combo", command=self.remove_subcombo)
        remove_subcombo_button.grid(row=2, column=1, padx=10, pady=10, sticky="ew")

        # Save button
        self.save_button = ttk.Button(frame, text="Save Sub-Combos", command=self.save_subcombos, state="disabled")
        self.save_button.grid(row=3, column=0, columnspan=2, padx=10, pady=10, sticky="ew")

    def format_leg_display_string(self, leg):
        """Create a string to display action, symbol, quantity, and sec_type for the leg."""
        return f"{leg.action} {leg.symbol} ({leg.sec_type}) Qty: {leg.quantity}"

    def add_subcombo(self):
        selected_indices = self.legs_listbox.curselection()
        if selected_indices:
            # Add the selected legs as a sub-combo to the right table
            selected_legs = [self.all_legs[idx] for idx in selected_indices]
            sub_combo_strs = [self.format_leg_display_string(leg) for leg in selected_legs]
            sub_combo_str = ", ".join(sub_combo_strs)

            self.subcombo_table.insert(tk.END, sub_combo_str)
            self.sub_combos.append(selected_legs)

            # Remove selected legs from left table
            for idx in selected_indices[::-1]:
                self.legs_listbox.delete(idx)

            # Reapply alternating row colors in both tables
            self.update_listbox_colors(self.legs_listbox)
            self.update_listbox_colors(self.subcombo_table)

        # Enable save button if left table is empty
        if self.legs_listbox.size() == 0:
            self.save_button.config(state="normal")

    def remove_subcombo(self):
        selected_index = self.subcombo_table.curselection()
        if selected_index:
            # Remove the selected sub-combo from the subcombo table
            sub_combo_str = self.subcombo_table.get(selected_index)
            self.subcombo_table.delete(selected_index)

            # Add the legs back to the left table
            removed_combo = self.sub_combos.pop(selected_index[0])
            for leg in removed_combo:
                self.legs_listbox.insert(tk.END, self.format_leg_display_string(leg))

            # Reapply alternating row colors
            self.update_listbox_colors(self.legs_listbox)
            self.update_listbox_colors(self.subcombo_table)

        # Disable save button if left table is not empty
        if self.legs_listbox.size() > 0:
            self.save_button.config(state="disabled")

    def save_subcombos(self):
        # Call the create combination function for each sub-combo
        for combo in self.sub_combos:
            self.create_combination(combo)

        # Destroy the pop-up after saving
        self.popup.destroy()

    def update_listbox_colors(self, listbox):
        for idx in range(listbox.size()):
            if idx % 2 == 0:
                listbox.itemconfig(idx, bg="lightblue")
            else:
                listbox.itemconfig(idx, bg="white")

    def create_combination(self, combo):
        # Simulate combination creation logic (replace with your actual logic)
        print(f"Creating combination: {[leg.symbol for leg in combo]}")

# Example usage
if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()  # Hide the root window

    # Example Leg object definition
    class Leg:
        def __init__(self, action, symbol, sec_type, quantity, con_id):
            self.action = action
            self.symbol = symbol
            self.sec_type = sec_type
            self.quantity = quantity
            self.con_id = con_id

    # Example combination object
    class Combination:
        def __init__(self, buy_legs, sell_legs):
            self.buy_legs = buy_legs
            self.sell_legs = sell_legs

    # Example legs
    leg1 = Leg("BUY", "AAPL", "STK", 100, 1)
    leg2 = Leg("SELL", "AAPL", "OPT", 50, 2)
    leg3 = Leg("BUY", "GOOGL", "FUT", 10, 3)
    leg4 = Leg("SELL", "TSLA", "STK", 20, 4)

    # Example combination
    combination_obj = Combination(buy_legs=[leg1, leg3], sell_legs=[leg2, leg4])

    app = DivideComboPopUp(combination_obj)
    app.create_pop_up()
    root.mainloop()
