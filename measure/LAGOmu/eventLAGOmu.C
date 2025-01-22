{
drs4data->GetListOfLeaves()->Print();
cout<<"Usar evn="<<drs4data->GetEntries()/1024 << "para ver todos juntos y salir" << endl;
cout<<"Usar 0<=evn<="<<drs4data->GetEntries()/1024-1 <<"para ver un solo evento"<<endl; 
cout<<"Otros valores de evn para terminar" << endl; 
TCanvas *myCanvas = new TCanvas;
myCanvas->Divide(1,3);
int evn=0;
while ( 0<=evn && evn<=drs4data->GetEntries()/1024 ) {
 if (evn<=drs4data->GetEntries()/1024-1) {
  myCanvas->cd(1);  drs4data->Draw("v0:t",Form("evn==%d",evn));
  myCanvas->cd(2);  drs4data->Draw("v1:t",Form("evn==%d",evn));
  myCanvas->cd(3);  drs4data->Draw("v2:t",Form("evn==%d",evn));
  myCanvas->Update();
  cout << "evn=";
  cin >> evn;
  }
 if (evn==drs4data->GetEntries()/1024) {
  myCanvas->cd(1);  drs4data->Draw("v0:t");
  myCanvas->cd(2);  drs4data->Draw("v1:t");
  myCanvas->cd(3);  drs4data->Draw("v2:t");
  break;
 }
} //myCanvas->SaveAs("myCanvas.pdf")
}
