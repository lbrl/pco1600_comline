#include <TTree.h>
#include <TFile.h>
#include <TH2S.h>
#include <iostream>
#include <fstream>

int raw2root(string finname, string Foutname){
    // std::ifstream fin("data/example_ifstream.bin", std::ios::binary);
    // std::ifstream fin("data/example_ifstream2.bin", std::ios::binary);
    // std::ifstream fin("data/example_ifstream3.bin", std::ios::binary);
	// std::ifstream fin("/Users/liberulo/Dropbox/g-2/bpm/ccd_sdk/data/example_ifstream2.bin", std::ios::binary);
	std::ifstream fin(finname.c_str(), std::ios::binary);
    if( !fin )
        printf( "The file openning failed.\n" );
    printf( "the size of char is %lu.\n", (sizeof(char)) );
    printf( "the size of short is %lu.\n", (sizeof(short)) );
    printf( "the size of Short_t is %lu.\n", (sizeof(Short_t)) );
    ////////////////
    // TFile * Fout = new TFile("try5.root", "recreate");
    TFile * Fout = new TFile(Foutname.c_str(), "recreate");
    const int nx =  1600, ny = 1200;
    // const int nx =  800, ny = 600;
    TH2S * h = new TH2S("h", "h", nx, 0, nx, ny, 0, ny);
    TTree * tout = new TTree("t", "Tree with pictures");
    tout->Branch("h", &h);
    ////////////////
    ////////////////
    // fin.seekg(nx*ny*2, ios::cur);
    ////////////////
    unsigned short a[nx];
    while( !fin.eof() ){
        for(int i=0; i<ny; i++){
            fin.read((char *) a, nx*2);
            for(int j=0; j<nx; j++){
                h->SetBinContent(j, ny-i, a[j]/4);
            }
        }
        if( !fin.eof() ){
            tout->Fill();
            std::cout << "pic\n";
        }
    }
    std::cout << "Reach the end of the file.\n";
    // std::cout << "\n";
    ////////////////
    tout->Write();
    h->Write();
    Fout->Close();
    ////////////////
    return 0;
}
