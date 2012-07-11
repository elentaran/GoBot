
#include "move_generator.h"

// 4 value 8 locations -> 65536 possibilities
// one for each color
float patternValue[2][65536]; 

const string move_generator::name() {
    return "AleaBot";
}

const string move_generator::version() {
    return "1.2.1";
}


move_generator::move_generator() {

}

move_generator::move_generator(int nb_args, char* args[]) {

    _gameGoban = Goban();
    _komi = DEFAULT_KOMI;
    _nb_sim = -1;
    clear();
    handleArguments(nb_args, args);
    initPatternValue();
}

void move_generator::handleArguments(int nb_args, char* args[]) {

    assert(nb_args<=2);
    if (nb_args>1)
        _nb_sim = atoi(args[1]); 



/*
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
        //    ("compression", po::value<int>(), "set compression level")
        ;

    try{
        po::variables_map vm;
        po::store(po::parse_command_line(nb_args, args, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            exit(1);
        }

    
        if (vm.count("compression")) {
            cout << "Compression level was set to "
                 << vm["compression"].as<int>() << ".\n";
        }
    
   }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        cerr << desc <<  "\n";
        exit(0);
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
        exit(0);
    }
*/


}


// Bot can think while waiting a command (opponent thinking)
void move_generator::ponder() {

    return ;
}


string move_generator::genmove(string player) {

   _gameGoban.set_playerTurn(_gameGoban.playerToInt(player));
    Goban newGoban = Goban(_gameGoban);
    Node rootNode = Node(newGoban,_previousKeys);


    boost::timer t;
    double elapsed_time = 0; 
    int nb_sim=0;
    int res = PASSMOVE;
    double nb_s=1;

    bool cont = true;

    while ( cont )  {
        rootNode.descent();
        nb_sim++;
        elapsed_time = t.elapsed();
        if (_nb_sim > 0)
            cont = nb_sim < _nb_sim;
        else
            cont = elapsed_time < nb_s;
    }

    rootNode.show();
    cerr << "nb sim total: " << nb_sim << endl;
    cerr << "nb sim/s: " << nb_sim / elapsed_time << " (" << elapsed_time << "s)"  << endl;


    // TODO problem superko
    res = rootNode.GetMoveFinal();

    string Sres = _gameGoban.intToMove(res);

    play(player,Sres);
    return Sres;

}




void move_generator::play(string player, string move) {
    int iplayer=_gameGoban.playerToInt(player);
    int imove=_gameGoban.moveToInt(move);
    _gameGoban.play(iplayer,imove);
    _previousMoves.push_back(imove);  //for undo purpose
    _previousColors.push_back(iplayer);  //for undo purpose
    _previousKeys.push_back(_gameGoban.getGobanKey());  //for superko purpose
}


void move_generator::setSize(int boardsize) {
    _gameGoban.setSize(boardsize);
}

void move_generator::show() {
    _gameGoban.show();

}

void move_generator::clear() {
        _previousMoves.clear();
        _previousColors.clear();
        _previousKeys.clear();
        _gameGoban.clear();
        _gameGoban.setKomi(_komi);

}


void move_generator::setKomi(float komi) {
    _komi=komi;
    _gameGoban.setKomi(_komi);
}

void move_generator::setTimeLeft(int timeLeft) {
    _timeLeft = timeLeft;
}

void move_generator::undo() {

    if (_previousMoves.size() > 0) {

        _previousColors.pop_back();
        _previousMoves.pop_back();
        _previousKeys.pop_back();
        Goban tempGoban = Goban(_gameGoban.getSize());
        tempGoban.clear();
        tempGoban.setKomi(_komi);
        for (int i=0; i<_previousMoves.size(); i++) {
            tempGoban.play(_previousColors[i],_previousMoves[i]); 
        }
        _gameGoban=tempGoban;
    } else {
        cerr << "empty board" << endl;
    }
    
    //show();
}


bool move_generator::isSuperKo(int location) {

    Goban tempGoban = Goban(_gameGoban);

    tempGoban.play(tempGoban.get_playerTurn(),location);
    //tempGoban->show();
    GobanKey testKey = tempGoban.getGobanKey();

    for (int i=0; i<_previousKeys.size(); i++) {
        if (tempGoban.equal_gobanKey(testKey,_previousKeys[i])) {
           //tempGoban->showGobanKey(testKey); 
//            cerr << "SUPERKO!!" << endl;
            return true;
        }
    }


    return false;
}


void move_generator::initPatternValue() {

    int patternBonus = 1000;

    for (int color=0; color<2; color++) {

        for (int i=0; i<65536; i++)
            patternValue[color][i] = 0;
    }
    
    int num_pattern_created=0;
    int pattern[9];    
    for (int color=0; color<2; color++) {
        
        //description pattern1
        pattern[0] = color;
        pattern[1] = !color;
        pattern[2] = color;
        pattern[3] = EMPTY;
        pattern[4] = EMPTY;
        pattern[5] = EMPTY;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                for (int space3=0; space3<3; space3++) {
                    pattern[6] = space1;
                    pattern[7] = space2;
                    pattern[8] = space3;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=2;
                    }
                }
            }

        }
         
        //description pattern2
        pattern[0] = color;
        pattern[1] = !color;
        pattern[2] = EMPTY;
        pattern[3] = EMPTY;
        pattern[4] = EMPTY;
        pattern[5] = EMPTY;
        pattern[7] = EMPTY;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                    pattern[6] = space1;
                    pattern[8] = space2;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=2;
                    }
                
            }
        }


        //description pattern3
        pattern[0] = color;
        pattern[1] = !color;
        pattern[3] = color;
        pattern[4] = EMPTY;
        pattern[5] = EMPTY;
        pattern[7] = EMPTY;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                for (int space3=0; space3<3; space3++) {
                    pattern[2] = space1;
                    pattern[6] = space2;
                    pattern[8] = space3;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=2;
                    }
                }
            }

        }
  
        //description pattern4
        pattern[0] = color;
        pattern[1] = !color;
        pattern[2] = !color;
        pattern[3] = EMPTY;
        pattern[4] = EMPTY;
        pattern[5] = EMPTY;
        pattern[7] = EMPTY;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                    pattern[6] = space1;
                    pattern[8] = space2;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created++;
                    }
                
            }
        }


        //description pattern5
        pattern[0] = color;
        pattern[1] = !color;
        pattern[3] = !color;
        pattern[4] = EMPTY;
        pattern[5] = color;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                for (int space3=0; space3<3; space3++) {
                    for (int space4=0; space4<3; space4++) {
                        pattern[2] = space1;
                        pattern[6] = space2;
                        pattern[7] = space3;
                        pattern[8] = space4;

                        // getting code for every symmetry
                        for (int sym=0; sym<8; sym++) {
                            patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                            patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                            num_pattern_created+=2;
                        }
                    }
                }
            }

        }
 
        //description pattern5 bis
        pattern[0] = color;
        pattern[1] = !color;
        pattern[3] = !color;
        pattern[4] = EMPTY;
        pattern[5] = EMPTY;
        pattern[7] = EMPTY;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                for (int space3=0; space3<3; space3++) {
                    pattern[2] = space1;
                    pattern[6] = space2;
                    pattern[8] = space3;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=2;
                    }
                }
            }

        }
  
 
        //description pattern6
        pattern[1] = color;
        pattern[3] = !color;
        pattern[4] = EMPTY;
        pattern[5] = !color;

        for (int space1=0; space1<4; space1++) {
            for (int space2=0; space2<4; space2++) {
                for (int space3=0; space3<4; space3++) {
                    for (int space4=0; space4<4; space4++) {
                        for (int space5=0; space5<4; space5++) {
                            if (space3 == !color || space4 == !color || space5 == !color)
                                continue;
                            pattern[0] = space1;
                            pattern[2] = space2;
                            pattern[6] = space3;
                            pattern[7] = space4;
                            pattern[8] = space5;

                            // getting code for every symmetry
                            for (int sym=0; sym<8; sym++) {
                                patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                                patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                                num_pattern_created+=2;
                            }
                        }
                    }
                }
            }

        }
 
        //description pattern7
        pattern[0] = color;
        pattern[1] = EMPTY;
        pattern[3] = !color;
        pattern[4] = EMPTY;
        pattern[6] = EDGE;
        pattern[7] = EDGE;
        pattern[8] = EDGE;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                    pattern[2] = space1;
                    pattern[5] = space2;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=2;
                    }
                
            }
        }

 
        //description pattern8
        pattern[1] = color;
        pattern[3] = color;
        pattern[4] = EMPTY;
        pattern[5] = !color;
        pattern[6] = EDGE;
        pattern[7] = EDGE;
        pattern[8] = EDGE;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                    pattern[0] = space1;
                    pattern[2] = space2;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        patternValue[!color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=2;
                    }
                
            }
        }
 
        //description pattern9
        pattern[1] = color;
        pattern[2] = !color;
        pattern[4] = EMPTY;
        pattern[6] = EDGE;
        pattern[7] = EDGE;
        pattern[8] = EDGE;

        for (int space1=0; space1<3; space1++) {
            for (int space2=0; space2<3; space2++) {
                for (int space3=0; space3<3; space3++) {
                    pattern[0] = space1;
                    pattern[3] = space2;
                    pattern[5] = space3;
    
                    // getting code for every symmetry
                    for (int sym=0; sym<8; sym++) {
                        patternValue[color][codeSymPattern(sym,pattern)] = patternBonus;
                        num_pattern_created+=1;
                    }
               } 
            }
        }



    }
    cerr << "nb pattern created (possible overlaps): " << num_pattern_created << endl;

}

// return the pattern code corresponding to different symetry/rotation
// the pattern is described as follow:
// 0 1 2
// 3 4 5
// 6 7 8
// 4 is always empty
int move_generator::codeSymPattern(int numSym, int* pattern) {

// sym 0, 1, 2 ,3: rotation
// sym 4, 5 ,6 7: sym axiale + rotation

    int *newpattern=pattern;

    if (numSym == 1) {
        newpattern[0]=pattern[6];        
        newpattern[1]=pattern[3];        
        newpattern[2]=pattern[0];        
        newpattern[3]=pattern[7];        
        newpattern[5]=pattern[1];        
        newpattern[6]=pattern[8];        
        newpattern[7]=pattern[5];        
        newpattern[8]=pattern[2];        


    } else if (numSym == 2) {

        newpattern[0]=pattern[8];        
        newpattern[1]=pattern[7];        
        newpattern[2]=pattern[6];        
        newpattern[3]=pattern[5];        
        newpattern[5]=pattern[3];        
        newpattern[6]=pattern[2];        
        newpattern[7]=pattern[1];        
        newpattern[8]=pattern[0];        

    } else if (numSym == 3) {

        newpattern[0]=pattern[2];        
        newpattern[1]=pattern[5];        
        newpattern[2]=pattern[8];        
        newpattern[3]=pattern[1];        
        newpattern[5]=pattern[7];        
        newpattern[6]=pattern[0];        
        newpattern[7]=pattern[3];        
        newpattern[8]=pattern[6];        
    } else if (numSym == 4) {

        newpattern[0]=pattern[2];        
        newpattern[1]=pattern[1];        
        newpattern[2]=pattern[0];        
        newpattern[3]=pattern[5];        
        newpattern[5]=pattern[3];        
        newpattern[6]=pattern[8];        
        newpattern[7]=pattern[7];        
        newpattern[8]=pattern[6];        
    } else if (numSym == 5) {

        newpattern[0]=pattern[8];        
        newpattern[1]=pattern[5];        
        newpattern[2]=pattern[2];        
        newpattern[3]=pattern[7];        
        newpattern[5]=pattern[1];        
        newpattern[6]=pattern[6];        
        newpattern[7]=pattern[3];        
        newpattern[8]=pattern[0];        
    } else if (numSym == 6) {

        newpattern[0]=pattern[6];        
        newpattern[1]=pattern[7];        
        newpattern[2]=pattern[8];        
        newpattern[3]=pattern[3];        
        newpattern[5]=pattern[5];        
        newpattern[6]=pattern[0];        
        newpattern[7]=pattern[1];        
        newpattern[8]=pattern[2];        
    } else if (numSym == 7) {

        newpattern[0]=pattern[0];        
        newpattern[1]=pattern[3];        
        newpattern[2]=pattern[6];        
        newpattern[3]=pattern[1];        
        newpattern[5]=pattern[7];        
        newpattern[6]=pattern[2];        
        newpattern[7]=pattern[5];        
        newpattern[8]=pattern[8];        
    }


    return codePattern(newpattern);
}


int move_generator::codePattern(int* pattern) {

	int res=pattern[0];
	for (int i=1; i<8 ; i++) {
		res=res<<2;
		res+=pattern[i];
	}
	assert (res < 65536);
	return res;

}
