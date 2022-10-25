import cv2
import MeanShift

box = [(0,0),(0,0)]
def on_mouse(event, x, y, flags, param):
    coordinates = [] #temp coordinates
    if event == cv2.EVENT_LBUTTONDOWN:
        print('Start Mouse Position: '+str(x)+', '+str(y))
        box[0] = ((x, y))

    elif event == cv2.EVENT_LBUTTONUP:
        print('End Mouse Position: '+str(x)+', '+str(y))
        box[1] = ((x, y))


 
color = (0, 0, 255)
video_cap = cv2.VideoCapture("./ObjectTracking/data/cars.mp4")
ret, frame = video_cap.read()
while(1):
    cv2.namedWindow('video frame')
    cv2.setMouseCallback('video frame', on_mouse, 0)
    cv2.imshow("video frame", frame)
    

    k = cv2.waitKey(0)
    if k == 27:
        cv2.destroyAllWindows()
        break
    if k == 32 :
        print(box)
    else:
        print(k)

    frame = cv2.rectangle(frame, box[0], box[1], color, 6)

if(box):
    x,y,w,h = box[0][0],box[0][1],abs(box[0][0]-box[1][0]),abs(box[0][1]-box[1][1])
    track_window = (x,y,w,h)
    tracker1 = MeanShift.MeanShift(track_window,video_cap)
    tracker1.track()
    