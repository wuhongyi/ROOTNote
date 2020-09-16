<!-- TGenPhaseSpace.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 10月 11 02:42:12 2018 (+0800)
;; Last-Updated: 三 9月 16 10:43:33 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TGenPhaseSpace*

**public TObject**

```
 Utility class to generate n-body event, with constant cross-section (default) or with Fermi energy dependence (opt="Fermi").
 The event is generated in the center-of-mass frame, but the decay products are finally boosted using the betas of the original particle.
```


## class

```cpp
private:
   Int_t        fNt;             // number of decay particles
   Double_t     fMass[18];       // masses of particles
   Double_t     fBeta[3];        // betas of decaying particle
   Double_t     fTeCmTm;         // total energy in the C.M. minus the total mass
   Double_t     fWtMax;          // maximum weigth
   TLorentzVector  fDecPro[18];  //kinematics of the generated particles

   Double_t PDK(Double_t a, Double_t b, Double_t c);

public:
   TGenPhaseSpace(): fNt(0), fMass(), fBeta(), fTeCmTm(0.), fWtMax(0.) {}
   TGenPhaseSpace(const TGenPhaseSpace &gen);
   virtual ~TGenPhaseSpace() {}
   TGenPhaseSpace& operator=(const TGenPhaseSpace &gen);

/// Input:
///  - TLorentzVector &P:    decay particle (Momentum, Energy units are Gev/C, GeV)
///  - Int_t nt:             number of decay products
///  - Double_t *mass:       array of decay product masses
///  - Option_t *opt:        default -> constant cross section
///                       "Fermi" -> Fermi energy dependence
/// Return value:
///  - kTRUE:      the decay is permitted by kinematics
///  - kFALSE:     the decay is forbidden by kinematics
   Bool_t          SetDecay(TLorentzVector &P, Int_t nt, const Double_t *mass, Option_t *opt="");
   
///  Generate a random final state.
///  The function returns the weight of the current event.
///  The TLorentzVector of each decay product can be obtained using GetDecay(n).
/// Note that Momentum, Energy units are Gev/C, GeV   
   Double_t        Generate();
   
/// Return Lorentz vector corresponding to decay n   
   TLorentzVector *GetDecay(Int_t n);

   Int_t    GetNt()      const { return fNt;}
   Double_t GetWtMax()   const { return fWtMax;}
```

## example

```cpp
void PhaseSpace() {

   TLorentzVector target(0.0, 0.0, 0.0, 0.938);
   TLorentzVector beam(0.0, 0.0, .65, .65);
   TLorentzVector W = beam + target;

   //(Momentum, Energy units are Gev/C, GeV)
   Double_t masses[3] = { 0.938, 0.139, 0.139} ;

   TGenPhaseSpace event;
   event.SetDecay(W, 3, masses);

   TH2F *h2 = new TH2F("h2","h2", 50,1.1,1.8, 50,1.1,1.8);

   for (Int_t n=0;n<100000;n++) {
      Double_t weight = event.Generate();

      TLorentzVector *pProton = event.GetDecay(0);

      TLorentzVector *pPip    = event.GetDecay(1);
      TLorentzVector *pPim    = event.GetDecay(2);

      TLorentzVector pPPip = *pProton + *pPip;
      TLorentzVector pPPim = *pProton + *pPim;

      h2->Fill(pPPip.M2() ,pPPim.M2() ,weight);
   }
   h2->Draw();
}
```


<!-- TGenPhaseSpace.md ends here -->
