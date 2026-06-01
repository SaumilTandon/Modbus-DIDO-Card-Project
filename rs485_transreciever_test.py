import serial
import time

# Open COM14 at 115200 baud
ser = serial.Serial('COM14', baudrate=115200, timeout=1)

print("Connected to", ser.port)

try:
    while True:
        # ---- Receive ----
        data = ser.readline()
        if data:
            print("Received:", data.decode(errors='ignore').strip())

        # ---- Optional: Send a test message every 5 seconds ----
        # (you can comment this block out if you only want to receive)
        msg = "Ping from Python\r\n"
        ser.write(msg.encode())
        time.sleep(5)

except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()
