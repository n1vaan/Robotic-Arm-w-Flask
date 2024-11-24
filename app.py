from flask import Flask, jsonify, render_template, request
import serial
import json


app = Flask(__name__)

arduino = serial.Serial('/dev/cu.usbmodem101', 9600, timeout=1)

@app.route('/')
def render():
    return render_template('main.html')

@app.route('/processinputs')
def processinputs():
    motors = json.loads(request.args.get('motors'))
    print(motors, flush=True)
    json_data = json.dumps(motors)
    print(f"Sending JSON to Arduino: {json_data}")  # Log the JSON being sent
    arduino.write(f"{json_data}\n".encode())
    arduino_response = arduino.readline().decode('utf-8').strip()
    print(f"Arduino response: {arduino_response}")  # Log the response from Arduino
    return jsonify({"status": "success"}) 

    

if __name__ == '__main__':
    app.run()