import scipy.stats as stats
import subprocess
from enum import Enum
import os
import numpy as np

class Implementation(Enum):
    Serial = 1
    Mutex = 2
    rwLock = 3


def getSampleSize(confidence_level, population_stddev, error):
    z_score = stats.norm.ppf((1 + confidence_level) / 2)
    return int(round((z_score ** 2) * (population_stddev ** 2) / (error ** 2)))

def getTimeForOperationsFile(thread_count, implementation_type, case, sample_size, mMember, mInsert, mDelete):
    filename = "Case" + str(case) + "/" + implementation_type + "_" + str(thread_count) + ".txt"
    implementation_type_int = Implementation[implementation_type].value
    command = f"./main 1000 10000 {implementation_type_int} {thread_count} {mMember} {mInsert} {mDelete} {filename}"
    print(command)

    # create new file
    os.makedirs(os.path.dirname("results/" + filename), exist_ok=True)
    file = open("results/" + filename, "w")
    file.close()

    for i in range(sample_size):
        try:
            subprocess.run(command, shell=True, check=True)
        except subprocess.CalledProcessError as e:
            print(e)


def runCases(case_no, mMember, mInsert, mDelete, sample_size):
    for i in range(4):
        getTimeForOperationsFile(2**i, "Mutex", case_no, sample_size, mMember, mInsert, mDelete)
        getTimeForOperationsFile(2**i, "rwLock", case_no, sample_size, mMember, mInsert, mDelete)
        if i == 0:
            getTimeForOperationsFile(2**i, "Serial", case_no, sample_size, mMember, mInsert, mDelete)  


def calculateAvgAndStd():
    file = open("results/final.txt", "w")
    file.close()

    for i in range(3):
        for j in range(3):
            if j == 0:
                filename = "results/Case" + str(i+1) + "/" + Implementation(j+1).name + "_1.txt"
                print(filename)
                    
                try:
                    with open(filename, 'r') as file:
                        lines = [float(line.strip()) for line in file]
                            
                    # calculate average
                    avg = np.mean(lines)
                            
                    # calculate standard deviation
                    std = np.std(lines)
                        
                    with open("results/final.txt", 'a') as results_file:
                        # results_file.write(f"{avg:.2f}, {std:.2f}\n")
                        results_file.write(f"File: {filename}, Average: {avg:.2f}, StdDev: {std:.2f}\n")

                    print(filename + " average: " + str(avg) + " std: " + str(std))
                except FileNotFoundError:
                    print(filename + " File not found")
            else:
                for k in range(4):
                    filename = "results/Case" + str(i+1) + "/" + Implementation(j+1).name + "_" + str(2**k) + ".txt"
                    print(filename)
                    
                    try:
                        with open(filename, 'r') as file:
                            lines = [float(line.strip()) for line in file]
                            
                        # calculate average
                        avg = np.mean(lines)
                            
                        # calculate standard deviation
                        std = np.std(lines)
                        
                        with open("results/final.txt", 'a') as results_file:
                            # results_file.write(f"{avg:.2f}, {std:.2f}\n")
                            results_file.write(f"File: {filename}, Average: {avg:.2f}, StdDev: {std:.2f}\n")

                        print(filename + " average: " + str(avg) + " std: " + str(std))
                    except FileNotFoundError:
                        print(filename + " File not found")


if __name__ == "__main__":
    # generate sample size
    sample_size = getSampleSize(0.95, 0.5, 0.05)

    # case 1
    runCases(1, 0.99, 0.005, 0.005, sample_size)

    # case 2
    runCases(2, 0.9, 0.05, 0.05, sample_size)

    # case 3
    runCases(3, 0.5, 0.25, 0.25, sample_size)

    # calculate average and standard deviation
    calculateAvgAndStd()
