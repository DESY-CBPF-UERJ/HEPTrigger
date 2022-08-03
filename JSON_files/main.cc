#include <iostream>
#include "sf_trigger.h"

int main() {

     // Setup analyzer
    std::string filePath = "SF_2016_ttbar.json";
    sf_trigger SFAnalyzer;
    SFAnalyzer.readFile(filePath);
    // Event loop
    float leading_pt = 20;
    float subleading_pt = 250;
    // Eval
    double SF = SFAnalyzer.getSF("DoubleEl",leading_pt, subleading_pt);
    double err_low = SFAnalyzer.getSFErrorLow("DoubleEl",leading_pt, subleading_pt);
    double err_up = SFAnalyzer.getSFErrorUp("DoubleEl",leading_pt, subleading_pt);

    std::cout << "SF: " << SF <<" com erro UP: "<< err_up<<" e erro LOW: "<<err_low<< std::endl;
    
}