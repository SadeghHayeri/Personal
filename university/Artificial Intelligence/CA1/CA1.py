import random
import re

populationSize = 10
crossoverProbability = 40 / 100
mutationProbability = 60 / 100
base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

fitnessWeights = dict()
fitnessWeights["TH"] = +2
fitnessWeights["HE"] = +1
fitnessWeights["IN"] = +1
fitnessWeights["ER"] = +1
fitnessWeights["AN"] = +1
fitnessWeights["ED"] = +1
fitnessWeights["THE"] = +5
fitnessWeights["ING"] = +5
fitnessWeights["AND"] = +5
fitnessWeights["EEE"] = -5

def findAll(string, reg):
    return [m.start() for m in re.finditer(reg, string)]

def getFitness(gene):
    score = 0.0
    for fitness in fitnessWeights:
        score += len( findAll(gene, fitness) ) * fitnessWeights.get(fitness)
    return score

# first generation
population = []
for _ in range(0,populationSize):
    tmpList = list(base)
    random.shuffle(tmpList)
    population.append(tmpList)

# print( findAll("sadegh hayeri hastam :D", "ha") )
# print( getFitness( "THE ROUND FRUIT OF A TREE OF THE ROSE FAMILY, WHICH TYPICALLY HAS THIN RED OR GREEN SKIN AND CRISP FLESH. MANY VARIETIES HAVE BEEN" ) )


# print( getFitness("fsfssfsfskkkmsfafsdgss") )
# print( "salam".translate(str.maketrans(base,base)) )
