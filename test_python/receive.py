from pydoc import cli
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("scooter/112", qos=1)

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

def on_log(client, userdata, level, buf):
    print(f"log - {buf}")

client = mqtt.Client(client_id="2347023", clean_session=True)
client.on_connect = on_connect
client.on_message = on_message
# client.on_log  = on_log
# client.enable_logger()

client.connect("mqtt.eclipseprojects.io", 1883, 60)
client.loop_forever()