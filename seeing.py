# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 09:42:18 2019

@author: dingxu
"""


import serial
import time

i = 0

if __name__ == '__main__':
    
    f = open('E:/stm32_text/seeing/test.txt','w')
    f.write('it is ok1')
    serial = serial.Serial('COM5', 115200)  #/dev/ttyUSB0
    
   
    if serial.isOpen() :
        print("open success")
    else :
        print("open failed")       
    
        
       
    while True:
      data = serial.readline()
      if data != b'' :
        print(data.decode("gbk")) 
        f.write(data.decode("gbk"))        
          
      dt = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
      i = i + 1
      if i == 5:
        print (dt)
        f.write(dt)
        f.write('\n')  
        i = 0
       
        
      t = (dt.find(' 8:2'))   
      if (t > 0):
          f.close()
          serial.close()
    
          

   
          
 
