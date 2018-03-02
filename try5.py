{
    // std::ifstream fin("data/example_ifstream.bin", std::ios::binary);
    // std::ifstream fin("data/example_ifstream2.bin", std::ios::binary);
    // std::ifstream fin("data/example_ifstream3.bin", std::ios::binary);
	std::ifstream fin("example.txt", std::ios::binary);
    if( !fin )
        printf( "The file openning failed.\n" );
    printf( "the size of char is %lu.\n", (sizeof(char)) );
    printf( "the size of short is %lu.\n", (sizeof(short)) );
    printf( "the size of Short_t is %lu.\n", (sizeof(Short_t)) );
    ////////////////
    TFile * Fout = new TFile("try5.root", "recreate");
    const int nx =  1600, ny = 1200;
    // const int nx =  800, ny = 600;
    TH2S * h = new TH2S("h", "h", nx, 0, nx, ny, 0, ny);
    /*
    for(int i=0; i<ny; i++){
        for(int j=0; j<nx; j++){
            h->SetBinContent(j+1, ny-i, (short) 123);
        }
    }
    */
    ////////////////
    ////////////////
    fin.seekg(nx*ny*2, ios::cur);
    ////////////////
    unsigned short a[nx];
    for(int i=0; i<ny; i++){
        fin.read((char *) a, nx*2);
        for(int j=0; j<nx; j++){
            h->SetBinContent(j, ny-i, a[j]/4);
        }
    }
    // std::cout << "\n";
    ////////////////
    h->Write();
    Fout->Close();
    ////////////////
}
