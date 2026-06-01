import serial, time

ser = serial.Serial(port='COM12', baudrate=115200, timeout=1)

# Test "Namaste"
ser.write(b'Namaste\r\n')
time.sleep(1)
print("Response to Namaste:", ser.readline().decode().strip())

time.sleep(1)

# Test "Kaise Ho Aap"
ser.write(b'KaiseHoAap')
time.sleep(1)
print("Response to Kaise Ho Aap:", ser.readline().decode().strip())

ser.close()
