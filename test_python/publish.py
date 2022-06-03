from distutils.command.clean import clean
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

def on_log(client, userdata, level, buf):
    print(f"log - {buf}")

# client = mqtt.Client(client_id="12847720", clean_session=False)
client = mqtt.Client(client_id="756888235", clean_session=True)
client.on_connect = on_connect
# client.on_log = on_log
# client.enable_logger()

client.connect("mqtt.eclipseprojects.io", 1883, 60)
client.loop_start()

# from time import sleep
# sleep(2)
# lock = 0;
# front_led = 0;
# while True:
#     lock += 1
#     lock %= 3

#     msg = 0b00111000 | (front_led << 2) | (lock)
#     client.publish("scooter/112", f"\r\n$@{chr(msg)}\r\n", qos=0)
#     print(f"Publish {chr(msg)} | {bin(msg)} | lock:{lock}, front_led:{front_led}")

#     sleep(5)

lock = 0;
front_led = 0;
def send_to_scooter():
    msg = 0b00111000 | (front_led << 2) | (lock)
    client.publish("scooter/112", f"\r\n$@{chr(msg)}\r\n", qos=0)
    print(f"Publish {chr(msg)} | {bin(msg)} | lock:{lock}, front_led:{front_led}")

while True:
    x = input("Input: ")
    if x == 'L':
        lock = (lock + 1) % 3
    elif x == 'F':
        front_led = (front_led + 1) % 2
    
    send_to_scooter()