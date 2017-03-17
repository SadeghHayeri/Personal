import random
import re

# config
POPULATIONSIZE = 50
CROSSOVERPROBABILITY = 100 / 100
MUTATIONPROBABILITY = 80 / 100
SWAPMUTATUINTIMES = 3
BASICLETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
LENGTH = len(BASICLETTERS)

# define fitness weights table
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

def getFitness(stringInput, gene):
    score = 0.0
    mainString = stringInput.translate(str.maketrans(gene, BASICLETTERS))
    for fitness in fitnessWeights:
        score += len( findAll(mainString, fitness) ) * fitnessWeights.get(fitness)
    return score

def initFirstGeneration():
    population = []
    for _ in range(0, POPULATIONSIZE):
        tmpList = list(BASICLETTERS)
        random.shuffle(tmpList)
        population.append( ''.join(tmpList) )
    return population

def findRouletteTable(population, stringInput):
    rouletteTable = []
    for i in range(0, len(population)):
        rouletteTable.append( getFitness(stringInput, population[i]) )
    return rouletteTable, sum(rouletteTable)

def wheelOut(rouletteTable, sumWeights):
    return random.randint(0, len(rouletteTable)-1)
    rand = random.randint(0, sumWeights-1)
    for i in range(0, len(rouletteTable)):
        rand -= rouletteTable[i]
        if rand <= 0:
            return i

def crossover(p1, p2):
    p1, p2 = list(p1), list(p2)
    child = [None] * LENGTH
    p1Selections = random.sample( range(LENGTH), int(LENGTH/2) )

    for i in p1Selections:
        child[i] = p1[i]
        p2.remove(p1[i])

    p2Index = 0;
    for i in range(0, LENGTH):
        if child[i] == None:
            child[i] = p2[p2Index]
            p2Index += 1

    return ''.join(child)

def mutation(gene):
    gene = list(gene)
    if random.random() < MUTATIONPROBABILITY:
        for _ in range(0, random.randint(0,SWAPMUTATUINTIMES)):
            x1 = random.randint(0, len(gene)-1)
            x2 = random.randint(0, len(gene)-1)
            gene[x1], gene[x2] = gene[x2], gene[x1]
    return ''.join(gene)

def selectionAndCrossover(population, stringInput):
    (rouletteTable, sumWeights) = findRouletteTable(population, stringInput)

    crossoverList = []
    for _ in range(0, POPULATIONSIZE):
        if random.random() < CROSSOVERPROBABILITY:
            crossoverList.append( population[ wheelOut(rouletteTable, sumWeights) ] )

    for i in range(0, len(crossoverList)-1):
        newChild = crossover(crossoverList[i], crossoverList[i+1])
        population.append( mutation(newChild) )

    population.sort( key=lambda x: getFitness(stringInput, x), reverse=True )
    return population[:POPULATIONSIZE]

def main():
    stringInput = open("EncryptedText", "r").read().upper()
    population = initFirstGeneration()

    result = population[0]
    maxFitness = 0
    generation = 0
    while True:
        if generation == 300:
            CROSSOVERPROBABILITY = 0
        generation += 1
        population = selectionAndCrossover(population, stringInput)
        best = getFitness(stringInput, population[0])
        if best > maxFitness:
            maxFitness = best
            result = population[0]
        print( stringInput.translate(str.maketrans(population[0], BASICLETTERS)) )
        print("Generation: ", generation)
        print("Max Score: ", maxFitness)
        print( population )

main()
