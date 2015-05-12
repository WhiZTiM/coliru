stringstream stream_Babel;


for(string line: Zmat){
                Zfile << line << endl;
                stream_Babel << "babel" << " -igzmat" << " File.gzmat" << " -osdf "<< fileName;

                system("babel -igzmat File.gzmat -osdf fileName");
                //system(stream_Babel.str().c_str());
            }
            cntfileName++;
            fileName = to_string(cntfileName) + (".sdf");
            cout << fileName << endl;