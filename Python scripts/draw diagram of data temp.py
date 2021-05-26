import matplotlib.pyplot as plt

filename = "C:/Users/Abdelwakil/Desktop/python/draw diagrams with python pfe stuff/PD regu 3SV.txt"


file = open(filename, "r")

text=file.read()
SV=0
SV_list=[]
list=[]
tempC=[]
secondes=[]
z=0
q=0
list=text.split()
print(list)

for i in list:
    z+=1
    if z==2:
        tempC+=[float(i)]
    if z==4:
        SV_list+=[float(i)]

    if z==12:
        z=0

for u in range(0,len(tempC)):
    #q+=3
    secondes+=[u]



plt.plot(secondes,tempC)
plt.plot(secondes,SV_list)

plt.xlabel("time(secondes)")
plt.ylabel("temperature")


plt.grid()
plt.show()

