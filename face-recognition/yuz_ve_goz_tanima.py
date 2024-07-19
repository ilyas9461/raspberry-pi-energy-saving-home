
'''
  Yuz algılama ile evde kablosuz tasarruf sistemi
  
'''

import numpy as np
import cv2
import os
import time
from imutils.video import VideoStream
import imutils
import RPi.GPIO as GPIO
import serial
import threading

kmt_str=""

''' Seri olarak gelen verilerin  thread(iş parçacığı) ile arka planda alınıp işlenmesi'''
def ReceiveThread():
    # threading fps yi normal seviyesine getirdi
  while Serial:                 # Serial nesnesi oluşturulmuş ise;

    if Serial.inWaiting() > 0:  #Giriş arabelleğindeki bayt sayısını alır ve
                                #arabellekteki bayt sayısını döndürür.
        kmt =Serial.readline()
        kmt_str= kmt.decode('utf-8').rstrip()
       # if len(kmt_str) > 0:
        if kmt_str == "ACK":
            print(kmt_str)
            
    else:
      time.sleep(0.1)   #her 100mS bir seri alma belleğine bak.

GPIO.setmode(GPIO.BCM) 
GPIO.setup(12, GPIO.OUT)        # GPIO pinini çıkış olarak kur.
GPIO.output(12,GPIO.HIGH)       # GPIO ya bağlı olan ledi yak.

''' Seri haberleşme nesnesini oluştur. '''
Serial= serial.Serial('/dev/ttyACM0', 9600, timeout=1)

'''yuz algılama veri dosyasını yükle '''
path_cascade=os.getcwd()+'/haarcascade_frontalface_default.xml'
print(path_cascade)

faceCascade = cv2.CascadeClassifier()
test=faceCascade.load(path_cascade)
print(test) # test işlem sonucunu ekrana yaz.

''' RPi video kamera başlat.'''
cap = VideoStream(src=0, usePiCamera=True, resolution=(640,480), framerate=90,
                             video_stabilization=True, contrast=0).start()   #brightness=50,
#cap = cv2.VideoCapture(0)
#cap.set(3,640) # set Width
#cap.set(4,480) # set Height

time.sleep(2.0) # kameranın açılmasını bekle 2 saniye
GPIO.output(12,GPIO.LOW)    #Ledi söndür

oda_bos=0
lamba_yak=False
time_goster=0

threading.Thread(target=ReceiveThread).start()  # seri veri alma için okuma arka plan işlmini başlat.

while True:
    
    timeCheck = time.time() #fps hesaplamk için zaman bilgisinei al
    #print(timeCheck)
    millis = int(round(time.time() * 1000))     #mS elde etmek için
    #print(millis)

    img = cap.read()    #RPi kameradan frame(çerçeve) oku.
    if img is None:
        break
    
    #img = cv2.flip(img, -1) # görüntü yönünü çeviriyor
    img= imutils.resize(img, width=320)             # Çerçeveyi yeniden boyutlandır.
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)    # Gray filtre uygula, griye çevir.
    faces = faceCascade.detectMultiScale(           # Yüz algılama algoritmasını çalıştır.
        gray,
        scaleFactor=1.2,
        minNeighbors=5,     
        minSize=(20, 20)
    )

    for (x,y,w,h) in faces:                         #Bulunan yzleri dikdörtgen çerçeve içine al.
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)#BGR
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]

    peryot=(time.time() - timeCheck)            #fps için peryot bul
    
    ''' Her bir saniyede bir sistem değişimleri ile ilgili işlem yap '''
    if millis-time_goster>1000:                 
         print("fps-",1/peryot)                 # fps(frame per second) yaz.
                  
         if len(faces)>0:                       # Algılanan yuzler ile ilgili işlem yap.
             print("Agılanan Kişi:{0}".format(len(faces)))
             
             GPIO.output(12,GPIO.HIGH)  #Rpi bağlı ledi yak

             if lamba_yak==False:       # Daha önce elamba yak komutu gönderilmedi ise;
               for x in range(3):       # 3 kere 500ms aralıklarla komut gönder. (Ardu tarfından seri alınan komut  
                                        #  RF Modülle lamba modulüne gönderilir.)
                 Serial.write(b"YAK\n")    #Ardu seri komut gönder
                 time.sleep(0.5)
               
                 
             oda_bos=0              #Oda durum değişkenini sıfırla
             lamba_yak=True         # Lamba yakıldı durum değişkenini ayarla
             
         else:                      # Eğer algılanan yuz yoksa;
             oda_bos=oda_bos+1      #oda durumunun kontrol için sayacı arttır.
             GPIO.output(12,GPIO.LOW)
             
         time_goster=millis         # Zaman sayıcını resetle
         
    if oda_bos>5:   # 5 saniyedir oda boşsa odadaki lambayı söndür
        
        if len(faces)==0 and oda_bos<=7:    # 1 saniye arkalıklarla 3 defa komut gönder.
            Serial.write(b"SONDUR\n")  #Arduya seri bilgi gönder.
            lamba_yak=False
    
         
    cv2.imshow('video',img)     # Kameradan okunan çerçeveyi ekranda göster.
    

    k = cv2.waitKey(1) & 0xff   # klavyeden basılan tuşu yakala
    if k == 27:                 # 'ESC' ise döngünden çık.   
        break


GPIO.cleanup()                  # GPIO pinlere ait etkileri temizle
cap.stop()                      # Kamerayı durdur.
cv2.destroyAllWindows()         # Açık olan bütün görüntü pencerelerini sonlandır.
