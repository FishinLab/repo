#test of web service

import sys , urllib2 , urllib

def downloadPage():
  print('input the url address of the page for download:')
  req = sys.stdin.readline().rstrip()
  fd = urllib2.urlopen(req)

  print('got the page url:' + str(fd.geturl()))

  try:
	info = fd.info()
	for key , value in info.items():
	  print('%s = %s' % (key , value))
  except urllib2.HTTPError , e:
	print('error: ' , e)
	sys.exit(1)

  print('\n\n\n\nthe page: \n\n\n\n')
  while True:
	data = fd.read(1024)

	if not len(data):
	  break
	sys.stdout.write(data)
def formGET():
  def addUrl(url , data):
	return url + '?' + urllib.urlencode(data)

  print('input the zipcode:')
  zipcode = sys.stdin.readline().rstrip()

  print('input the url:')
  u = sys.stdin.readline().rstrip()

  url = addUrl(u , (['query' , zipcode]))

  print('using URL:' , url)
  req = urllib2.Request(url)
  fd = urllib2.urlopen(req)

  while True:
	data = fd.read(1024)
	if not len(data):
	  break
	sys.stdout.write(data)


