---
date: July 14th 2016
header-includes:
- \usepackage{fancyhdr}
- \usepackage{multicol}
- \setlength{\textheight}{225mm}
- \setlength{\textwidth}{150mm}
- \setlength{\oddsidemargin}{6.6mm}
- \setlength{\evensidemargin}{6.6mm}
- \setlength{\topmargin}{-5.4mm}
- \pagestyle{fancy}
- \lhead{\textsl{AIIO 2019 --- Metropole}}
- \rhead{\thepage}
- \cfoot{}
- \renewcommand{\headrulewidth}{0.0pt}
- \renewcommand{\footrulewidth}{0.0pt}
---

# Metropole

Input File | Output File | Time Limit | Memory Limit
--- | --- | --- | ---
standard input | standard output | 1 second | 256 MiB

Roads are a thing of the past in the futuristic city of Metropole.
Instead, residents travel from station to station using _grids_.

The city consists of $V$ stations (numbered from 1 to $V$)
that are connected by $G$ grids (numbered from 1 to $G$).

The i-th grid connects $S_i$ stations.
If you are at any of those stations, you can pay $C_i$ dollars to travel
to any of the other stations in that grid.

You are currently at station $1$.
What is the fewest dollars you have to spend to get to station $V$?

## Subtasks and Constraints

For all subtasks, you are guaranteed that:

* $1 \leq V \leq 100\,000$.
* $1 \leq G \leq 100\,000$.
* $1 \leq S_i \leq V$, for all i.
* $1 \leq C_i \leq 100\,000$ for all i.
* $S_1 + S_2 + ... + S_V \leq 300\,000$

Additional constraints for each subtask are given below.

Subtask | Points | Additional constraints
:---: | :---: | -------------------------------------------------------------
1 | 12 | $S_i = 2$, for all i. That is, every grid connects exactly two cities.
2 | 28 | $S_i \leq 4$, for all i. That is, every grid connects at most 4 cities.
3 | 46 | $C_i = 1$, for all i. That is, every grid costs exactly 1 dollar to use.
4 | 14 | No further constraints apply.

## Input

The first line of input contains the two integers, $V$ and $G$.

Then, $G$ pairs of lines follow.
The first line in the i-th pair contains the integer $C_i$.
The second line in the i-th pair begins with $S_i$, followed by $S_i$ integers, describing the stations that the i-th grid connects.
No city is listed more than once in each grid.

## Output

The output should contain a single integer: the fewest dollars you have to spend to get from station $1$ to $V$.

## Sample Input 1
```
6 5
20
2 1 5
70
2 2 1
500
4 6
10
5 4
```

## Sample Output 1
```
600
```

## Sample Input 2

```
6 4
30
3 1 3 4
100
4 6 5 2 4
10
2 2 3
40
3 2 5 6
```

## Sample Output 2

```
70
```

## Explanation

In the first example, one path you can take is 1 -> 2 -> 4 -> 6, costing 70 + 30 + 500 = 600 dollars.
This is the minimum possible.

![Sample 1](sample1.pdf)

In the second example, one path you can take is 1 -> 2 -> 3 -> 6, costing 30 + 10 + 40 = 80 dollars.
This is the minimum possible.
Notice that when travelling from city 3 to 6, there are two grids you can use. You are free to choose the cheaper one.

![Sample 2](sample2.pdf)
