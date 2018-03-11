import cv2
import urllib2
import numpy as np
import sys
import time
import timeit
start_time = timeit.default_timer()

hoststring = 'http://' + "192.168.0.112/cam_pic_new.php?"
print 'Streaming '

stream=urllib2.urlopen(hoststring)

bytes=''
i=0;
while (i<65536):
	# time.sleep(0.1)
	bytes+=stream.read(1024)
	a = bytes.find('\xff\xd8')
	b = bytes.find('\xff\xd9')
	if a!=-1 and b!=-1:
		jpg = bytes[a:b+2]
		bytes= bytes[b+2:]
		img = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8),cv2.IMREAD_COLOR) 
		cv2.imshow("Blah", img)
		cv2.imwrite("buffer/"+str(i)+".jpg",img)
		i=i+1;
		if cv2.waitKey(1) ==27:
			exit(0)
elapsed = timeit.default_timer()-start_time
print(elapsed)