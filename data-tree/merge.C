//Script Preparado para combinar los datos obtenidos por el tanque.
//Se ejecuta en root
//
//root -l
//.L merge.C
//merge();
//root -l merged_LAGOmu.root
//drs4data->Print();  // Muestra la estructura del árbol
//drs4data->Scan();   // Verifica los datos combinados
//
//--------------------------------
void merge() {
    // Crear un archivo de salida
    TFile* outputFile = TFile::Open("merged_LAGOmu.root", "RECREATE");
    if (!outputFile || outputFile->IsZombie()) {
        std::cerr << "Error al crear el archivo de salida." << std::endl;
        return;
    }

    // Crear un TChain para combinar los árboles
    TChain chain("drs4data");

    // Lista de archivos a combinar
    chain.Add("PW0_LAGOmu.root");
    chain.Add("PW1_LAGOmu.root");
    chain.Add("PW2_LAGOmu.root");
    chain.Add("PW3_LAGOmu.root");
    chain.Add("PW4_LAGOmu.root");
    chain.Add("PW5_LAGOmu.root");
    chain.Add("PW6_LAGOmu.root");
    chain.Add("PW7_LAGOmu.root");
    chain.Add("PW8_LAGOmu.root");
    chain.Add("PW9_LAGOmu.root");

    // Clonar el árbol combinado al archivo de salida
    TTree* mergedTree = chain.CloneTree(-1, "fast");

    // Escribir el archivo de salida
    outputFile->Write();
    outputFile->Close();

    std::cout << "Archivos combinados exitosamente en 'merged_LAGOmu.root'." << std::endl;
}

