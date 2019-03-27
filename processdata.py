# -*- coding: utf-8 -*-
"""
Created on Wed Mar 27 15:45:50 2019

@author: dingxu
"""


import os

SaveData = open('E:/stm32_text/seeing/save.txt','w')


with open((os.path.join('E:/stm32_text/seeing/testb.txt')), 'r') as f:
	data = f.read()
    
strlist = data.split('deltADC =')

print(strlist[1])


for item in strlist[1:]:
	try:
         list_link = item.split('f')[0]   
         SaveData.write(list_link)        
         print (list_link) 
           
	except:
                   pass 
               
SaveData.close()       