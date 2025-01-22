/*
Permite escoger el eventoal cual se desea hacer la suma.

Int_t eneIndex:		evento seleccionado, 0 ~ 999

Se deben cargar previamente myTree.root y sumaRect.C

root[].L sumRecEven()

*/



Float_t sumRectEven( Int_t evenIndex)
{
Float_t sRE=0;
Float_t tt[1024],vv[1024];
myTree->SetBranchAddress("tt",tt);
myTree->SetBranchAddress("vv0",vv);
myTree->GetEntry(evenIndex);
sRE=sumaRect(tt,vv);
return(sRE);
}
