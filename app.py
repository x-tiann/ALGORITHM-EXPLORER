from flask import Flask, render_template_string, request
import subprocess
import os

app = Flask(__name__)

# HTML/CSS/JS Frontend Dashboard embedded directly for a single-file server component
HTML_TEMPLATE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Algorithm Explorer</title>
    <style>
        body { font-family: Arial, sans-serif; background-color: #f4f6f9; margin: 0; padding: 20px; display: flex; justify-content: center; }
        .container { background: #ffffff; padding: 30px; border-radius: 8px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); width: 100%; max-width: 700px; }
        h2 { color: #333; text-align: center; }
        label { font-weight: bold; color: #555; display: block; margin-top: 15px; }
        input[type="text"] { width: 100%; padding: 10px; margin-top: 5px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box; }
        button { background-color: #0056b3; color: white; border: none; padding: 10px 15px; margin-top: 15px; width: 100%; border-radius: 4px; font-size: 16px; cursor: pointer; }
        button:hover { background-color: #004494; }
        .results { margin-top: 20px; background: #eef2f7; padding: 15px; border-radius: 5px; }
        .steps { margin-top: 15px; background: #fffdf0; border: 1px solid #e2d96d; padding: 15px; border-radius: 5px; white-space: pre-wrap; font-family: monospace; max-height: 250px; overflow-y: auto; }
    </style>
</head>
<body>
    <div class="container">
        <h2>Algorithm Explorer (C Back-End)</h2>
        <form method="POST">
            <label for="numbers">Enter numbers (space-separated):</label>
            <input type="text" id="numbers" name="numbers" value="{{ request.form.get('numbers', '38 27 43 3 9 82 10') }}" required>
            <button type="submit">Run Algorithm</button>
        </form>

        {% if result %}
        <div class="results">
            <strong>Sorted Result:</strong> {{ result.sorted_arr }}<br>
            <strong>Total Operations:</strong> {{ result.operations }}<br>
            <strong>Running Time:</strong> {{ result.time_ms }} ms
        </div>

        <h3>Steps Taken:</h3>
        <div class="steps">{{ result.steps }}</div>
        {% endif %}
    </div>
</body>
</html>
"""

@app.route("/", methods=["GET", "POST"])
def index():
    result = None
    if request.method == "POST":
        raw_input = request.form.get("numbers", "")
        # Validate and sanitize numeric inputs
        try:
            tokens = [int(x) for x in raw_input.split()]
        except ValueError:
            return render_template_string(HTML_TEMPLATE, result={"sorted_arr": "Error: Please enter valid integers only.", "operations": 0, "time_ms": 0, "steps": ""})

        if tokens:
            # Path to the compiled C executable
            exe_path = "./algorithm_explorer.exe" if os.name == "nt" else "./algorithm_explorer"
            
            if not os.path.exists(exe_path):
                return render_template_string(HTML_TEMPLATE, result={"sorted_arr": "Error: C binary not found. Please compile main.c, datastructures.c, and sorting.c first.", "operations": 0, "time_ms": 0, "steps": ""})

            # Execute C binary via subprocess passing user inputs as CLI arguments
            cmd = [exe_path] + [str(t) for t in tokens]
            try:
                process = subprocess.run(cmd, capture_output=True, text=True, timeout=5)
                output_lines = process.stdout.strip().split("\n")
                
                ops, time_ms, sorted_arr, steps = "0", "0.0", "", ""
                parsing_steps = False

                for line in output_lines:
                    if line.startswith("OPERATIONS:"):
                        ops = line.split(":")[1]
                    elif line.startswith("TIME_MS:"):
                        time_ms = line.split(":")[1]
                    elif line.startswith("SORTED:"):
                        sorted_arr = line.split(":")[1]
                    elif line.startswith("STEPS:"):
                        parsing_steps = True
                        continue
                    
                    if parsing_steps:
                        steps += line + "\n"

                result = {
                    "sorted_arr": sorted_arr,
                    "operations": ops,
                    "time_ms": time_ms,
                    "steps": steps.strip()
                }
            except Exception as e:
                result = {"sorted_arr": f"Execution Error: {str(e)}", "operations": 0, "time_ms": 0, "steps": ""}

    return render_template_string(HTML_TEMPLATE, result=result)

if __name__ == "__main__":
    app.run(debug=True, port=5000)