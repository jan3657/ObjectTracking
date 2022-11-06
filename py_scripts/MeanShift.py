import numpy as np
import cv2
import os

class MeanShift:
    def __init__(self, track_window, video_cap):
        self.video_cap = video_cap
        self.track_window = track_window

    def track(self):
        cap = self.video_cap

        print(cap)# take first frame of the video
        ret,frame = cap.read()
        # setup initial location of window
        track_window = self.track_window
        x,y,w,h = track_window

        # set up the ROI for tracking
        roi = frame[y:y+h, x:x+w]
        hsv_roi =  cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        #  cv2.imshow('HSVroi',hsv_roi)
        mask = cv2.inRange(hsv_roi, np.array((0., 60.,32.)), np.array((180.,255.,255.)))
        roi_hist = cv2.calcHist([hsv_roi],[0],mask,[180],[0,180])
        cv2.normalize(roi_hist,roi_hist,0,255,cv2.NORM_MINMAX)

        # Setup the termination criteria, either 10 iteration or move by at least 1 pt
        term_crit = ( cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 1 )

        count = 0
        while(1):
            ret ,frame = cap.read()
            count += 1

            if ret == True:
                hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
                dst = cv2.calcBackProject([hsv],[0],roi_hist,[0,180],1)

                # apply meanshift to get the new location
                ret, track_window = cv2.meanShift(dst, track_window, term_crit)

                # Draw it on image
                x,y,w,h = track_window
                img2 = cv2.rectangle(frame, (x,y), (x+w,y+h),(0,0,255),6)
                cv2.imshow('img2',img2)
                #cv2.imwrite("../output/cars"+str(count)+".jpg",img2)
                #print(os.listdir("/home/jan/Projects/ObjectTracking/output")) 

                k = cv2.waitKey(60) & 0xff
                if k == 27:
                    break
                else:
                    cv2.imwrite(chr(k)+".jpg",img2)

            else:
                break

        cv2.destroyAllWindows()
        cap.release()

