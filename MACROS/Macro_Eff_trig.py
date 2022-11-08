import os
import Run_conversion as Conv

type = 18

if (type == 16 or type == 'all'):
    #Criando os arquivos.root
    # os.system("root -q Conversion_Data_C_2016.C")
    # os.system("root -q Conversion_Data_D_2016.C")
    # os.system("root -q Conversion_Data_E_2016.C")
    # os.system("root -q Conversion_Data_F_2016.C")
    # os.system("root -q Conversion_Data_G_2016.C")
    # os.system("root -q Conversion_Data_H_2016.C")
    # os.system("root -q Conversion_Data_HIPM_F_2016.C")
    # os.system("root -q Conversion_Data_v2_B_2016.C")
    # os.system("root -q Conversion_ttbar_2016.C")
    # os.system("root -q Conversion_ttbar_APV_2016.C")
    
    # list_samples_2016 = [
    #                 ("Data_MET_C_16_files","_Run2016C"),
    #                 ("Data_MET_D_16_files","_Run2016D"),
    #                 ("Data_MET_E_16_files","_Run2016E"),
    #                 ("Data_MET_F_16_files","_Run2016F_1"),
    #                 ("Data_MET_G_16_files","_Run2016G"),
    #                 ("Data_MET_H_16_files","_Run2016H"),
    #                 ("Data_MET_HIPM_F_16_files","_Run2016F_2"),
    #                 # ("Data_MET_v1_B_16_files","_Run2016B_1"),
    #                 ("Data_MET_v2_B_16_files","_Run2016B_2"),
    #                 ("TTTo2L2Nu_16_files","_ttbar"),
    #                 ("TTTo2L2Nu_APV_16_files","_ttbarAPV"),
    #                 ("WZTo3LNu_16_files","_WZ"),
    #                 ("WZTo3LNu_APV_16_files","_WZAPV"),
    #                 ("ZZTo4L_16_files","_ZZ"),
    #                 ("ZZTo2L2Nu_16_files","_ZZAPV")
    #                 ]
    # for x,y in list_samples_2016:
    #     Conv.change_template(x,y,"2016")     
    
    # os.system("hadd -f ../datasets/2016/_Run2016F.root ../datasets/2016/_Run2016F_1.root ../datasets/2016/_Run2016F_2.root ")
    # os.system("rm -r ../datasets/2016/_Run2016F_1.root ../datasets/2016/_Run2016F_2.root")
    # os.system("hadd -f ../datasets/2016/_Run2016B.root ../datasets/2016/_Run2016B_2.root ") #../datasets/2016/_Run2016B_1 
    # os.system("rm -r ../datasets/2016/_Run2016B_1.root ../datasets/2016/_Run2016B_2.root")
    
    # os.system("hadd -f ../datasets/2016/_Run2016Full.root  ../datasets/2016/_Run2016C.root ../datasets/2016/_Run2016D.root ../datasets/2016/_Run2016E.root ../datasets/2016/_Run2016F.root ../datasets/2016/_Run2016G.root ../datasets/2016/_Run2016H.root")
    # os.system("hadd -f ../datasets/2016/_MC2016.root ../datasets/2016/_ttbar.root ../datasets/2016/_ttbarAPV.root ../datasets/2016/_WZ.root ../datasets/2016/_WZAPV.root ../datasets/2016/_ZZ.root ../datasets/2016/_ZZAPV.root")
    # os.system("rm -r  ../datasets/2016/_ttbar.root ../datasets/2016/_ttbarAPV.root ../datasets/2016/_WZ.root ../datasets/2016/_WZAPV.root ../datasets/2016/_ZZ.root ../datasets/2016/_ZZAPV.root")
  
    # os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_Run2016Full.root\", \"true\", 2016)'")
    # os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_MC2016.root\", \"true\", 2016)'")

    # os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Run2016Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MCPT/MC/outfile_MC2016.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/\",1,\"\")'")
    # list_varied_SF = ["_NJETSHIGH","_NJETSLOW","_NPVHIGH","_NPVLOW","_METHIGH","_METLOW","_ExNumMu0","_ExNumMu1","_ExNumMu2","_ExNumEl0","_ExNumEl1","_ExNumEl2","_DeltaRZone0","_DeltaRZone1","_DeltaRZone2","_DeltaRZone3"]
    # for x in list_varied_SF:
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Run2016Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MCPT/MC/outfile_MC2016.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/\",1,\""+x+"\")'")

    # list_eras = ['B','C','D','E','F','G','H']
    # for x in list_eras:
    #     os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_Run2016"+x+".root\", \"true\", 2016)'")
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Run2016"+x+".root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MCPT/MC/outfile_MC2016.root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/\",0,\"\")'")


    # os.system("root -q 'ScaleFactors_syst_lumi.C(\"2016\")'")




    ## COMEÇA A DAR ERRO AQUI
    # # STUDY of NEW REGIONS
    # for x in list_varied_SF:
    #     os.system("root -q 'Systematic_regions.C(\""+x+"\",\"2016\")'")


    # os.system("root -q '../systCombiner.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/\",\"2016\")'")


    os.system("root -q '../outputs_and_plotting_script/2016/Writer_SF.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/Final_2016_SFs_with_full_systematics/\",\"2016\")'")

if (type==17 or type == 'all'):

    list_samples_2017 = [
                    ("Data_MET_B_17_files","_Run2017B"),
                    ("Data_MET_C_17_files","_Run2017C"),
                    ("Data_MET_D_17_files","_Run2017D"),
                    ("Data_MET_E_17_files","_Run2017E"),
                    ("Data_MET_F_17_files","_Run2017F"),
                    ("TTTo2L2Nu_17_files","_ttbar"),
                    ("WZTo3LNu_17_files","_WZ"),
                    ("ZZTo2L2Nu_17_files","_ZZ")
                    ]
    for x,y in list_samples_2017:
        Conv.change_template(x,y,"2017")     
    
    os.system("hadd -f ../datasets/2017/_Run2017Full.root ../datasets/2017/_Run2017B.root ../datasets/2017/_Run2017C.root ../datasets/2017/_Run2017D.root ../datasets/2017/_Run2017E.root ../datasets/2017/_Run2017F.root")
    os.system("hadd -f ../datasets/2017/_MC2017.root ../datasets/2017/_ttbar.root ../datasets/2017/_WZ.root ../datasets/2017/_ZZ.root")
    
    os.system("rm -r ../datasets/2017/_ttbar.root ../datasets/2017/_WZ.root ../datasets/2017/_ZZ.root")
  
    os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_Run2017Full.root\", \"true\", 2017)'")
    os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_MC2017.root\", \"true\", 2017)'")

    os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Run2017Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/MC/outfile_MC2017.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/\",1,\"\")'")
    list_varied_SF = ["_NJETSHIGH","_NJETSLOW","_NPVHIGH","_NPVLOW","_METHIGH","_METLOW","_ExNumMu0","_ExNumMu1","_ExNumMu2","_ExNumEl0","_ExNumEl1","_ExNumEl2","_DeltaRZone0","_DeltaRZone1","_DeltaRZone2","_DeltaRZone3"]
    for x in list_varied_SF:
        os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Run2017Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/MC/outfile_MC2017.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/\",1,\""+x+"\")'")

    list_eras = ['B','C','D','E','F']
    for x in list_eras:
        os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_Run2017"+x+".root\", \"true\", 2017)'")
        os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Run2017"+x+".root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/MC/outfile_MC2017.root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/\",0,\"\")'")


    os.system("root -q 'ScaleFactors_syst_lumi.C(\"2017\")'")

    # STUDY of NEW REGIONS
    for x in list_varied_SF:
        os.system("root -q 'Systematic_regions.C(\""+x+"\",\"2017\")'")


    os.system("root -q '../systCombiner.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/\",\"2017\")'")


    os.system("root -q '../outputs_and_plotting_script/2017/Writer_SF.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/Final_2017_SFs_with_full_systematics/\",\"2017\")'")





 




if (type == 18 or type == 'all'):
    
    # list_samples_2018 = [
    #                 ("Data_MET_A_18_files","_Run2018A"),
    #                 ("Data_MET_B_18_files","_Run2018B"),
    #                 ("Data_MET_C_18_files","_Run2018C"),
    #                 ("Data_MET_D_18_files","_Run2018D"),
    #                 ("TTTo2L2Nu_18_files","_ttbar"),
    #                 # ("DYJetsToLL_HT-Inclusive_18_files","_DY_HT")
    #                 # ("DYJetsToLL_Pt-Inclusive_18_files","_DY_PT")
    #                 ("WZTo3LNu_18_files","_WZ"),
    #                 ("ZZTo2L2Nu_18_files","_ZZ")
    #                 ]
    # for x,y in list_samples_2018:
    #     Conv.change_template(x,y,"2018")      



    # os.system("hadd -f ../datasets/2018/_Run2018Full.root ../datasets/2018/_Run2018A.root ../datasets/2018/_Run2018B.root ../datasets/2018/_Run2018C.root ../datasets/2018/_Run2018D.root")
    # os.system("hadd -f ../datasets/2018/_MC2018.root ../datasets/2018/_ttbar.root ../datasets/2018/_WZ.root ../datasets/2018/_ZZ.root")

    # os.system("rm ../datasets/2018/_ttbar.root ../datasets/2018/_WZ.root ../datasets/2018/_ZZ.root")


    # os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_Run2018Full.root\", \"true\", 2018)'")
    # os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_MC2018.root\", \"true\", 2018)'")

    # os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",1,\"\")'")
    # list_varied_SF = ["_NJETSHIGH","_NJETSLOW","_NPVHIGH","_NPVLOW","_METHIGH","_METLOW","_ExNumMu0","_ExNumMu1","_ExNumMu2","_ExNumEl0","_ExNumEl1","_ExNumEl2","_DeltaRZone0","_DeltaRZone1","_DeltaRZone2","_DeltaRZone3"]
    # for x in list_varied_SF:
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",1,\""+x+"\")'")

    # list_eras = ['A','B','C','D']
    # for x in list_eras:
    #     os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_Run2018"+x+".root\", \"true\", 2018)'")
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018"+x+".root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",0,\"\")'")

    os.system("root -q 'ScaleFactors_syst_lumi.C(\"2018\")'")

    # # # STUDY of NEW REGIONS
    # for x in list_varied_SF:
    #     os.system("root -q 'Systematic_regions.C(\""+x+"\",\"2018\")'")





    os.system("root -q '../systCombiner.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",\"2018\")'")


    os.system("root -q '../outputs_and_plotting_script/2018/Writer_SF.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/Final_2018_SFs_with_full_systematics/\",\"2018\")'")



########################################################################################################################################################################################################################################################################################################################
########################################################################################################################################################################################################################################################################################################################
########################################################################################################################################################################################################################################################################################################################



###### os.system("root -q 'conversion_macro.C(\"/home/matheus/Desktop/TChain/Data_MET_F_16_files\", \"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_F.root\")'")
###ETAPA DE CRIACAO DAS NOSSAS TREES PARA DIFERENTES ANOS/AMOSTRAS
# #----DADOS-2016---------------------------------------------------------------------------------
# os.system("root -q Conversion_Data_C_2016.C")
# os.system("root -q Conversion_Data_D_2016.C")
# os.system("root -q Conversion_Data_E_2016.C")
# os.system("root -q Conversion_Data_F_2016.C")
# os.system("root -q Conversion_Data_G_2016.C")
# os.system("root -q Conversion_Data_H_2016.C")
# os.system("root -q Conversion_Data_HIPM_F_2016.C")
# os.system("root -q Conversion_Data_v2_B_2016.C")
# # # # # #MC 2016
# os.system("root -q Conversion_ttbar_2016.C")
# os.system("root -q Conversion_ttbar_APV_2016.C")
# os.system("root -q Conversion_DY_inclu_2016.C")
# os.system("root -q Conversion_DYHT_inclu_2016.C")
## DY PT BINNED
# os.system("root -q Conversion_DYPT_0_65_2016.C")
# os.system("root -q Conversion_DYPT_50_100_2016.C")
# os.system("root -q Conversion_DYPT_100_250_2016.C")
# os.system("root -q Conversion_DYPT_250_400_2016.C")
# os.system("root -q Conversion_DYPT_400_650_2016.C")
# os.system("root -q Conversion_DYPT_650_inf_2016.C")

# # #################################
# # #JUNTANDO TODAS AS TREES DE DADOS EM UMA SO E TODAS AS TREES DE MC EM UMA SO
# os.system("rm ../datasets/2016/_DataPRE.root")
# os.system("rm ../datasets/2016/_DataPOS.root")
# os.system("rm ../datasets/2016/_Data2016.root")
# os.system("hadd ../datasets/2016/_Data2016.root ../datasets/2016/Data_F* ../datasets/2016/Data_G* ../datasets/2016/Data_H.root ../datasets/2016/Data_C* ../datasets/2016/Data_D* ../datasets/2016/Data_E* ../datasets/2016/Data_v2* ../datasets/2016/Data_HIPM*")
# os.system("hadd ../datasets/2016/_DataPRE.root ../datasets/2016/Data_C* ../datasets/2016/Data_D* ../datasets/2016/Data_E* ../datasets/2016/Data_v2* ../datasets/2016/Data_HIPM*")
# os.system("hadd ../datasets/2016/_DataPOS.root ../datasets/2016/Data_F* ../datasets/2016/Data_G* ../datasets/2016/Data_H*")
# os.system("rm ../datasets/2016/_MC2016.root")
# os.system("hadd ../datasets/2016/_MC2016.root ../datasets/2016/_ttbarAPV.root ../datasets/2016/_ttbarPOS.root")




# os.system("rm ../datasets/2016/_MCPRE.root")
# os.system("rm ../datasets/2016/_MCPOS.root")
## os.system("hadd ../datasets/2016/_MCPRE.root ../datasets/2016/_DYPtInclusiveAPV.root ../datasets/2016/_ttbarAPV.root")
# os.system("hadd ../datasets/2016/_MCPOS.root ../datasets/2016/_DYPtInclusive.root ../datasets/2016/_ttbarPOS.root")
# os.system("rm ../datasets/2016/_DYPTBINNED.root")
# os.system("hadd ../datasets/2016/_DYPTBINNED.root ../datasets/2016/_DYPT_*")
#os.system("hadd ../datasets/2016/_MCPTBI.root ../datasets/2016/_DYPtInclusiveAPV.root ../datasets/2016/_ttbarAPV.root")
# os.system("hadd ../datasets/2016/_MCPOS.root ../datasets/2016/_DYPTBINNED.root ../datasets/2016/_ttbarPOS.root")

# # ##################################
# #------DADOS-2017---------------------------------------------------------------------------------
# os.system("root -q Conversion_Data_B_2017.C")
# os.system("root -q Conversion_Data_C_2017.C")
# os.system("root -q Conversion_Data_D_2017.C")
# os.system("root -q Conversion_Data_E_2017.C")
# os.system("root -q Conversion_Data_F_2017.C")
# #-----MC 2017-------------------------------------------------------------------------------------
# os.system("root -q Conversion_DY_HTinclu_2017.C")
# os.system("root -q Conversion_DY_Ptinclu_2017.C")
# os.system("root -q Conversion_ttbar_2017.C")
# #################################
# #JUNTANDO TODAS AS TREES DE DADOS EM UMA SO E TODAS AS TREES DE MC EM UMA SO
# os.system("rm ../datasets/2017/_Data.root")
# os.system("rm ../datasets/2017/_MCPT.root")
# os.system("rm ../datasets/2017/_MCHT.root")
# os.system("hadd ../datasets/2017/_Data.root ../datasets/2017/Data_*")
# os.system("hadd ../datasets/2017/_MCPT.root ../datasets/2017/_ttbar*")
# os.system("hadd ../datasets/2017/_MCHT.root ../datasets/2017/_DYHT.root ../datasets/2017/_ttbar.root")

# # ##################################
# #----DADOS 2018 -----------------------------------------------------------------------------------
# os.system("root -q Conversion_Data_A_2018.C")
# os.system("root -q Conversion_Data_B_2018.C")
# os.system("root -q Conversion_Data_C_2018.C")
# os.system("root -q Conversion_Data_D_2018.C")

# #-------MC 2018---------------------------------------------------------------------------------
# os.system("root -q Conversion_DY_HTinclu_2018.C")
# os.system("root -q Conversion_DY_Ptinclu_2018.C")
# os.system("root -q Conversion_ttbar_2018.C")


# #JUNTANDO TODAS AS TREES DE DADOS EM UMA SO E TODAS AS TREES DE MC EM UMA SO
# os.system("rm ../datasets/2018/_Data.root")
# os.system("rm ../datasets/2018/_MCPT.root")
# os.system("rm ../datasets/2018/_MCHT.root")
# os.system("hadd ../datasets/2018/_Data.root ../datasets/2018/Data_*")
# os.system("hadd ../datasets/2018/_MCPT.root ../datasets/2018/_ttbar.root")
# os.system("hadd ../datasets/2018/_MCHT.root ../datasets/2018/_DYHT.root ../datasets/2018/_ttbar.root")
#######################################################################################################################################################################################
#######################################################################################################################################################################################
#######################################################################################################################################################################################
###ETAPA DA EFICIENCIA DOS TRIGGERS
#-----------------------------------------2016--------------------------------------------------------
# RODANDO NOS DADOS, MAS EM ERAS SEPARADAS: C,D,E,F,G,H,HIPM_F e v2_B para erro SISTEMATICO (AINDA TENHO QUE CONFIRMAR)
# os.system("root -q 'trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_F.root\", \"true\", 2016)'")
# os.system("root -q 'trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_G.root\", \"true\", 2016)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data_H.root\", \"true\", 2016)'")
# PROS DADOS JUNTOS
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_Data2016.root\", \"true\", 2016)'")
# #DADOS POS
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_DataPOS.root\", \"true\", 2016)'")
# # #DADOS PRE
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_DataPRE.root\", \"true\", 2016)'")


# # ##RODANDO NO MC
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC2016/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_MC2016.root\", \"true\", 2016)'")
#ttbar
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/ttbar/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_ttbarPOS.root\", \"true\", 2016)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/ttbar_APV/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_ttbarAPV.root\", \"true\", 2016)'")
# # #DY
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DY/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_DYPtInclusive.root\", \"true\", 2016)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DY_APV/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_DYPtInclusiveAPV.root\", \"true\", 2016)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DYPTBI/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_DYPTBINNED.root\", \"true\", 2016)'")

# # MC_PRE_POS
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC_APV/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_MCPRE.root\", \"true\", 2016)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC_POS/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_MCPOS.root\", \"true\", 2016)'")


#-----------------------------------------2017----------------------------------------------------------
# #PROS DADOS JUNTOS
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_Data.root\", \"true\", 2017)'")
# #RODANDO NO MC
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_MCPT.root\", \"true\", 2017)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCHT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_MCHT.root\", \"true\", 2017)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/ttbar/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_ttbar.root\", \"true\", 2017)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/DYHT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_DYHT.root\", \"true\", 2017)'")
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/DYPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_DYPT.root\", \"true\", 2017)'")
#-----------------------------------------2018----------------------------------------------------------
################################################################
# #PROS DADOS JUNTOS
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_Data.root\", \"true\", 2018)'")
# #RODANDO NO MC
# os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_MCPT.root\", \"true\", 2018)'")
################################################################
#os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCHT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_MCHT.root\", \"true\", 2018)'")
#os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/ttbar/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_ttbar.root\", \"true\", 2018)'")
#os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/DYHT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_DYHT.root\", \"true\", 2018)'")
#os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/DYPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_DYPT.root\", \"true\", 2018)'")
#######################################################################################################################################################################################

#######################################################################################################################################################################################
#######################################################################################################################################################################################
###ETAPA DA PRODUCAO DE SCALE_FACTOR
#list_prefix = [""]
#list_prefix = ["","_NJETSHIGH","_NJETSLOW","_NPVHIGH","_NPVLOW","_METHIGH","_METLOW"]
# #list_dados_2016 = ["_F","_G","_H"]
#list_MC_2016 = ["_MC","_ttbarPOS","_ttbarAPV","_DYPtInclusiveAPV","_DYPtInclusive"]
# list_MC_2017 = ["_MC","_ttbar","_DYHT","_DYPT"]
# list_MC_2018 = ["_MC","_ttbar","_DYHT","_DYPT"]

#DY_2016 
# ---------------------
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPOS.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DYPTBI/MC/outfile_MCPTBI.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_DY2PT/\",1,\"\")'")
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPOS.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DYPTBI/MC/outfile_DYPTBINNED.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_DY2PT/\",1,\"\")'")
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPOS.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DY/MC/outfile_DYPtInclusive.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_DYPtInclusive/\",1,\"\")'")
# --------------------
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPRE.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/DY_APV/MC/outfile_DYPtInclusiveAPV.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_DYPtInclusiveAPV/\",1,\"\")'")
#ttbar_2016
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPOS.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/ttbar//MC/outfile_ttbarPOS.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_ttbarPOS/\",1,\"\")'")
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPRE.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/ttbar_APV/MC/outfile_ttbarAPV.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_ttbarAPV/\",1,\"\")'")
#MC_2016
###################################################################
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Data2016.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC2016/MC/outfile_MC2016.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_MC2016/\",1,\"\")'")
######################################################################
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPOS.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC_POS/MC/outfile_MCPOS.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_MCPOS/\",1,\"\")'")


# #MC_2017
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCHT/MC/outfile_MCHT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_MCHT/\",1,\"\")'")
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/MC/outfile_MCPT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_MCPT/\",1,\"\")'")
# #DY_2017
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/DYPT/MC/outfile_DYPT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_DYPT/\",1,\"\")'")
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/DYHT/MC/outfile_DYHT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_DYHT/\",1,\"\")'")
# #ttbar_2017
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/ttbar/MC/outfile_ttbar.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_ttbar/\",1,\"\")'")


#MC_2018
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCHT/MC/outfile_MCHT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data_MCHT/\",1,\"\")'")
# os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MCPT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data_MCPT/\",1,\"\")'")
#DY_2018
#os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/DYPT/MC/outfile_DYPT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data_DYPT/\",1,\"\")'")
#os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/DYHT/MC/outfile_DYHT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data_DYHT/\",1,\"\")'")
#ttbar_2018
#os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/ttbar/MC/outfile_ttbar.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data_ttbar/\",1,\"\")'")





# for u in list_MC_2016:    
#         os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPOS.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC/outfile"+u+".root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data"+u+"/\",1,\"\")'")
#         os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_DataPRE.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC/outfile"+u+".root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data"+u+"/\",1,\"\")'")
    #for x in list_prefix:
    #os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC/outfile_MC.root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_mc/\",1,\"\")'")
#     for u in list_MC_2018:
#         os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MC/outfile"+u+".root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data"+u+"/\",1,\"\")'")
#     for u in list_MC_2017:
#         os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MC/outfile"+u+".root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data"+u+"/\",1,\"\")'")        
    #DADOS DE 2016
    #os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Data.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC/outfile_MC.root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_mc/\",1,\"\")'")
    #for i in list_dados_2016:
        #for u in list_MC_2016:
            #os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile"+i+".root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC/outfile"+u+".root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data"+u+"/syst_lumi/\",0,\""+i+"\")'")


