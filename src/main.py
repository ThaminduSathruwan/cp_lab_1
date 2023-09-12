import scipy.stats as stats
import subprocess
from enum import Enum

class Implementaion(Enum):
    Serial = 1
    Mutex = 2
    rwLock = 3
    
def getSampleSize(confidence_level, population_stddev, error):
    z_score = stats.norm.ppf((1 + confidence_level) / 2)
    return int(round((z_score ** 2) * (population_stddev ** 2) / (error ** 2)))

def getTimeForOperationsFile(thread_count, implementation_type, case, sample_size, mMember, mInsert, mDelete):
    filename = "Case" + str(case) + "/" + implementation_type + "_" + str(thread_count) + ".txt"
    implementation_type_int = Implementaion[implementation_type].value
    command = "./main 1000 10000 " + str(thread_count) + " " + str(implementation_type_int) + " " + str(mMember) + " " + str(mInsert) + " " + str(mDelete) + " " + filename

    # create new file
    file = open(filename, "w")
    file.close()

    for i in range(sample_size):
        try:
            subprocess.run(command, shell=True, check=True)
        except subprocess.CalledProcessError as e:
            print(e)



