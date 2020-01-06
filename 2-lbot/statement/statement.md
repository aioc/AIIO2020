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
- \lhead{\textsl{AIIO 2020 --- L-bots}}
- \rhead{\thepage}
- \cfoot{}
- \renewcommand{\headrulewidth}{0.0pt}
- \renewcommand{\footrulewidth}{0.0pt}
---

# L-Bots

Input File | Output File | Time Limit | Memory Limit
--- | --- | --- | ---
standard input | standard output | 1 second | 256 MiB

There is a large grid containing $R$ rows (numbered from 1 to $R$ from top to bottom)
and $C$ columns (numbered from 1 to $C$ from left to right).

Each grid square contains a robot. The robot in the $r$-th row and $c$-th column
has a _profit value_ of $P_{rc}$, which can be *negative*.

Each robot has two connectors 90 degrees apart, which it can use to connect to up two other robots.
This allows the robot to be rotated one of four different ways:

![The four ways of arranging the bots](fourbots.pdf)

If two adjacent robots are pointing one of their connectors at each other, then they will form a _pair_,
and make you a number of dollars equal to the sum of their profit values. If the sum of profit values would
be _negative_, then the robots will make you 0 dollars instead.

Since each robot has two connectors, they can each be part of up to two pairs.

What is the maximum number of dollars the robots can make if you rotate them optimally?

## Subtasks and Constraints

For all subtasks, you are guaranteed that:

* $1 \leq R, C \leq 1\,000$.
* $-1\,000 \leq P_{ij} \leq 1\,000$, for all i and j.

Additional constraints for each subtask are given below.

Subtask | Points | Additional constraints
:---: | :---: | -------------------------------------------------------------
1 | 35 | $R, C \leq 3$
2 | 15 | $R = 1$
3 | 20 | $R = 2$
4 | 22 | $R = 3$
5 | 8  | No further constraints apply.

\newpage

## Input

* The first line of input contains the two integers, $R$ and $C$.
* Then $R$ lines follow, containing $C$ integers each. On the $r$-th line, the $c$-th integer is $P_{rc}$.

## Output

The output should contain a single integer: the maximum number of dollars you can make.

## Sample Input 1
```
1 7
15 -5 100 -40 10 10 10
```

## Sample Output 1
```
115
```

## Sample Input 2

```
2 2
100 100
100 100
```

## Sample Output 2

```
800
```

## Sample Input 3

```
3 3
-10 4 -10
3 1 -10
6 2 8
```

## Sample Output 3

```
28
```

\newpage

## Explanation

In sample case 1, there are three pairs.

* The first pair makes you $-5 + 100 = 95$ dollars.
* The second pair would make you $-40 + 10 = -30$ dollars, but since this is less than 0, it makes you 0 dollars
  instead.
* The third pair makes you $10 + 10 = 20$ dollars.

This makes you a total of $95 + 0 + 20 = 115$ dollars.

![Sample case 1](sample1.pdf)

In sample case 2, every robot is part of two pairs, generating $100 + 100$ dollars for each pair.

![Sample case 2](sample2.pdf)

In sample case 3, note that the robot with profit value 4 is part of two pairs. One of those pairs makes you 0 dollars,
while the other pair makes you 5 dollars.

![Sample case 3](sample3.pdf)

