#!/usr/bin/env python3

import random
MAXN = 100000

''' Modes:
        1: N = MAXN, D small enough so O(ND) runs in time.
        2: N <= 10000, D <= 10000
        3: As in 2 but required flowers is only up to 100.
'''
mode = random.randint(1,3)
FLOWERSLIMIT = 10**9
if mode == 1:
    N = MAXN
    D = 100
if mode == 2:
    N = random.randint(1,10000)
    D = min(N, random.randint(1,10000))
if mode == 3:
    N = random.randint(1,10000)
    D = min(N, random.randint(1,10000))
    FLOWERSLIMIT = 100

directions = []
for i in range(N):
    directions.append(random.choice(['L','R']))
vals = []
for i in range(N):
    # NOTE: a poor random but better than nothing
    vals.append(random.randint(1, FLOWERSLIMIT))
deleteds = random.sample(list(range(1, N+1)), D)
random.shuffle(deleteds)
print(N, D)
print(*directions, sep='')
print(*vals, sep=' ')
print(*deleteds, sep=' ')
