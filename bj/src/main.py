import math

inputstring = input()
[m, a, c, x0, n, g] = [int(x) for x in inputstring.split(' ')]

a_n = pow(a,n,m)

if(a!=1):
    x_n = a_n * x0 + c*(a_n-1)/(a-1)
else:
    x_n = x0 + n*c
x_n%=m
print(int(x_n%g))




