import subprocess
import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext

def select_file():
    path = filedialog.askopenfilename(
        title="Select shellcode bin",
        filetypes=[("Binary files", "*.bin"), ("All files", "*.*")]
    )
    file_entry.delete(0, tk.END)
    file_entry.insert(0, path)

def analyze():
    path = file_entry.get()
    if not path:
        messagebox.showerror("Error", "No file selected")
        return

    try:
        result = subprocess.run(
            ["./sc_analyzer", path],
            capture_output=True,
            text=True
        )
        output_box.delete("1.0", tk.END)
        output_box.insert(tk.END, result.stdout)
    except Exception as e:
        messagebox.showerror("Error", str(e))

def export_output():
    data = output_box.get("1.0", tk.END)
    if not data.strip():
        return

    path = filedialog.asksaveasfilename(
        defaultextension=".txt",
        filetypes=[("Text file", "*.txt")]
    )
    if path:
        with open(path, "w") as f:
            f.write(data)

def copy_output():
    root.clipboard_clear()
    root.clipboard_append(output_box.get("1.0", tk.END))

# GUI
root = tk.Tk()
root.title("Shellcode Analyzer v1")

tk.Label(root, text="Shellcode file:").pack(pady=2)

file_entry = tk.Entry(root, width=60)
file_entry.pack(padx=10)

tk.Button(root, text="Browse", command=select_file).pack(pady=4)
tk.Button(root, text="Analyze", command=analyze).pack(pady=4)

output_box = scrolledtext.ScrolledText(root, width=90, height=25)
output_box.pack(padx=10, pady=10)

btn_frame = tk.Frame(root)
btn_frame.pack()

tk.Button(btn_frame, text="Copy", command=copy_output).pack(side=tk.LEFT, padx=5)
tk.Button(btn_frame, text="Export", command=export_output).pack(side=tk.LEFT, padx=5)

root.mainloop()
