from ultralytics import YOLO
import cvzone
import cv2
import math
from pyfirmata import Arduino, util
import time
import pygame

url = 'http://192.168.0.100:81/stream'

# Connect to Arduino
board = Arduino('COM11')  
pygame.init()
alarm_sound = pygame.mixer.Sound('firealert.mp3') 
# Initialize iterator
it = util.Iterator(board)
it.start()

# Define the pin connections to aurdino
buzz_pin = 9  
relay_pin = 10
nodemcu_pin= 8

# Initialize pin as output
board.digital[buzz_pin].mode = 1
board.digital[relay_pin].mode = 1
board.digital[nodemcu_pin].mode = 1
# Running real-time from webcam
cap = cv2.VideoCapture(url)
model = YOLO('best1.pt')

# Reading the classes
classnames = ['fire']

# Flag to track if the alarm is already triggered
alarm_triggered = False

# Time duration (in seconds) for the alarm cooldown period
cooldown_duration = 60  # Change this to set the cooldown duration

# Initialize the timestamp for cooldown tracking
cooldown_start_time = 0

while True:
    ret, frame = cap.read()
    cv2.imshow('IP Camera', frame)
    result = model(frame, stream=True)

    # Getting bbox, confidence, and class names information to work with
    for info in result:
        boxes = info.boxes
        for box in boxes:
            confidence = box.conf[0]
            confidence = math.ceil(confidence * 100)
            Class = int(box.cls[0])
            if confidence > 50:
                x1, y1, x2, y2 = box.xyxy[0]
                x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 255), 5)
                cvzone.putTextRect(frame, f'{classnames[Class]} {confidence}%', [x1 + 8, y1 + 100],
                                   scale=1.5, thickness=2)
                
                # Activate buzzer and pump when fire is detected
                if not alarm_triggered:
                    alarm_sound.play()
                    board.digital[buzz_pin].write(1)  # Turn buzzer on
                    board.digital[relay_pin].write(1)  # Turn pump on
                    board.digital[nodemcu_pin].write(1)
                    alarm_triggered = True
                    cooldown_start_time = time.time()
                    time.sleep(4)
                    board.digital[buzz_pin].write(0)   # Turn buzzer off
                    board.digital[relay_pin].write(0)  # Turn pump off
                    board.digital[nodemcu_pin].write(0)
                    
    
    if alarm_triggered and time.time() - cooldown_start_time > cooldown_duration:
        alarm_triggered = False
    cv2.imshow('frame', frame)
    cv2.waitKey(1)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
