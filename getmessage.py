# coding = UTF-8
# 爬取李东风PDF文档,网址：http://www.math.pku.edu.cn/teachers/lidf/docs/textrick/index.htm

import urllib.request
import re
import os

# open the url and read
def getHtml(url):
    page = urllib.request.urlopen(url)
    html = page.read()
    page.close()
    return html

# compile the regular expressions and find
# all stuff we need
def getUrl(html):
    reg = r'(?:href|HREF)="?((?:http://)?.+?\.pdf)'
    url_re = re.compile(reg)
    url_lst = url_re.findall(html.decode('UTF-8'))
    return(url_lst)

def getFile(url):
    file_name = url.split('-')[-1]
    u = urllib.request.urlopen(url)
    f = open(file_name, 'wb')

    block_sz = 8192
    while True:
        buffer = u.read(block_sz)
        if not buffer:
            break

        f.write(buffer)
    f.close()
    print ("Sucessful to download" + " " + file_name)

#关键字
root_url = 'http://gr.xjtu.edu.cn//c/document_library/get_file?folderId=1826595&name=DLFE-'
#网址
raw_url = 'http://gr.xjtu.edu.cn/web/jiansun/teaching'

html = getHtml(raw_url)
url_lst = getUrl(html)

os.mkdir('ldf_download')
os.chdir(os.path.join(os.getcwd(), 'ldf_download'))

'''
for url in url_lst[:]:
    url = root_url + url
    getFile(url)
'''

for i in range(1,16):
    temp = url_lst[i].split('-')[-1]
    url = root_url + temp
    getFile(url)

    
    
