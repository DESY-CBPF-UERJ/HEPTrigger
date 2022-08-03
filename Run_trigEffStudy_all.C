#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>


void Run_trigEffStudy_all()
{
	// gSystem->Load("/afs/cern.ch/work/c/ckoraka/For_ttH_Hbb_DL_Trigger_ScaleFactors/setup_for_github/CMSSW_9_4_13_patch2/src/TopAnalysis/ttH-triggerEfficiency-DL/conversion_macro_C.so");
	gSystem->Load("trigEffStudy_C.so");

	int  Era;

	//For 2016 Era
	char InputFilesData2016[3][1000] = {
        //"/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2016/met_run2016B.root",
        //"/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2016/met_run2016C.root",
        //"/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2016/met_run2016D.root",
        //"/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2016/met_run2016E.root",
        "/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_F.root",
        //"/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2016/met_run2016F2.root",
        "/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_G.root",
        "/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_H.root"
    };
	//For 2017 Era
	// char InputFilesData2017[8][1000] = {
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2017/met_run2017B.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2017/met_run2017C.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2017/met_run2017D.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2017/met_run2017E.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2017/met_run2017F.root"
    // };
	// //For 2018 Era
	// char InputFilesData2018[8][1000] = {
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2018/met_run2018A.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2018/met_run2018B.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2018/met_run2018C.root",
    //     "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2018/met_run2018D.root"
    // };
	char InputFilesMC[3][1000] = {
        "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2016/MC_2016.root",
        "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2017/MC_2017.root",
        "/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/convertedNTuples/2018/MC_2018.root"
    };




	cout<<"Data 2016 Trig Study :"<<endl;
	for (int i = 0; i<3; ++i)
	{
		cout << "Set of Files  : "<<InputFilesData2016[i]<<" is used as input. "<<endl;
        trigEffStudy("/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/","false",InputFilesData2016[i],"true",2016);
	}
	// cout<<"Data 2017 Trig Study :"<<endl;
	// for (int i = 0; i<5; ++i)
	// {
	// 	cout << "Set of Files  : "<<InputFilesData2017[i]<<" is used as input. "<<endl;
    //     trigEffStudy("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/TriggerFiles_2017/","false",InputFilesData2017[i],"true",2017);
	// }
	// cout<<"Data 2018 Trig Study :"<<endl;
	// for (int i = 0; i<4; ++i)
	// {
	// 	cout << "Set of Files  : "<<InputFilesData2018[i]<<" is used as input. "<<endl;
    //     trigEffStudy("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/TriggerFiles_2018/","false",InputFilesData2018[i],"true",2018);
	// }

	// cout<<"MC Trig Study :"<<endl;
	// trigEffStudy("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/TriggerFiles_2016/","true",InputFilesMC[0],"true",2016);
	// trigEffStudy("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/TriggerFiles_2017/","true",InputFilesMC[1],"true",2017);
	// trigEffStudy("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/TriggerFiles_2018/","true",InputFilesMC[2],"true",2018);
}
