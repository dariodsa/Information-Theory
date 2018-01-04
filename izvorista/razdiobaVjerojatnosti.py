import math 
a=input()
file = open(a, "r") 
D = []
s=file.read()
kol = len(s)
for i in range(2):
    D.append(0);
for i in range(kol):
   D[ord(s[i])-ord('x')] = D[ord(s[i])-ord('x')] + 1
H = 0 
for i in range(2):
    D[i] = D[i] / kol
for i in range(2):
    if D[i]>=0.00001:
        H = H + D[i] * math.log2(1.0/D[i])
print("Entropija: "+str(H))
print(D)

