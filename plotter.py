import pandas as pd
import matplotlib.pyplot as plt
'''
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
    print(f"File '{file_path}' not found.")'''

'''
df = pd.read_csv('implied_volatility.csv')

market = pd.read_csv('resources/NIFTY_put_data_1_aug_2024.csv')
market["IV"] = market["IV"].str.replace(',','').replace('-','0').astype(float)

df["DATA"] = 100*df["DATA"]

plt.scatter(df["STRIKE"],df["DATA"],label="BS Implied")
plt.scatter(df["STRIKE"],market["IV"],label="Market Implied")
plt.ylim(0,100)
plt.grid()
plt.title("Market Implied Volatility")
plt.legend()
plt.show()
'''

df = pd.read_csv("delta_hedging.csv")
df1 = pd.read_csv("no_hedge.csv")

fig,ax = plt.subplots(1,1)

ax.plot(df["Stock"],df["Option"],label="Delta Hedging")
ax.plot(df1["Stock"],df1["Option"],label="No Hedge")
ax.axvline(x=100, color='r', linestyle='--', label='Vertical Line')
ax.legend()
ax.grid()
ax.set_title("Delta Hedging")

plt.show()

'''
df = pd.read_csv("delta_hedging.csv")

plt.plot(df["Stock"],label="Stock")
plt.plot(df["Option"],label="Call")
plt.plot(df["Portfolio"],label="Delta Neutral")
plt.grid()
plt.title("Delta Neutral Portoflio")
plt.legend()
plt.show()
'''