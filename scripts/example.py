import ROOT

if not ROOT.gSystem.Load("libral"):
    print('RAL Found!')
if ROOT.loadRal():
    print('RAL Loaded!')
