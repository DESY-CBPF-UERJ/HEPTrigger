#include <iostream>
#include "sf_trigger.h"

int main() {

     // Setup analyzer
    std::string filePath = "SF_2018_ttbar.json";
    sf_trigger SFAnalyzer;
    SFAnalyzer.readFile(filePath);
    // Event loop
    float leading_pt = 210;
    float subleading_pt = 200;
    // Eval
    double SF = SFAnalyzer.getSF("DoubleEl",leading_pt, subleading_pt);
    double err_low = SFAnalyzer.getSFErrorLow("DoubleEl",leading_pt, subleading_pt);
    double err_up = SFAnalyzer.getSFErrorUp("DoubleEl",leading_pt, subleading_pt);
    double err_syst = SFAnalyzer.getSFErrorSys("DoubleEl",leading_pt, subleading_pt);
    std::cout << "SF: " << SF <<" com erro UP: "<< err_up<<" e erro LOW: "<<err_low<<"e erro syst:"<<err_syst<<std::endl;
    
}