// note_hist.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 12月  5 12:32:36 2014 (+0800)
// Last-Updated: 六 4月 11 10:26:29 2015 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 8
// URL: http://wuhongyi.github.io 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Fill
//You can also call a Fill() function with one of the arguments being a string:
hist1->Fill(somename,weigth);
hist2->Fill(x,somename,weight);
hist2->Fill(somename,y,weight);
hist2->Fill(somenamex,somenamey,weight);

//案例：
TF1 *f1=new TF1("aaaaa","f(x)",min,max);
TF2 *f2=new TF2("aaaaa","f(x,y)",x min,x max,y min,y max);
TH1F *h1=new TH1F("stats name","title name",number of bins,min,max);
TH1F *h1=new TH1F("stats name","title name;X axis;Y axis",number of bins,min,max);
TH2* h = new TH2D(/* name */ "h2",/* title */ "Hist with constant bin width",/* X-dimension */ 100, 0.0, 4.0,/* Y-dimension */ 200, -3.0, 1.5);


 float x=gRandom->Uniform(-5.,5.);
 h1->Fill(x);                       //均匀分布
h1->FillRandom("gaus",50000);       //

h1->Draw();
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//循环创建图片
  TH1D  h[16];
  char Stringtemp[256];
  for(int i=0;i<16;i++){ 
    sprintf(Stringtemp,"h[%d]",i);//这样创建数组名不好，直接 "h%d"这样好
    h[i]=new TH1D(Stringtemp,"",4096,0,4096);
  } 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH3D *h3 = new TH3D("h3", "h3", 20, -2, 2, 20, -2, 2, 20, 0, 4);
Double_t x,y,z;
for (Int_t i=0; i<10000; i++) {
gRandom->Rannor(x,y);     
z=x*x+y*y;
h3->Fill(x,y,z);
}
h3->Draw("iso");

TF3 *fun3 = new TF3("fun3","sin(x*x+y*y+z*z-36)",-2,2,-2,2,-2,2);
fun3->Draw();

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const Int_t XBINS = 5; const Int_t YBINS = 5;
Double_t xEdges[XBINS + 1] = {0.0, 0.2, 0.3, 0.6, 0.8, 1.0};
Double_t yEdges[YBINS + 1] = {-1.0, -0.4, -0.2, 0.5, 0.7, 1.0};
TH2* h = new TH2D("h2", "h2", XBINS, xEdges, YBINS, yEdges);
TAxis* xAxis = h->GetXaxis(); TAxis* yAxis = h->GetYaxis();
cout << "Third bin on Y-dimension: " << endl; // corresponds to [-0.2, 0.5]
cout << "\tLower edge: " << yAxis->GetBinLowEdge(3) << endl;
cout << "\tCenter: " << yAxis->GetBinCenter(3) << endl;
cout << "\tUpper edge: " << yAxis->GetBinUpEdge(3) << endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//直方图的bin标签设置：

const Int_t nx = 12;
const Int_t ny = 20;
char *month[nx]  = {"January","February","March","April","May","June","July","August","September","October","November","December"};
char *people[ny] = {"Jean","Pierre","Marie","Odile","Sebastien","Fons","Rene","Nicolas","Xavier","Greg","Bjarne","Anton","Otto","Eddy","Peter","Pasha","Philippe","Suzanne","Jeff","Valery"};
TCanvas *c1 = new TCanvas("c1","demo bin labels",10,10,800,800);
c1->SetGrid();
c1->SetLeftMargin(0.15);
c1->SetBottomMargin(0.15);
TH2F *h = new TH2F("h","test",nx,0,nx,ny,0,ny);
for (Int_t i=0;i<5000;i++) {
  h->Fill(gRandom->Gaus(0.5*nx,0.2*nx), gRandom->Gaus(0.5*ny,0.2*ny));
 }
h->SetStats(0);
for (i=1;i<=nx;i++) h->GetXaxis()->SetBinLabel(i,month[i-1]);//直方图每个bin设置标签名字。
for (i=1;i<=ny;i++) h->GetYaxis()->SetBinLabel(i,people[i-1]);//一维二维一样的添加方式。
h->Draw("text");
   
TPaveText *pt = new TPaveText(0.6,0.85,0.98,0.98,"brNDC");//添加图片的注释。
pt->SetFillColor(18);
pt->SetTextAlign(12);
pt->AddText("Use the axis Context Menu LabelsOption");
pt->AddText(" \"a\"   to sort by alphabetic order");
pt->AddText(" \">\"   to sort by decreasing vakues");
pt->AddText(" \"<\"   to sort by increasing vakues");
pt->Draw();

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//进度滑动条
TCanvas *c1 = new TCanvas("c1","The HSUM example",200,10,600,400);
c1->SetGrid();
gBenchmark->Start("hsum");
// Create some histograms.
auto total  = new TH1F("total","This is the total distribution",100,-4,4);
auto main   = new TH1F("main","Main contributor",100,-4,4);
auto s1     = new TH1F("s1","This is the first signal",100,-4,4);
auto s2     = new TH1F("s2","This is the second signal",100,-4,4);
total->Sumw2();  // store the sum of squares of weights
total->SetMarkerStyle(21);
total->SetMarkerSize(0.7);
main->SetFillColor(16);
s1->SetFillColor(42);
s2->SetFillColor(46);
TSlider *slider = 0;////////滑动条

// Fill histograms randomly
gRandom->SetSeed();
const Int_t kUPDATE = 500;
Float_t xs1, xs2, xmain;
for ( Int_t i=0; i<10000; i++) {
  xmain = gRandom->Gaus(-1,1.5);
  xs1   = gRandom->Gaus(-0.5,0.5);
  xs2   = gRandom->Landau(1,0.15);
  main->Fill(xmain);
  s1->Fill(xs1,0.3);
  s2->Fill(xs2,0.2);
  total->Fill(xmain);
  total->Fill(xs1,0.3);
  total->Fill(xs2,0.2);
  if (i && (i%kUPDATE) == 0) {
    if (i == kUPDATE) {
      total->Draw("e1p");
      main->Draw("same");
      s1->Draw("same");
      s2->Draw("same");
      c1->Update();
      slider = new TSlider("slider",
			   "test",4.2,0,4.6,total->GetMaximum(),38);
      slider->SetFillColor(46);
    }
    if (slider) slider->SetRange(0,Float_t(i)/10000.);
    c1->Modified();
    c1->Update();
  }
 }
slider->SetRange(0,1);
total->Draw("sameaxis"); // to redraw axis hidden by the fill area
c1->Modified();
gBenchmark->Show("hsum");

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......








// 
// note_hist.cc ends here
