from pymodbus.client import ModbusSerialClient
import time

# Zero calibration for wind speed
ZERO_CURRENT = 5.17

client = ModbusSerialClient(
    port="COM6",
    baudrate=9600,
    parity="N",
    stopbits=1,
    bytesize=8,
    timeout=1
)

if not client.connect():
    print("Connection Failed")
    exit()

print("Wind Monitoring Started\n")

while True:

    try:
        # Wind Speed (A1 -> 4000)
        speed_result = client.read_input_registers(
            address=4000,
            count=1,
            device_id=1
        )

        # Wind Direction (A2 -> 4001)
        direction_result = client.read_input_registers(
            address=4001,
            count=1,
            device_id=1
        )

        if (not speed_result.isError()) and (not direction_result.isError()):

            # -------- WIND SPEED --------
            speed_raw = speed_result.registers[0]
            current_mA = speed_raw / 100.0

            wind_speed = (
                (current_mA - ZERO_CURRENT)
                / (20.0 - ZERO_CURRENT)
            ) * 250.0

            wind_speed = max(0, wind_speed)

            # -------- WIND DIRECTION --------
            direction_raw = direction_result.registers[0]

            # Assuming module scales 0-5V as 0-500
            voltage = direction_raw / 100.0

            wind_direction = (voltage / 5.0) * 360.0

            # Clamp to valid range
            wind_direction = max(0, min(360, wind_direction))

            print(
                f"Speed: {wind_speed:6.2f} km/h | "
                f"Direction: {wind_direction:6.1f}° | "
                f"RawDir: {direction_raw}"
            )

        time.sleep(1)

    except KeyboardInterrupt:
        print("\nStopped")
        break

    except Exception as e:
        print("Error:", e)

client.close()