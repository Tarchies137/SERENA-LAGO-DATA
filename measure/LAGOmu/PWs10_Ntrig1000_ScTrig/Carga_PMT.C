#include <iostream>
#include <TFile.h>
#include <TTree.h>

void createTree() {
    // Abre un archivo ROOT para escribir
    TFile *file = TFile::Open("carga.root", "RECREATE");

    // Crea un árbol
    TTree *tree = new TTree("myTree", "Árbol de datos");

    // Define un arreglo para almacenar los flotantes
    float vv[1000];

    // Añade una rama al árbol para almacenar los flotantes
    tree->Branch("vv", vv, "vv[1000]/F");

    // Llena los flotantes con datos (esto es solo un ejemplo, deberías llenarlos con tus datos reales)
    for (int i = 0; i < 1000; ++i) {
        vv[i] = i; // Llenar con tus datos reales
    }

    // Escribe el árbol en el archivo ROOT
    tree->Fill();
    tree->Write();

    // Cierra el archivo
    file->Close();
}

int main() {
    createTree();
    std::cout << "Datos almacenados en datos.root" << std::endl;
    return 0;
}

