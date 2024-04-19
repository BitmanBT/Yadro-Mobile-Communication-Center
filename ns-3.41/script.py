import pandas as pd

dldf = pd.read_csv("DlRlcStats.txt", sep='\t', index_col=False)
for i in 1, 2:
    dltotalbytes = dldf[dldf['IMSI'] == i]['RxBytes'].sum()
    dltotaltime = dldf[dldf['IMSI'] == i].iloc[-1]['end'] - dldf[dldf['IMSI'] == i].iloc[0]['% start']
    print('Dl Average throughput of {:d} UE: '.format(i), dltotalbytes/dltotaltime / 2**10, " kBytes/s")

uldf = pd.read_csv("UlRlcStats.txt", sep='\t', index_col=False)
for i in 1, 2:
    ultotalbytes = uldf[uldf['IMSI'] == i]['RxBytes'].sum()
    ultotaltime = uldf[uldf['IMSI'] == i].iloc[-1]['end'] - uldf[uldf['IMSI'] == i].iloc[0]['% start']
    print('Ul Average throughput of {:d} UE: '.format(i), ultotalbytes/ultotaltime / 2**10, " kBytes/s")