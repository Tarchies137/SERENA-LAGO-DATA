//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May  3 16:56:44 2024 by ROOT version 6.26/06
// from TTree myTree/Conversión de Tupla a Tree
// found on file: PW0_LAGOmu_Tree.root
//////////////////////////////////////////////////////////

#ifndef Datatotal_h
#define Datatotal_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Datatotal {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           ev;
   Float_t         tt[1024];
   Float_t         vv0[1024];
   Float_t         vv1[1024];
   Float_t         vv2[1024];
   Float_t         eVals[9];

   // List of branches
   TBranch        *b_ev;   //!
   TBranch        *b_tt;   //!
   TBranch        *b_vv0;   //!
   TBranch        *b_vv1;   //!
   TBranch        *b_vv2;   //!
   TBranch        *b_eVals;   //!

   Datatotal(TTree *tree=0);
   virtual ~Datatotal();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Datatotal_cxx
Datatotal::Datatotal(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PW0_LAGOmu_Tree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PW0_LAGOmu_Tree.root");
      }
      f->GetObject("myTree",tree);

   }
   Init(tree);
}

Datatotal::~Datatotal()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Datatotal::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Datatotal::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Datatotal::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ev", &ev, &b_ev);
   fChain->SetBranchAddress("tt", tt, &b_tt);
   fChain->SetBranchAddress("vv0", vv0, &b_vv0);
   fChain->SetBranchAddress("vv1", vv1, &b_vv1);
   fChain->SetBranchAddress("vv2", vv2, &b_vv2);
   fChain->SetBranchAddress("eVals", eVals, &b_eVals);
   Notify();
}

Bool_t Datatotal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Datatotal::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Datatotal::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Datatotal_cxx
