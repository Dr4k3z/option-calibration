import pandas as pd
import matplotlib.pyplot as plt

file_path = 'fd.csv'

try:
    data = pd.read_csv(file_path)
    data.reset_index(inplace=True)
    plt.plot(data.loc[1])
    plt.plot(data.loc[10])
    #plt.plot(data.loc[100])
    #plt.plot(data.loc[1000])
    plt.show()
except FileNotFoundError:
    print(f"File '{file_path}' not found.")