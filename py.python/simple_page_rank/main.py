import sys , urllib2 , numpy , time , traceback
from xml.dom import minidom
from HTMLParser import HTMLParser

import parser , datasort


"""the main program"""
def main():

  pirnt('input the start web site...')
  startWeb = sys.stdin.readline().rstrip()

  try:
    
	print('input the domain for testing...')
	method = sys.stdin.readline().rstrip()

	if(method == 'local'):
	  web = open(startWeb)
	elif(method == 'global'):
	  web = urllib2.urlopen(startWeb)
	
	storeWeb = web
    
	currentParseWeb = None
	currentParseWeb.append(web)

	pa = Parser

	while(web):

	  pa.feed(web.read())

	  nextPageLi = pa.getNextURL()
	  currentParseWeb.append(web)

	  for n in nextPageLi:
	  	if(n not in currentParseWeb):
		  web = n
		else:
		  web = None

	allPages = pa.getAllPages
	allPages.sort()

	row = [0 for i in range(allPages.__sizeof__())]
	transMat = [row for i in range(allPages.__sizeof__())]

	web = storeWeb
	counter = 0
	while(web):

	  pa.feed(web.read())
	  nextPageLi = pa.getNextURL()
	  currentParseWeb.append(web)

	  for n in nextPageLi:
		for k , a in allPages:
		  if(n == a):
			transMat.item(counter , k)= 1
		  else:
			transMat.item(counter , k) = 0
	  counter = counter + 1

	sortLi = datasort.generateRank(transMat)
	
	tmpD = None
	for i in range(sortLi.__len__()):
      key , val = allPages[i]
	  tmpD[[i , val]] = i , val
	
	tmpD.sort()
	
	for key , val in tmpD:
	  print 'the sort result:'
	  print str(key) + ':' + val
	
  except:
    traceback.print_exc()
	exit(1)
