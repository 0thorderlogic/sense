import serial
import time

def send_file_to_arduino(serial_port, baud_rate, filename):
    try:
        ser = serial.Serial(serial_port, baud_rate, timeout=1)
        time.sleep(2)  # Let Arduino reset
    except Exception as e:
        print(f"Error opening serial port: {e}")
        return

    try:
        with open(filename, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                ser.write((line + '\n').encode())
                print(f"Sent: {line}")
                time.sleep(1)  # Delay to let Arduino display Braille
    except Exception as e:
        print(f"Error: {e}")
    finally:
        ser.close()

if __name__ == "__main__":
    port = input("Enter COM port (e.g., COM3): ")
    send_file_to_arduino(port, 9600, "scraped_text.txt")