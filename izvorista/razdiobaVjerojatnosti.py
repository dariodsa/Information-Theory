import math 
a=input()
file = open(a, "r") 
D = {}
s=file.read()
kola = len(s)
kol =0
for i in range(1,kola):
   #D[ord(s[i])-ord('x')] = D[ord(s[i])-ord('x')] + 1
    key = s[i]+s[i-1]#+s[i-2]+s[i-3]#+s[i-4]+s[i-5]+s[i-6]+s[i-7]
    if key in D:
        D[key] +=  1
    else:
        D.update({key:1})
    kol +=1
H = 0 
for key in D:
    D[key] = D[key] / kol
for key in D:
    if D[key]>=0.00001:
        H = H + D[key] * math.log2(1.0/D[key])
print("Entropija: "+str(H))
for key in D :
    print(key+" "+str(D[key]))

