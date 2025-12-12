import serial
import time
import json
import pyaudio
from vosk import Model, KaldiRecognizer

# ---------------- Serial Setup ----------------
ser = serial.Serial('COM4', 115200, timeout=1)  # Pico is on COM4

# ---------------- Vosk Model ----------------
model = Model("vosk-model-small-en-us-0.15")
rec = KaldiRecognizer(model, 16000)

# Voice commands mapped to Pico letters
COMMANDS = {
    "go robot": "G",      # activation
    "forward": "W",       # move forward
    "go forward": "W",
    "left": "A",          # turn left
    "right": "D",         # turn right
    "stop": "S"           # stop
}

# ---------------- Audio Setup ----------------
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16, channels=1, rate=16000,
                input=True, frames_per_buffer=8000)
stream.start_stream()

print("Listening for commands...")

# ---------------- Main loop ----------------
while True:
    data = stream.read(4000, exception_on_overflow=False)
    if rec.AcceptWaveform(data):
        result = json.loads(rec.Result())
        text = result.get("text", "").lower()
        if text:
            print("You said:", text)
            for phrase, cmd in COMMANDS.items():
                if phrase in text:
                    print(">>> Sending command:", cmd)
                    ser.write(cmd.encode())  # send to Pico
                    time.sleep(0.1)  # small delay