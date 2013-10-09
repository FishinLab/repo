import sys , urllib2 , time , traceback
from xml.dom import minidom
from HTMLParser import HTMLParser

"""Parser Class"""
class Parser(HTMLParser):
  
  """here is the parser initionaliztion"""
  def __init__(self):
	
	self.data = ''
	self.tag = ''
	self.attrs = None
	self.href = None
	self.currentURL = ''
	self.nextURL = None
	self.allPages = None

	self.readingflag = False

	HTMLParser.__init__(self)

  """handle the start tag in HTML element"""
  def handle_starttag(self , tag , attrs):
	
	if(tag == 'img'):
	  self.readingflag = True

	  for name , value in attrs:
		if(name == 'src'):
		  self.attrs.append(value)
    
	if(tag == 'a'):
	  self.readingflag = True
	  for name , value in attrs:
		if(name == 'href'):
		  if(value not in self.nextURL):
			self.href.append(value)

  """handle the data in HTML element"""
  def handle_data(self , data):

	if(self.readingflag):
	  self.data = data

  """handle the end tag in HTML element"""
  def handle_endtag(self , tag):
	
	if(self.readingflag):
	  self.readingflag = False
	  
  """get the attrs from object container
  	 and return a tuple(image src , size , number)
  """

  def getSrc(self):

	attrsNum = self.attrs.__len__()
	attrsSize = self.attrs.__sizeof__()
	attrsSrc = self.attrs

	resLi = [attrsSrc , attrsSize , attrsNum]
    #return resLi
  
  """get the href from object container
  	 and return a list[hrefs]
  """

  def getHref(self):
    return self.href

  """get the next URL from the object container"""
  def getNextURL(self):
    return self.nextURL

  """get the current URL from the object container"""
  def getCurrentURL(self):
  
	return self.currentURL
	
  """record the current URL"""
  def generateAllPages(self):

	for x in self.allPages:
	  index = self.allPages.__len__() + 1
	  webPage = self.currentURL

	  self.allPages.append([index , webPage])
  
  """get the all pages index from object container"""
  def getAllPages(self):
	return self.allPages
