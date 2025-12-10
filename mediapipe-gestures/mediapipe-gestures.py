import cv2
import mediapipe as mp
import time
from pythonosc.udp_client import SimpleUDPClient
from mediapipe.tasks import python
from mediapipe.tasks.python import vision

# --- 1. Configuration & Initialization ---

# OSC Client setup
IP = "127.0.0.1"  # The IP address of the listening application (e.g., Max/MSP, TouchDesigner)
PORT = 57120      # The port of the listening application
client = SimpleUDPClient(IP, PORT)
print(f"OSC Client initialized. Sending data to {IP}:{PORT}")

# MediaPipe Gesture Recognizer setup
MODEL_PATH = 'gesture_recognizer.task' # Ensure this file is in the same directory

# Configuration options for the Gesture Recognizer
base_options = python.BaseOptions(model_asset_path=MODEL_PATH)
options = vision.GestureRecognizerOptions(
    base_options=base_options,
    running_mode=vision.RunningMode.VIDEO
)

# Create the Gesture Recognizer object
try:
    recognizer = vision.GestureRecognizer.create_from_options(options)
except RuntimeError as e:
    print(f"Error initializing MediaPipe Gesture Recognizer: {e}")
    print(f"Please ensure the model file '{MODEL_PATH}' is downloaded and in the correct path.")
    exit()

# Drawing utility for visualization (optional)
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands # Used only for HAND_CONNECTIONS and HandLandmark index

# Webcam setup
cap = cv2.VideoCapture(0) # 0 is typically the default webcam

# Variables for FPS calculation
prev_time = 0

# --- 2. Main Processing Loop ---

print("Starting webcam stream. Press 'q' to quit.")
while cap.isOpened():
    success, frame = cap.read()
    if not success:
        print("Ignoring empty camera frame.")
        continue

    # Flip the image horizontally for a selfie-view display
    frame = cv2.flip(frame, 1)

    # Convert the BGR image to RGB for MediaPipe processing
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    # Create a MediaPipe Image object
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame_rgb)

    # Get the current timestamp in milliseconds (required for VIDEO mode)
    timestamp_ms = int(time.time() * 1000)

    # Perform gesture recognition
    recognition_result = recognizer.recognize_for_video(mp_image, timestamp_ms)

    # Convert the processed image back to BGR for display
    frame_bgr = cv2.cvtColor(frame_rgb, cv2.COLOR_RGB2BGR)


    # --- 3. Process Results and Send OSC ---

    if recognition_result.gestures:
        for i, hand_gesture_result in enumerate(recognition_result.gestures):
            
            # 1. Get the recognized gesture
            # The result is a list of lists: [[Category, Category, ...], [Category, ...]]
            # We take the top gesture for the first hand (index 0)
            top_gesture = hand_gesture_result[0]
            gesture_name = top_gesture.category_name
            gesture_score = top_gesture.score
            
            # Determine which hand it is (Left/Right)
            handedness = recognition_result.handedness[i][0].category_name
            
            # 2. Format and Send OSC Message
            # The OSC Address will be something like: /hand/left/gesture or /hand/right/gesture
            osc_address = f"/hand/{handedness.lower()}/gesture"
            
            # Send the gesture name and its confidence score
            # E.g., /hand/left/gesture "Open_Palm" 0.95
            client.send_message(osc_address, [gesture_name, gesture_score])
            


            
            display_text = f"{handedness}: {gesture_name} ({gesture_score:.2f})"
            cv2.putText(frame_bgr, display_text, (30, 30),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2, cv2.LINE_AA)
            
            print(f"OSC Sent: {osc_address} {gesture_name} {gesture_score:.2f}")





    # Display the final frame
    cv2.imshow('MediaPipe Gesture Recognizer & OSC', frame_bgr)

    # Break the loop on 'q' key press
    if cv2.waitKey(5) & 0xFF == ord('q'):
        break

# --- 4. Cleanup ---
print("Exiting application...")
cap.release()
cv2.destroyAllWindows()
