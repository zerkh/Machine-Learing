__author__ = 'kh'

from numpy import matrix, mat, shape, zeros, inf

def loadSimpData():
    dataMat = matrix([
        [1, 2.1],
        [2, 1.1],
        [1.3, 1],
        [1, 1],
        [2, 1]
    ])
    classLabels = [1, 1, -1, -1, 1]
    return dataMat, classLabels
#
# def stumpClassify(dataMatrix, dimen, threshVal, threshIneq):
#
#
# def buildStump(dataArr, classLabels, D):
#     dataMatrix = mat(dataArr)
#     labelMat = mat(classLabels).T
#     m, n = shape(dataMatrix)
#     numSteps = 10.0
#     bestStump = {}
#     bestClasEst = mat(zeros((m, 1)))
#     minError = inf
#
#     for i in range(n):
#         rangeMin = dataMatrix[:, i].min()
#         rangeMax = dataMatrix[:, i].max()
#         stepSize = (rangeMax-rangeMin)/numSteps
#
#         for j in range(-1, int(numSteps)+1):
#             for inequal in ['lt', 'gt']:
#                 threshVal = (rangeMin + float(j)*stepSize)
#                 predictedVals = stumpClassify(dataMatrix, i, threshVal, inequal)