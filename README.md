├── measure 				: DAtos obtendios del experiment
│   ├── LAGOmu-20240314T152939Z-001.zip    
│   └── LAGOmu
└── data-tree				: Conversiòn de estructura de datos	
    ├── Tree_Lagomu.root
    ├── Readmerged.h			
    ├── Readmerged.C
    ├── PW9_LAGOmu.root
    ├── PW8_LAGOmu.root
    ├── PW7_LAGOmu.root
    ├── PW6_LAGOmu.root
    ├── PW5_LAGOmu.root
    ├── PW4_LAGOmu.root
    ├── PW3_LAGOmu.root
    ├── PW2_LAGOmu.root
    ├── PW1_LAGOmu.root
    ├── PW0_LAGOmu.root
    ├── merged_LAGOmu.root
    └── merge.C


'merge.C' crea 'merged_LAGOmu.root' Archivo que contiene todos los datos con la misma estructura inicial 
'Readmerged.C' crea 'Tree:Lagomu.root' archivo a partir de merged_LAGOmu.root co0n estructura de arbol. ademá contiene calculos de la data

root -l


´´´.x merge.C
.L Readmerged.C
Readmerged r;
r.Loop();
TFile *_file0 = TFile::Open("Tree_Lagomu.root")
.ls´´



TFile**		Tree_Lagomu.root	
 TFile*		Tree_Lagomu.root	
  KEY: TTree	LAGOmu;2	Árbol de datos convertido [current cycle]
  KEY: TTree	LAGOmu;1	Árbol de datos convertido [backup cycle]

