from numpy import *
import operator
from os import listdir

def createDataSet():
    group = array([[1.0, 1.1], [1.0, 1.0], [0, 0], [0, 0.1]])
    labels = ['A', 'A', 'B', 'B']
    return group, labels

def Classify0(inX, dataset, labels, k):
    DataSetSize = dataset.shape[0]
    DiffMat = tile(inX, (DataSetSize,1)) - dataset
    sqDiffMat = DiffMat**2
    sqDistances = sqDiffMat.sum(axis=1)
    Distances = sqDistances**0.5
    SortedDistInd = Distances.argsort()
    ClassCount = {}

    for i in range(k):
        voteIlabel = labels[SortedDistInd[i]]
        ClassCount[voteIlabel] = ClassCount.get(voteIlabel, 0) + 1
    
    SortedClassCount = sorted(ClassCount.iteritems(), key = operator.itemgetter(1), reverse = True)
    return SortedClassCount[0][0]

def file2matrix(filename):
    fr = open(filename)
    ArrayOfLines = fr.readlines()
    NumberOfLines = len(ArrayOfLines)
    returnMat = zeros((NumberOfLines, 3))
    ClassLabelVec = []
    Index = 0

    for line in ArrayOfLines:
        line = line.strip()
        listFromLines = line.split('\t')
        returnMat[Index, :] = listFromLines[0:3]
        ClassLabelVec.append(int(listFromLines[-1]))
        Index += 1

    return returnMat, ClassLabelVec

def autoNorm(dataset):
    MinVal = dataset.min(0)
    MaxVal = dataset.max(0)
    ranges = MaxVal-MinVal
    m = dataset.shape[0]
    normDataSet = dataset-tile(MinVal, (m,1))
    normDataSet = normDataSet/tile(ranges, (m,1))
    return normDataSet, ranges, MinVal

def datingClassTest():
    hoRatio = 0.1
    datingDataMat, datingLabels = file2matrix('datingTestSet.txt')
    normMat, ranges, MinVal = autoNorm(datingDataMat)
    m = normMat.shape[0]
    numTestVecs = int(hoRatio*m)
    errorCounr = 0.0

    for i in range(numTestVecs):
        classifierResult = Classify0(normMat[i,:], datingDataMat[numTestVecs:m, :], datingLabels[numTestVecs:m, :], 3)
        print "the classifier came back with: %d, the real answer is: %d" %(classifierResult, datingLabels[i])
        if(classifierResult != datingLabels[i]):errorCount += 1.0

    print "the total error rate is: %f" %(errorCount/float(numTestVecs))

def classifyPerson():
    resultList = ['not at all', 'in small doses', 'in large doses']
    percentTats = float(raw_input("percentage of time spent playing video games?"))
    ffMiles = float(raw_input("frequent flier miles earned per year?"))
    iceCream = float(raw_input("liters of ice cream consumed per year?"))
    datingDataMat, datingLabels = file2matrix('datingTestSet2.txt')
    normMat, ranges, minVals = autoNorm(datingDataMat)
    inArr = array([ffMiles, percentTats, iceCream])
    classifierResult = Classify0((inArr-minVals)/ranges, normMat, datingLabels, 3)
    print "You will probably like this person: ", resultList[classfierResult - 1]

def img2vector(filename):
    returnVect = zeros((1,1024))
    fr = open(filename)
    for i in range(32):
        lineStr = fr.readline()
        for j in range(32):
            returnVect[0,i*32+j] = int(lineStr[j])
    return returnVect

def handwritingClassTest():
    hwLabels = []
    trainingFileList = listdir("trainingDigits")
    m = len(trainingFileList)
    trainingMat = zeros((m, 1024))

    for i in range(m):
        filenameStr = trainingFileList[i]
        fileStr = filenameStr.split('.')[0]
        classStr = int(fileStr.split('_')[0])
        hwLabels.append(classStr)
        trainingMat[i,:] = img2vector("trainingDigits/%s" %filenameStr)

    testFileList = listdir("testDigits")
    errorCount = 0.0
    mTest = len(testFileList)
    for j in range(mTest):
        filenameStr = testFileList[j]
        fileStr = filenameStr.split('.')[0]
        classStr = int(fileStr.split('_')[0])
        testVec = img2vector("testDigits/%s" %filenameStr)
        classifierResult = Classify0(testVec, trainingMat, hwLabels, 3)
        print "the classifier came back with: %d, the real answer is: %d" %(classifierResult, classStr)
        
        if(classifierResult != classStr):errorCount += 1.0
    print "\nthe total number of errors is: %d" %errorCount
    print "\nthe totsl error rate is: %f" %(errorCount/float(mTest))
    
    
