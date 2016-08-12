// note.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 12月  5 11:29:55 2014 (+0800)
// Last-Updated: 五 12月  5 11:33:27 2014 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.github.io 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Chapter13.Math Libraies inROOT
//随机数（需要哪个调用哪个）：
#include "TRandom.h"           TRandom r;r.Rndm();r.Gaus();r.Gaus(10,3);
#include "TRandom1.h"          TRandom3 r(111);
#include "TRandom2.h"          TRandom3 r(0);
#include "TRandom3.h"          TRandom3 r(0);

#include "Vector3D.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
     //默认调用TRandom3
gRandom->SetSeed();//设置随机种子
gRandom->Binomial(ntot,p)       //二项分布
gRandom->BreiWigner(mean,gamma) //Brei-Wigner分布
gRandom->Exp(tau)               //指数分布
gRandom->Gaus(mean,sigma)       //高斯分布
gRandom->Integer(imax)          //（0，imax-1）随机整数
gRandom->Landau(mean,sigma)     //Landau分布
gRandom->Poisson(mean)          //泊松分布（返回int）
gRandom->PoissonD(mean)         //泊松分布（返回double）
gRandom->Rndm()                 //（0，1]均匀分布
gRandom->Uniform(x1,x2)         //（x1，x2]均匀分布

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



// 
// note.cc ends here
