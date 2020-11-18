import time
from multiprocessing import Pool


def derivative_calc(arg):
    (x, y) = arg
    return x * y


start_time = time.time()
file_name = "20.txt"
file_result = "result.txt"

with open(file_name, "r") as file:
    polin = []
    degree = int(file.readline())
    for i in range(degree + 1):
        polin.append((int(file.readline()), i))
    with Pool() as pool:
        result = pool.map(derivative_calc, polin)
        print(result)
    print("--- %s seconds ---" % (time.time() - start_time))
    with open(file_result, "w") as file_result:
        for r in result:
            file_result.write(str(r) + "\n")
