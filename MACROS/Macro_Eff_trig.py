import os


type = 18

if (type == 16 or type == 'all'):
    #Criando os arquivos.root
    os.system("root -q Conversion_Data_C_2016.C")
    os.system("root -q Conversion_Data_D_2016.C")
    os.system("root -q Conversion_Data_E_2016.C")
    os.system("root -q Conversion_Data_F_2016.C")
    os.system("root -q Conversion_Data_G_2016.C")
    os.system("root -q Conversion_Data_H_2016.C")
    os.system("root -q Conversion_Data_HIPM_F_2016.C")
    os.system("root -q Conversion_Data_v2_B_2016.C")
    os.system("root -q Conversion_ttbar_2016.C")
    os.system("root -q Conversion_ttbar_APV_2016.C")
    # #juntando eles
    os.system("hadd -f ../datasets/2016/_Run2016Full.root ../datasets/2016/Run2016B* ../datasets/2016/Run2016G* ../datasets/2016/Run2016H* ../datasets/2016/Run2016C* ../datasets/2016/Run2016D* ../datasets/2016/Run2016E* ../datasets/2016/Run2016F1* ../datasets/2016/Run2016F2*")
    # os.system("rm ../datasets/2016/_MC2016.root")
    os.system("hadd -f ../datasets/2016/_MC2016.root ../datasets/2016/_ttbarAPV.root ../datasets/2016/_ttbarPOS.root")

    # # rodando o TriEffStudy.C
    os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_Run2016Full.root\", \"true\", 2016)'")
    os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC2016/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/_MC2016.root\", \"true\", 2016)'")

    # #criando os graficos
    os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Run2016Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC2016/MC/outfile_MC2016.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/\",1,\"_2016\")'")

    # list_varied_SF = ["_2016_NJETSHIGH","_2016_NJETSLOW","_2016_NPVHIGH","_2016_NPVLOW","_2016_METHIGH","_2016_METLOW"]
    # for x in list_varied_SF:
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2016\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/data/outfile_Data2016.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2016/MC2016/MC/outfile_MC2016.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_MC2016/\",1,\""+x+"\")'")
    # #criando os arquivos JSON
    # # os.system("root -q '../outputs_and_plotting_script/2016/data_MC2016/Writer_SF.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_MC2016/\")'")

    # os.system("root -q '../systCombiner.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/data_MC2016\")'")

if (type==17 or type == 'all'):

    os.system("root -q Conversion_Data_B_2017.C")
    os.system("root -q Conversion_Data_C_2017.C")
    os.system("root -q Conversion_Data_D_2017.C")
    os.system("root -q Conversion_Data_E_2017.C")
    os.system("root -q Conversion_Data_F_2017.C")
    os.system("root -q Conversion_ttbar_2017.C")
    # os.system("rm ../datasets/2017/_MCPT.root")
    os.system("hadd -f ../datasets/2017/_Run2017Full.root ../datasets/2017/Run2017*")
    os.system("hadd -f ../datasets/2017/_MC2017.root ../datasets/2017/_ttbar*")
  
    os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_Run2017Full.root\", \"true\", 2017)'")
    os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2017/_MC2017.root\", \"true\", 2017)'")

    # list_varied_SF = ["_2017_NJETSHIGH","_2017_NJETSLOW","_2017_NPVHIGH","_2017_NPVLOW","_2017_METHIGH","_2017_METLOW"]
    # for x in list_varied_SF:
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Run2017Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/MC/outfile_MCPT.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_MCPT/\",1,\""+x+"\")'")

    os.system("root -q 'draw_ScaleFactors_systematics.C(\"2017\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/data/outfile_Run2017Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2017/MCPT/MC/outfile_MC2017.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/\",1,\"_2017\")'")
    
    # os.system("root -q '../outputs_and_plotting_script/2017/Writer_SF.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/data_MCPT/\")'")


 




if (type == 18 or type == 'all'):
    # os.system("root -q Conversion_Data_A_2018.C")
    # os.system("root -q Conversion_Data_B_2018.C")
    # os.system("root -q Conversion_Data_C_2018.C")
    # os.system("root -q Conversion_Data_D_2018.C")
    # os.system("root -q Conversion_ttbar_2018.C")
    # os.system("hadd -f ../datasets/2018/_Run2018Full.root ../datasets/2018/_Run2018A.root ../datasets/2018/_Run2018B.root ../datasets/2018/_Run2018C.root ../datasets/2018/_Run2018D.root")
    # os.system("hadd -f ../datasets/2018/_MC2018.root ../datasets/2018/_ttbar.root")



    # os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_Run2018Full.root\", \"true\", 2018)'")
    # os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/\", \"true\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_MC2018.root\", \"true\", 2018)'")

    # os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",1,\"\")'")

    list_varied_SF = ["_NMu2"]
    for x in list_varied_SF:
        os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",1,\""+x+"\")'")

    # list_varied_SF = ["_NJETSHIGH","_NJETSLOW","_NPVHIGH","_NPVLOW","_METHIGH","_METLOW"]
    # for x in list_varied_SF:
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018Full.root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",1,\""+x+"\")'")

    # os.system("root -q '../outputs_and_plotting_script/2018/Writer_SF.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/data_MCPT/\")'")

    # list_eras = ['A','B','C','D']
    # for x in list_eras:
    #     os.system("root -q '../trigEffStudy.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/\", \"false\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2018/_Run2018"+x+".root\", \"true\", 2018)'")
    #     os.system("root -q 'draw_ScaleFactors_systematics.C(\"2018\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/data/outfile_Run2018"+x+".root\" ,\"/home/matheus/Desktop/tt-triggerEfficiency-DL/TriggerFiles_2018/MCPT/MC/outfile_MC2018.root\",\""+x+"\",\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/\",0,\"\")'")

    # os.system("root -q 'ScaleFactors_syst_lumi.C()'")
    # os.system("root -q '../systCombiner.C(\"/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018\")'")






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


