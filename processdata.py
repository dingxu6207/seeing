# -*- coding: utf-8 -*-
"""
Created on Wed Mar 27 15:45:50 2019

@author: dingxu
"""


import os


startkey = 'deltADC ='
endkey = 'f'

SaveData = open('E:/stm32_text/seeing/save.txt','w')

with open((os.path.join('E:/stm32_text/seeing/testb.txt')), 'r') as f:
	data = f.read()
    
strlist = data.split(startkey)

print(strlist[1])


for item in strlist[1:]:
	try:
         list_link = item.split(endkey)[0]   
         SaveData.write(startkey+list_link)        
         print (startkey,list_link) 
           
	except:
                   pass 
               
SaveData.close()       