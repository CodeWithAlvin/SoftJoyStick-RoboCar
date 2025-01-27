# Joystick Car Control Interface

A web-based interface for controlling a robotic car using a virtual joystick. The system consists of a Flask backend that communicates with an ESP8266 microcontroller to control the car's movements.

## Features

- Virtual joystick interface with touch and mouse support
- Real-time PWM control for precise motor speed adjustment
- Adjustable PWM scaling factor (0-100%)
- Responsive web design that works on both desktop and mobile devices
- Directional control (Forward, Backward, Left, Right, and Stop)
- Independent left and right motor speed control for smooth turning
- Debounced commands to prevent control flooding

## System Requirements

- Python 3.x
- Flask
- Requests library
- ESP8266 microcontroller
- Web browser with JavaScript enabled

## Installation

1. Clone this repository:
```bash
git clone [repository-url]
cd [repository-name]
```

2. Install the required Python packages:
```bash
pip install flask requests
```

3. Configure the ESP8266 IP address:
   - Open `app.py`
   - Modify the `ESP8266_IP` variable to match your ESP8266's IP address:
     ```python
     ESP8266_IP = "http://192.168.137.100"  # Replace with your ESP8266's IP address
     ```

## Usage

1. Start the Flask server:
```bash
python app.py
```

2. Open a web browser and navigate to:
```
http://localhost:5000
```

3. Control the car using:
   - Mouse: Click and drag the joystick
   - Touch: Tap and drag on touch-enabled devices
   - The PWM scaling slider to adjust maximum speed

## Control Interface

- **Joystick**: The main control interface shown as a blue dot in a circular boundary
- **PWM Scaling**: Slider to adjust the maximum power output (0-100%)
- **Direction Display**: Shows current direction and PWM values for both motors

## API Endpoints

### `/move`
- Method: GET
- Parameters:
  - `direction`: Movement direction ('W', 'A', 'S', 'D', 'STOP')
  - `dutyA`: PWM duty cycle for left motor (0-255)
  - `dutyB`: PWM duty cycle for right motor (0-255)
- Example: `/move?direction=W&dutyA=200&dutyB=200`

## Technical Details

### PWM Control
- PWM range: 0-255 (8-bit resolution)
- Default PWM: 128 (50% duty cycle)
- Scaling factor applies to both motors
- Independent motor control for turning maneuvers

### Direction Control
- W: Forward
- S: Backward
- A: Left
- D: Right
- STOP: No movement

## Browser Compatibility

- Chrome (recommended)
- Firefox
- Safari
- Edge
- Mobile browsers with touch support

## Contributing

Feel free to submit issues, fork the repository, and create pull requests for any improvements.

## License

[Your chosen license]

## Acknowledgments

- Built with Flask and vanilla JavaScript
- Uses HTML5 Canvas for joystick interface