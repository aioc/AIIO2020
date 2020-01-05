---
date: July 14th 2016
header-includes:
- \usepackage{fancyhdr}
- \usepackage{multicol}
- \usepackage{svg}
- \setlength{\textheight}{225mm}
- \setlength{\textwidth}{150mm}
- \setlength{\oddsidemargin}{6.6mm}
- \setlength{\evensidemargin}{6.6mm}
- \setlength{\topmargin}{-5.4mm}
- \pagestyle{fancy}
- \lhead{\textsl{AIIO 2020 --- Gaze}}
- \rhead{\thepage}
- \cfoot{}
- \renewcommand{\headrulewidth}{0.0pt}
- \renewcommand{\footrulewidth}{0.0pt}
---

# Purview

Input File | Output File | Time Limit | Memory Limit
--- | --- | --- | ---
standard input | standard output | 1 second | 256 MiB

There are $N$ statues lined up along the shoreline of a sparesely inhabited
polynesian island. The local residents have endearingly named them from 1 to $N$, going
from left to right.

Each year, the locals plant flowers in front of some of the statues.
For each statue, the locals can plant any non-negative integer number of flowers (including 0).

Each statue is either facing to the left, or to the right. If the $i$-th statue is:

* Facing to the left, then it is able to see any flowers in front of statues 1, 2, ..., $i-1$, $i$.
* Facing to the right, then it is able to see any flowers in front of statues $i$, $i+1$, ..., $N-1$, $N$.

Note that every statue is able to see the flowers in front of itself.

The locals have determined that the $i$-th statue must be able to see _at least_ $F_i$ flowers.
What is the fewest flowers that need to be planted to satisfy these requirements?

Furthermore, in subtasks 3, 4, and 5, you must also handle $D$ _demolitions_.
The $i$-th demolition destroys statue $X_i$, meaning that:

* You cannot plant any flowers in front of this statue, and
* this statue _does not_ need to see at least $F_i$ flowers anymore.

The demolitions cause all the flowers that have been planted already to disappear.
After each demolition, what is the fewest flowers that now need to be planted to satisfy these requirements?

## Subtasks and Constraints

For all subtasks, you are guaranteed that:

* $1 \leq N \leq 100\,000$.
* $0 \leq D \leq N$.
* $1 \leq F_i \leq 1\,000\,000\,000$, for all i.
* $1 \leq X_i \leq N$ for all i.
* Each statue is demolished at most once.

Additional constraints for each subtask are given below.

Subtask | Points | Additional constraints
:---: | :---: | -------------------------------------------------------------
1 | 18 | $D = 0$ and $N \leq 1000$ 
2 | 18 | $D = 0$
3 | 20 | Only right facing statues are demolished
4 | 25 | $D = N$ and $X_i = i$, for all $i$. That is, the statues are demolished from left to right.
5 | 19 | No further constraints apply.

\newpage

## Input

* The first line of input contains the two integers, $N$ and $D$.
* The second line contains a string of $N$ characters.
  The $i$-th character (starting from 1) in the string is `L` if the $i$-th statue faces left, otherwise it is `R` (the statue faces right).
* The third line contains $N$ integers. The $i$-th integer (starting from 1) is $F_i$.
* The fourth line contains $D$ integers. The $i$-th integer (starting from 1) is $X_i$.

## Output

The output should contain $D+1$ lines.

* The first line should contain a single integer: the fewest flowers that need to be planted before any demolitions.
* $D$ lines should follow. The $i$-th of these lines should contain the fewest flowers that need to be planted after the
  $i$-th demolition takes place.

## Sample Input 1
```
4 0
RRLR
5 1 2 1

```

## Sample Output 1
```
5
```

## Sample Input 2

```
6 2
RRLLRL
2 3 6 1 2 3
5 3
```

## Sample Output 2

```
8
6
4
```

\newpage

## Explanation

![Sample Case 1](sample1.pdf){ width=40% }

![Sample Case 2](sample2.pdf){ width=60% }
