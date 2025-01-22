#define Readmerged_cxx
#include "Readmerged.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Readmerged::Readmerged(TTree *tree) : fChain(0) 
{
   // Abrir el archivo de entrada
   TFile *f = TFile::Open("merged_LAGOmu.root");
   if (!f || !f->IsOpen()) {
      std::cerr << "Error: No se pudo abrir el archivo de entrada." << std::endl;
      return;
   }
   f->GetObject("drs4data", tree);

   Init(tree);
}

Readmerged::~Readmerged()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Readmerged::GetEntry(Long64_t entry)
{
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t Readmerged::LoadTree(Long64_t entry)
{
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Readmerged::Init(TTree *tree)
{
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evn", &evn, &b_evn);
   fChain->SetBranchAddress("evn_time", &evn_time, &b_evn_time);
   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("v0", &v0, &b_v0);
   fChain->SetBranchAddress("v1", &v1, &b_v1);
   fChain->SetBranchAddress("v2", &v2, &b_v2);

   // Crear archivo de salida y el árbol
   outputFile = new TFile("Tree_Lagomu.root", "RECREATE");
   LAGOmu = new TTree("LAGOmu", "Árbol de datos convertido");
   
   LAGOmu->Branch("ev", &ev, "ev/I");
   LAGOmu->Branch("tt", tt, TString::Format("tt[%d]/F", kNsample).Data());
   LAGOmu->Branch("vv0", vv0, TString::Format("vv0[%d]/F", kNsample).Data());
   LAGOmu->Branch("vv1", vv1, TString::Format("vv1[%d]/F", kNsample).Data());
   LAGOmu->Branch("vv2", vv2, TString::Format("vv2[%d]/F", kNsample).Data());
   LAGOmu->Branch("Q0", &Q0, "Q0/F");
   LAGOmu->Branch("Q1", &Q1, "Q1/F");
   LAGOmu->Branch("Q2", &Q2, "Q2/F");
   LAGOmu->Branch("VP1", &VP1, "VP1/F");
   LAGOmu->Branch("VP2", &VP1, "VP2/F");
   LAGOmu->Branch("STDP1", &STDP1, "STDP1/F"); 
   LAGOmu->Branch("STDP2", &STDP2, "STDP2/F"); 
   LAGOmu->Branch("V_Min0", &V_Min0, "V_Min0/F");
   LAGOmu->Branch("V_Min1", &V_Min1, "V_Min1/F");
   LAGOmu->Branch("V_Min2", &V_Min2, "V_Min2/F");
   LAGOmu->Branch("T_Min0", &T_Min0, "T_Min0/F");
   LAGOmu->Branch("T_Min1", &T_Min1, "T_Min1/F");
   LAGOmu->Branch("T_Min2", &T_Min2, "T_Min2/F");
   
   Notify();
}

Bool_t Readmerged::Notify()
{
   return kTRUE;
}

void Readmerged::Show(Long64_t entry)
{
   if (!fChain) return;
   fChain->Show(entry);
}

void Readmerged::Loop()
{
   if (!fChain) return;

   Long64_t nentries = fChain->GetEntriesFast()/kNsample;;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry = 0; jentry < nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      float p =0 ;
      
      	//
      	Float_t sR0=0,sR1=0,sR2=0;
	Float_t t0_min,v0_min=1000,t1_min,v1_min=1000,t2_min,v2_min=1000;
	Float_t vp1=0, vp2=0, v2p1=0, v2p2 =0, V2P1, V2P2;	
	Int_t np1=0, np2=0;

      	for (Int_t j = 0; j < kNsample; j++) {
        	nb = fChain->GetEntry(j + jentry*kNsample);   nbytes += nb;   
       		tt[j] = t;
            	vv0[j] = v0;
            	vv1[j] = v1;
            	vv2[j] = v2;
            	            
            if (WPi<t && t<WPf)
            {
            	vp1 += v1;
            	v2p1 += v1*v1;
            	v2p2 += v2*v2;
            	np1++;
            	vp2 += v2;
            	np2++;
            }
            
            if (t>Wi && t<Wf)
            {
            	sR0 += v0;// equivale a sR = sR+vv[k];
            	sR1 += v1;
            	sR2 += v2;
      
            	//Minimo ...  Incluir como nueva rama
		if (v0<v0_min)// Arreglar 
		{
			v0_min = v0;
			t0_min = t;
			      
		}
		if (v1<v1_min )
		{
			v1_min = v1;
			t1_min = t;
		
            	
		}
		if (v2<v2_min )
		{
			v2_min = v2;
			t2_min = t;
			
		}
		}
		
		}
	//	PEDESTAL
	//pedestal de v1,v2	
	VP1 = vp1/np1;
	VP2 = vp2/np2;
	//prom voltajes cuadrado
	V2P1 = v2p1/np1;
	V2P2 = v2p2/np2;
	// desviacion estandart Pedestal
	STDP1=sqrt(V2P1-VP1*VP1);
	STDP2=sqrt(V2P2-VP2*VP2);
	//carga total clectada
	Float_t dt = (tt[kNsample-1]-tt[0])/(kNsample - 1);
	/*Q[0] = (Float_t)sR0*dt/R;
	Q[1] = (Float_t)sR1*dt/R;
	Q[2] = (Float_t)sR2*dt/R;*/
	
	//Carga integrada 

	Q0 = sR0*dt/R;
	Q1 = (sR1*dt-VP1*(Wf-Wi))/R;
	Q2 = (sR2*dt-VP2*(Wf-Wi))/R;
	//Voltaje minimo
	V_Min0 = v0_min;
	V_Min1 = v1_min;
	V_Min2 = v2_min;
	//Tiempo en que sae da el voltaje mínimo
	T_Min0 = t0_min;
	T_Min1 = t1_min;
	T_Min2 = t2_min;
	
	
	LAGOmu->Fill();
      
	//Procesamiento de datos
	ev=jentry;	     
      	p=100*ev/10000;
	system("clear");
        std::cout << "// Completado un " << p << "%" << std::endl;

   }

   // Guardar el árbol en el archivo de salida
   outputFile->cd();
   LAGOmu->Write();
   outputFile->Close();
}

