import random
import re
import colorama
from colorama import Fore

import collections
import operator

import sys
import select
import tty
import termios

colorama.init()

# config
BASICLETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
LETTERFREQUENCY = "ETAOINSHRDLCUMWFGYPBVKJXQZ"
LENGTH = len(BASICLETTERS)
POPULATIONSIZE = 54
CROSSOVERPROBABILITY = 80 / 100
MUTATIONPROBABILITY = 1 / 100
SWAPMUTATUINTIMES = 1
BESTINITSIZE = 5
INITIALSIZE = 500


# define fitness weights table
fitnessWeights = dict()
fitnessWeights["TH"] = +2
fitnessWeights["HE"] = +1
fitnessWeights["IN"] = +1                                                                                                                                        ;fitnessWeights["HE"] = +1
fitnessWeights["ER"] = +1
fitnessWeights["AN"] = +1
fitnessWeights["ED"] = +1
fitnessWeights["THE"] = +5
fitnessWeights["ING"] = +5
fitnessWeights["AND"] = +5
fitnessWeights["EEE"] = -5


newFit = dict()

# add word lists
wordLists = ['1-1000.txt', 'bigList.txt']
words = dict()
for wList in wordLists:
    f = open('wordLists/' + wList)
    for word in f.read().splitlines():
        words[word] = True

def findAll(string, reg):
    return [m.start() for m in re.finditer(reg, string)]

def getFitness(stringInput, gene):
    score = 0.0
    mainString = stringInput.translate(str.maketrans(gene, BASICLETTERS))
    for fitness in fitnessWeights:
        score += len( findAll(mainString, fitness) ) * fitnessWeights.get(fitness)
    return score

def initFirstGeneration(text, stringInput):

    lettersC = collections.Counter(''.join(filter(str.isalpha, text)) + BASICLETTERS)
    letters = sorted(lettersC.items(), key=operator.itemgetter(1), reverse=True)

    bestInit = LENGTH * ["."]

    for i in range(0, LENGTH):
        bestInit[ BASICLETTERS.index( LETTERFREQUENCY[i] ) ] = letters[i][0]

    population = BESTINITSIZE * [''.join(bestInit)]
    # population += ['WOPFGLKADBCMNEIHJZQYXRTSVU']
    for _ in range(0, POPULATIONSIZE - BESTINITSIZE + INITIALSIZE):
        tmpList = list(BASICLETTERS)
        random.shuffle(tmpList)
        population.append( ''.join(tmpList) )

    population.sort( key=lambda x: getFitness(stringInput, x), reverse=True )
    population = population[:POPULATIONSIZE]

    return population

def findRouletteTable(population, stringInput):
    rouletteTable = []
    for i in range(0, len(population)):
        rouletteTable.append( getFitness(stringInput, population[i]) )
    return rouletteTable, sum(rouletteTable)

def wheelOut(rouletteTable, sumWeights):
    # return random.randint(0, len(rouletteTable)-1)
    rand = random.randint(0, sumWeights-1)
    for i in range(0, len(rouletteTable)):
        rand -= rouletteTable[i]
        if rand <= 0:
            return i

def crossover(p1, p2):
    p1, p2 = list(p1), list(p2)
    child = [None] * LENGTH
    p1Selections = random.sample(range(LENGTH), int(LENGTH/2) )

    # print( sorted(p1Selections) )

    for i in p1Selections:
        child[i] = p1[i]
        p2[ p2.index(p1[i]) ] = '.'

    for i in range(LENGTH):
        if child[i] == None:
            if p2[i] != '.':
                child[i] = p2[i]
                p2[i] = '.'

    p2 = list(filter(lambda a: a != '.', p2))

    pointer = -1
    for i in range(LENGTH):
        if child[i] == None:
            child[i] = p2[0]
            del p2[0]

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

    population.sort( key=lambda x: getFitness(stringInput, x), reverse=True )
    del population[-20:]

    (rouletteTable, sumWeights) = findRouletteTable(population, stringInput)

    newList = []
    for i in range(0, POPULATIONSIZE):
        p1 = population[ wheelOut(rouletteTable, sumWeights) ]
        p2 = population[ wheelOut(rouletteTable, sumWeights) ]
        newList += [crossover(p1, p2)]
        if random.random() < MUTATIONPROBABILITY:
            newList[len(newList)-1] = mutation( newList[len(newList)-1] )

    # population.sort( key=lambda x: getFitness(stringInput, x), reverse=True )
    newList.sort( key=lambda x: getFitness(stringInput, x) )

    mid = POPULATIONSIZE - (int)(POPULATIONSIZE * CROSSOVERPROBABILITY)
    population[mid:] = newList[mid:]

    return population[:POPULATIONSIZE]


def findMaxFitness(population, stringInput):
    result = ("", -1);
    for g in population:
        fitness = getFitness(stringInput, g)
        if fitness > result[1]:
            result = (g, fitness)
    return result

def printText( text, words ):
    correctCount = 0
    for line in text.lower().splitlines():
        for word in line.split():
            tmpWord = ''.join(filter(str.isalpha, word))
            if tmpWord in words or word.isnumeric():
                print(Fore.GREEN + word, end=" ")
                correctCount += 1
            else:
                print(Fore.WHITE + word, end=" ")
        print()
    print()
    return correctCount

def swap(gene, a, b):
    a, b = BASICLETTERS.find(a.upper()), BASICLETTERS.find(b.upper())
    lst = list(gene);
    lst[a], lst[b] = lst[b], lst[a]
    return ''.join(lst)

def changeGene(population, a, b):
    for i in range( len(population) ):
        population[i] = swap( population[i], a, b )

def isData():
    return select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], [])

def editMode(stringInput, gene, words):
    while True:
        print(gene)
        correctCount = printText( stringInput.translate(str.maketrans(gene, BASICLETTERS)), words )
        print(Fore.RED + str(correctCount) + "/" + str(len(stringInput.split())))
        a, b = input().split()
        gene = swap( gene, a, b )

def main():
    stringInput = open("EncryptedText", "r").read().upper()

    # # cheat!
    # s = [1, 15, 17, 32, 36, 38, 49, 54, 65, 69, 71, 1001, 3004, 1005, 4004, 3005, 3006, 84, 85, 4011, 5009, 3014, 89, 5013, 1018, 5014, 95, 6016, 6017, 101, 6023, 4027, 6024, 3030, 1031, 108, 5030, 6029, 3034, 5031, 4035, 1037, 6032, 5034, 116, 119, 123, 124, 135, 144, 147, 154];
    # if stringInput[0:10] == "“AIT WZYDL": random.seed(a=33)

    population = initFirstGeneration(stringInput, stringInput)

    result = (population[0], 0)
    generation = 0
    running = True
    correctCount = 0
    wordCount = len( stringInput.split() )

    his = []

    old_settings = termios.tcgetattr(sys.stdin)
    try:
        tty.setcbreak(sys.stdin.fileno())

        i = 0
        while True:

            if running:
                if generation > 50:
                    MUTATIONPROBABILITY = 1
                generation += 1
                population = selectionAndCrossover(population, stringInput)


            best = findMaxFitness(population, stringInput)
            if best[1] > result[1]:
                result = best
                his += [ (generation, result[1]) ]

            correctCount = printText( stringInput.translate(str.maketrans(result[0], BASICLETTERS)), words )
            # print( stringInput.translate(str.maketrans(result[0], BASICLETTERS)).lower() )

            print(Fore.YELLOW + str(population) )
            print(Fore.RED + "Max Score: ", result[1])
            print(Fore.RED + str(correctCount) + "/" + str(wordCount))
            print(Fore.RED + str(his))
            print(Fore.WHITE + "Generation: ", generation)

            # if his[-1][0] + 20 < generation:
            #     generation = 0
            #     population = initFirstGeneration()
            #     result = (population[0], 0)

            # print( result )

            if isData():
                c = sys.stdin.read(1)
                if c == 's':
                    print()
                    a, b = input().split()
                    changeGene(population, a, b)
                    result = (population[0], 0)
                if c == 'x':
                    break

        editMode(stringInput, best[0], words)

    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)

main()
