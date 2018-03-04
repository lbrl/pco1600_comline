/*
 *
 *  Usage:
 *    $ root -b -q 'raw2root.C+(input, output, binning_X, binning_Y)'
 *    $ root -b -q 'raw2root.C+("/path/to/in/fi.le", "out.root")'
 *    $ root -b -q 'raw2root.C("/path/to/in/fi.le", "out.root")'
 *    $ root -b -q 'raw2root.C+("/path/to/in/fi.le", "out.root", 2, 2)'
 *
 *  Default binning is 1 by 1.
 *
 *  
 *  An output file contains a TTree t and TH2S h histogram.
 *  The histogram is the last converted frame.  The TTree t
 *  contains one branch of TH2S histograms.  Each hisogram
 *  is a frame,  from the very first to the last.
 *
 *  An example how to access the stred converted histograms:
 *    Open file.
 *    $ root output.root
 *    Draw the last histogram h.
 *    [] h->Draw("colz")
 *    Draw the first histogram from the tree.
 *    [] t->Draw("h->Draw(\"colz\")", "", "goff", 1)
 *    or
 *    [] t->Draw("h->Draw(\"colz\")", "", "goff", 1, 0)
 *    Draw the second histogram.
 *    [] t->Draw("h->Draw(\"colz\")", "", "goff", 1, 1)
 *    Draw the tenth histogram.
 *    [] t->Draw("h->Draw(\"colz\")", "", "goff", 1, 9)
 *
 */


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
