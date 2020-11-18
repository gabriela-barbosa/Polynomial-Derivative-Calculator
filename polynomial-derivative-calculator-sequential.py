import time

start_time = time.time()
file_name = "20.txt"
with open(file_name, "r") as file:
    polin = []
    deriv = []
    degree = file.readline()
    for i in range(int(degree) + 1):
        polin.append(int(file.readline()))
        if i != 0:
            deriv.append(polin[i] * i)
            print(f'Elemento de coeficiente {deriv[i - 1]}, x elevado a {i}')
    print("--- %s seconds ---" % (time.time() - start_time))
