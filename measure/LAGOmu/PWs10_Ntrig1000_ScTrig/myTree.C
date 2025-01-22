#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include <memory> //Este include fue sugerido por ChatGPT
#include <iostream>
#include <sstream>

void tree(int fileNumber) {
    // Construir el nombre del archivo de entrada
    std::string inputFileName = "PW" + std::to_string(fileNumber) + "_LAGOmu.root";

    // Abrir el archivo de entrada
    std::unique_ptr<TFile> inputFile(TFile::Open(inputFileName.c_str()));

    // Construir el nombre del archivo de salida
    std::size_t found = inputFileName.find_last_of("/\\");
    std::string outputFileName = inputFileName.substr(found + 1); // obtener solo el nombre del archivo sin la ruta
    outputFileName = outputFileName.substr(0, outputFileName.find_last_of(".")); // eliminar la extensión
    outputFileName += "_Tree.root";

    // Crear el archivo de salida
    std::unique_ptr<TFile> outputFile(new TFile(outputFileName.c_str(), "recreate"));

    // Obtener el TNtuple del archivo de entrada
    TNtuple *drs4data = (TNtuple*)inputFile->Get("drs4data");

    // Crear el TTree de salida
    TTree myTree("myTree", "Conversión de Tupla a Tree");

    Float_t tt[1024], t, vv0[1024], v0, vv1[1024], v1, vv2[1024], v2;
    Int_t ev;

    // Establecer las direcciones de memoria de las variables
    drs4data->SetBranchAddress("t", &t);
    drs4data->SetBranchAddress("v0", &v0);
    drs4data->SetBranchAddress("v1", &v1);
    drs4data->SetBranchAddress("v2", &v2);
    myTree.Branch("ev", &ev, "ev/I");
    myTree.Branch("tt", tt, "tt[1024]/F");
    myTree.Branch("vv0", vv0, "vv0[1024]/F");
    myTree.Branch("vv1", vv1, "vv1[1024]/F");
    myTree.Branch("vv2", vv2, "vv2[1024]/F");

    // Llenar el árbol
    for (Int_t i = 0; i < 1000; i++) {
        ev = i;
        for (Int_t j = 0; j < 1024; j++) {
            drs4data->GetEntry(j + i * 1024);
            tt[j] = t;
            vv0[j] = v0;
            vv1[j] = v1;
            vv2[j] = v2;
        }
        myTree.Fill();
    }

    // Cerrar el archivo de entrada
    inputFile->Close();

    // Guardar la cabecera del árbol
    myTree.Write();

    // Cerrar el archivo de salida
    outputFile->Close();
}

// Ejemplo de uso:
// tree(0) procesará el archivo PW0_LAGOmu.root y generará PW0_LAGOmu_Tree.root
// tree(1) procesará el archivo PW1_LAGOmu.root y generará PW1_LAGOmu_Tree.root
// Y así sucesivamente

