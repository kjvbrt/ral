# ral

Key4hep library for use in ROOT RDataFrame based analysis.

## Interactive use

In order to use this library inside ROOT REPL one can open a root file with
```
root test.root
```
and then in the ROOT REPL do
```cpp
gSystem->Load("libral.so");
loadRal();
ROOT::RDataFrame dframe(*events);
auto hist = dframe.Define("pT", "k4::ral::ReconstructedParticle::get_pt(ReconstructedParticles)").Histo1D("pT");
hist->Draw();
```

The whole output of the ROOT REPL can be seen here:
```
   ------------------------------------------------------------------
  | Welcome to ROOT 6.32.04                        https://root.cern |
  | (c) 1995-2024, The ROOT Team; conception: R. Brun, F. Rademakers |
  | Built for linuxx8664gcc on Aug 21 2024, 03:51:07                 |
  | From heads/master@tags/v6-32-04                                  |
  | With g++ (GCC) 11.4.1 20230605 (Red Hat 11.4.1-2)                |
  | Try '.help'/'.?', '.demo', '.license', '.credits', '.quit'/'.q'  |
   ------------------------------------------------------------------

root [0]
Attaching file test.root as _file0...
(TFile *) 0x23c5ce0
root [1] gSystem->Load("libral.so");
root [2] loadRal()
(bool) true
root [3] ROOT::RDataFrame dframe(*events);
root [4] auto hist = dframe.Define("pT", "k4::ral::ReconstructedParticle::get_pt(ReconstructedParticles)").Histo1D("pT");
root [5] hist->Draw();
Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1
root [6]
```
