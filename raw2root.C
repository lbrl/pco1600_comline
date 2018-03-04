#include <TTree.h>
#include <TFile.h>
#include <TH2S.h>
#include <iostream>
#include <fstream>

int raw2root(string finname, string Foutname,
        int binx = 1, int biny = 1){
	std::ifstream fin(finname.c_str(), std::ios::binary);
    if( !fin ){
        printf( "The file openning failed.\n" );
        return 1;
    }
    ////////////////
    TFile * Fout = new TFile(Foutname.c_str(), "recreate");
    if( Fout->IsZombie() ){
        std::cout << "The output file is a zombie.\n";
        delete Fout;
        Fout = 0;
        return 2;
    }
    const int nx =  1600 / binx, ny = 1200 / biny;
    TH2S * h = new TH2S("h", "h", nx, 0, nx, ny, 0, ny);
    TTree * tout = new TTree("t", "Tree with pictures");
    tout->Branch("h", &h);
    ////////////////
    unsigned short a[nx];
    int counter = 0;
    while( !fin.eof() ){
        for(int i=0; i<ny; i++){
            fin.read((char *) a, nx*2);
            for(int j=0; j<nx; j++){
                h->SetBinContent(j, ny-i, a[j]/4);
            }
        }
        if( !fin.eof() ){
            tout->Fill();
            counter += 1;
            if( counter % 100 == 0 )
                std::cout << counter << "\n";
        }
    }
    std::cout << "Reach the end of the file.\n";
    ////////////////
    tout->Write();
    h->Write();
    Fout->Close();
    ////////////////
    return 0;
}
