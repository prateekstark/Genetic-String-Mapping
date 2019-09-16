# Genetic String Mapping

We take a complex new problem and formulate it as search.
For proving the similarity of some organisms to others, we have to map the genetic strings onto each other and calculate mapping scores between each pair of organisms. The organisms with lower map scores are probably more related. Similarly, later we may have multiple organisms and we may wish to prove if they are cumulatively related. 

The computational task is to compute an overall mapping score for a group of strings.

## Problem Statement
There are K strings Xi from the vocabulary V. Each string Xi has length Ni. Your goal is to map the strings to each other. An easy way to do this is to think of this in two steps – conversion and matching. Conversion is a function F that takes in a string and returns another string. All F(Xi)s have the same length N. N is greater than equal to all Nis. The function F is only allowed to make one change to the original string – it can introduce dashes. It can introduce any number of dashes at any position. The conversion cost of X to  (X) is CC*number of dashes, CC being a constant. Once all strings have been converted the matching step just matches characters at each position. The matching cost between two characters is given by a symmetric function MC(c1, c2) where c1 and c2 are two characters ϵ V U {-}. Matching cost of two strings is the sum of matching costs of their conversions at each position. Finally, the matching cost of K strings is the sum of pairwise matching costs between each pair.



## Example

Let K =3. Let vocabulary V= {A,C,T,G}. Suppose the three strings X is are:

##### X1: ACTGTGA

##### X2: TACTGC

##### X3: ACTGA

So, for this problem N1, N2, N3 are 7, 6 and 5 respectively. Let all costs be as follows: CC = 3, MC(x,y) = 2 if x, y ϵ V and x != y; MC(x, -) = 1; MC(x, x) = 0. We may define our conversions as follows:

##### F(X1): -ACTGTGA

##### F(X2): TACT--GC

##### F(X3): -ACTG--A

With these conversions N = 8. The conversion costs are respectively 3, 6, and 9. The matching cost between F(X1) and F(X2) is 1+0+0+0+1+1+0+2 = 5. Similarly between F(X2) and F(X3) is 1+0+0+0+1+0+1+2=5 and between F(X1) and F(X3) is 0+0+0+0+0+1+1+0=2. Hence the total matching cost of this conversion is 5+5+2=12. The final output cost of this mapping problem is the sum of conversion and matching costs = 3+6+9+12=30.



## Installation
For compiling: 

```bash
bash compile.sh
```
## 

```bash

bash run.sh [input.txt] [output.txt]
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

