#!/usr/bin/python3
import paho.mqtt.client as mqtt
import datetime
import time
import math
import json


mqttBroker = 'eu1.cloud.thethings.network'
mqttBrokerPort = 1883
mqttUser = 'pth-test-001@ttn'
mqttPW = 'NNSXS.5SLTYNUSBRRGXZMLRAQYWKHUAWJX5XJYMXGPMNQ.PSQQWJIX32IEC4SUKEOSZBMFGBMLMYS4ZIG4RJVEDWD3SAK3XRLA'
#subscribe = 'pth-test-001@ttn/#'
subscribe = '#'

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(subscribe)
    
def on_message(client, userdata, msg):
    #print("Received a message on topic: " + msg.topic)
    # Use utc as timestamp
    receiveTime = datetime.datetime.utcnow()
    message = msg.payload.decode("utf-8")
    
    print(msg.topic, message)
    
    messageData = json.loads(message)
    timeStamp = messageData['timestamp']
    if math.isnan(float(messageData['val'])):
        val = float(NaN)
    else:
        val = float(messageData['val'])


    print('%55s: %5.3f' %(msg.topic, val))

    #if msg.topic == 'emergencyHeating/tankSensors/heatingStorageTankOhm':
        #heatingStorageTankOhm = val
    
    #elif msg.topic == 'emergencyHeating/tankSensors/boilerOhm':
        #boilerOhm = val

        
    
            
    

# Initialize the MQTT client that should connect to the Mosquitto broker
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set(mqttUser, mqttPW)
connOK=False
while(connOK == False):
    try:
        client.connect(mqttBroker, mqttBrokerPort, 60)
        connOK = True
    except:
        connOK = False
    time.sleep(2)


# Blocking loop to the mqtt broker
print('read from broker...')
client.loop_forever()



