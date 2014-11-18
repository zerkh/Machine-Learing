from math import log

def calcShannonEnt(dataset):
    numEntries = len(dataset)
    labelCount = {}
    for featVec in dataset:
        currentLabels = featVec[-1]
        if currentLabels not in labelCount.keys():
            labelCount[currentLabels] = 0;
        labelCount[currentLabels] += 1.
    shannonEnt = 0.0
    for key in labelCount:
        prob = float(labelCount[key])/numEntries
        shannonEnt -= prob*log(prob, 2)
    return shannonEnt

def createDataSet():
    dataSet = [[1, 1, "yes"],
               [1, 1, "yes"],
               [1, 0, "no"],
               [0, 1, "no"],
               [0, 1, "no"]]
    labels = ["no surfacing", "flippers"]
    return dataSet, labels
