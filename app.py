import requests
from flask import Flask, render_template, request

app = Flask(__name__)

ESP8266_IP = "http://192.168.137.100"  # Replace with your ESP8266's IP address

@app.route('/')
def index():
    return render_template('index.html')  # Web interface for controlling the car

@app.route('/move', methods=['GET'])
def move():
    direction = request.args.get('direction')  # e.g., 'W', 'A', 'S', 'D', or 'STOP'
    dutyA = request.args.get('dutyA', default=128, type=int)  # Default to 128 (50% duty cycle)
    dutyB = request.args.get('dutyB', default=128, type=int)  # Default to 128 (50% duty cycle)

    # Send HTTP request to ESP8266
    try:
        url = f"{ESP8266_IP}/{direction}?dutyA={dutyA}&dutyB={dutyB}"
        response = requests.get(url)
        return f"ESP8266 Response: {response.text}"
    except requests.RequestException as e:
        return f"Error communicating with ESP8266: {e}", 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
