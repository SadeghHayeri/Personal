import random

s = open("input.txt", "r").read().upper()

base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
sh = list(base)
random.shuffle(sh)

tmp = ""
for char in sh:
    tmp += char

print( tmp )
print( s.translate(str.maketrans(base,tmp)) )
