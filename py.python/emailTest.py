#this is the test for email

import sys , traceback , email
from email.MIMEText import MIMEText
from email import Utils

def sendEmail():
  try:
	print('input the message what U want to say: ')
	mess = sys.stdin.readline().rstrip()
	
	msg = MIMEText(mess)
	msg['To'] = '350126003@qq.com'
	msg['From'] = '350126003@qq.com'
	msg['Date'] = Utils.formatdate(localtime = 1)
	msg['Message-ID'] = Utils.make_msgid()

	print msg.as_string()
	log = open('log' , 'w')
	log.write(msg.as_string())
  except:
	traceback.print_exc()
	sys.exit(1)

def recvEmail():
  try:
	msg = email.message_from_file('log')
	print('headers from emails:')
	for header , value in msg.items():
	  print header + ':' + value

	if msg.is_multipart():
	  print('this program cannot handle this')
	  sys.exit(1)

	print(msg.get_payload())

  except:
	traceback.print_exc()
	sys.exit(1)
