import ROOT

if not ROOT.gSystem.Load("libral") and ROOT.gSystem.Load("libedm4hep"):
    print('RAL Found!')
    print('EDM4HEP Found!')
if ROOT.loadRal() and ROOT.edm4hep.ReconstructedParticleData():
    print('RAL Loaded!')
    print('EDM4HEP Loaded!')

URL = "https://fccsw.web.cern.ch/tutorials/apr2023/tutorial2/p8_ee_WW_mumu_ecm240_edm4hep.root"

df = ROOT.RDataFrame("events", URL)
print(df.Describe())

    
