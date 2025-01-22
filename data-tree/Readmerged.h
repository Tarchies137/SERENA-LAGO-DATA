#ifndef Readmerged_h
#define Readmerged_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Readmerged {
public:
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TTree *LAGOmu;
   TFile *outputFile;

   // Fixed size dimensions of array or collections stored in the TTree if any.
   static const Int_t kNsample = 1024; // Número de muestras por evento
   Float_t R = 50;                    // Resistencia 50 [Ohm].
   Float_t Wi =0.02e-6;
   Float_t Wf =0.08e-6;			// Ventana de integracion de eventos
   Int_t ev;
   Float_t evn;
   Float_t evn_time;
   Float_t t;
   Float_t v0;
   Float_t v1;
   Float_t v2;
   Float_t tt[kNsample], vv0[kNsample], vv1[kNsample], vv2[kNsample];
   Float_t Q0, Q1, Q2;
   Float_t V_Min0, V_Min1, V_Min2;
   Float_t T_Min0, T_Min1, T_Min2;

   // Branch pointers
   TBranch        *b_evn;
   TBranch        *b_evn_time;
   TBranch        *b_t;
   TBranch        *b_v0;
   TBranch        *b_v1;
   TBranch        *b_v2;

   Readmerged(TTree *tree = 0);
   virtual ~Readmerged();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

