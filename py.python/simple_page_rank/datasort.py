import numpy , sys , time , traceback
from xml.dom import minidom

"""
recieve the input mat and recursive compution
return the sort result
""" 
def generateRank(transmitMat):

  try:

	tmpMat = numpy.array(transmitMat)
	transmitMat = numpy.matrix(tmpMat)

	flag = False
	maxIterationNum = 0
	while(flag == False or maxIterationNum == 100):

	  flagMat = transmitMat
	  transmitMat = numpy.dot(transmitMat , transmitMat)
	  
	  if(flagMat == transmitMat):
		flag = True
	  else:
		flag = False
	  
	  maxIterationNum = maxIterationNum + 1
	
	tmpLi = transmitMat[0]
	return tmpLi

   except:
	 traceback.print_exc()
	 exit(1)
