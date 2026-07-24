
"""def Edrv_Act_1(tp0,tp1,tp2,tp3,tp4,tp5,tp6,tp7):
    #TX (Transmitted from BRM)
    #Signal = [alias, startbit, lenght, scale, offset, minimum value, maximum value, unit]
    Edrv_nrChksAct = ['Checksum actual torque',0,8,1,0,0,255,'']
    Edrv_nrAlvCntrAct = ['Alive counter actual torque',8,4,1,0,0,15,'']
    Edrv_stRunAct = ['Actual run state',12,2,1,0,0,3,'']
    Edrv_stOperModAct = ['Actual operation mode',14,4,1,0,0,15,'']
    Edrv_tqAct = ['Actual torque',18,12,0.1,-200,-200,209.5,'Nm']
    Edrv_nAct = ['Actual speed',30,13,6,-24000,-24000,25146,'rpm']
    Edrv_uAct = ['Actual DC voltage',44,10,0.0625,0,0,63.9375,'V']
    Edrv_iAct = ['Actual DC current',54,10,1,-500,-500,523,'A']
    Edrv_Act_1_msg = [Edrv_nrChksAct,Edrv_nrAlvCntrAct,Edrv_stRunAct,Edrv_stOperModAct,Edrv_tqAct,Edrv_nAct,Edrv_uAct,Edrv_iAct]

    par_bin = [format((int(tp0,16)),'08b'),format((int(tp1,16)),'08b'),format((int(tp2,16)),'08b'),format((int(tp3,16)),'08b'),format((int(tp4,16)),'08b'),format((int(tp5,16)),'08b'),format((int(tp6,16)),'08b'),format((int(tp7,16)),'08b')]

    #Cria lista com os bits ordenados
    can_frame_matrix = []
    print (par_bin)
    for i in range(len(par_bin)):
        for n in range(-1,-9,-1):
            can_frame_matrix.append(par_bin[i][n])
    print (can_frame_matrix)
    print(len(can_frame_matrix))

    #Separa os bits de acordo com o tamanho de bits de cada sinal
    can_bin_data = []
    for i in range(len(Edrv_Act_1_msg)):
        bin_data = ''
        startbit = Edrv_Act_1_msg[i][1]
        finalbit = (startbit+Edrv_Act_1_msg[i][2])
        for n in range(startbit,finalbit):
            bin_data = bin_data + can_frame_matrix[n]
        can_bin_data.append(bin_data)
        bin_data = ''
    print(can_bin_data)
    
    #Converte a base de dados de binario para valores físicos
    can_physval_data=[]
    for i in range(len(Edrv_Act_1_msg)):
        physval = (int(can_bin_data[i],2)*Edrv_Act_1_msg[i][3])+Edrv_Act_1_msg[i][4]
        #can_physval_data.append(Edrv_Act_1_msg[i][0]+' = '+str(physval)+ Edrv_Act_1_msg[i][-1])
        can_physval_data.append([Edrv_Act_1_msg[i][0],physval])
    print(can_physval_data)
    
Edrv_Act_1('8E','87','32','FA','26','8E','BE','86')
"""
def Pt_Edrv_Des_1(rp_list):
    #RX (Received by BRM)
    #A entrada desta função deve ser uma lista no formato [[signal_name_1,value],[signal_name_2,value],...]
    n_sig = len(rp_list)
    #print(rp_list)

    #Signal = [alias, startbit, lenght, scale, offset, minimum value, maximum value, unit]
    Pt_nrChksAct = ['Checksum torque request',0,8,1,0,0,255,'']
    Pt_nrAlvCntrAct = ['Alive counter torque request',8,4,1,0,0,15,'']
    Pt_stOperModDesEdrv = ['Operation mode request',12,4,1,0,0,15,'']
    Pt_tqDesEdrv = ['Torque request & Maximum allowed torque',16,12,0.1,-200,-200,209.5,'Nm']
    Pt_tqMinEdrv = ['Minimum allowed torque',28,12,0.1,-200,-200,209.5,'Nm']
    Pt_nDesEdrv = ['Speed request',40,13,6,-24000,-24000,25146,'rpm']
    Pt_Edrv_Des_1_msg = [Pt_nrChksAct,Pt_nrAlvCntrAct,Pt_stOperModDesEdrv,Pt_tqDesEdrv,Pt_tqMinEdrv,Pt_nDesEdrv]

    #Converte os physical vales de cada sinal para binario
    can_bin_data = []
    for i in range(1):
        raw_dec_val = (rp_list[i][1]-Pt_Edrv_Des_1_msg[i][4])/(Pt_Edrv_Des_1_msg[i][3])
        bin_data = format(int(raw_dec_val),'0'+str(Pt_Edrv_Des_1_msg[i][2])+'b')
        can_bin_data.append(bin_data)
    print (can_bin_data)

    print(rp_list[0][1]-Pt_Edrv_Des_1_msg[0][4]/Pt_Edrv_Des_1_msg[0][3])
    print('0'+str(Pt_Edrv_Des_1_msg[0][2])+'b')
    

    #Separa os bits ordenados em uma lista
    can_frame_matrix = []
    for i in range(len(can_bin_data)):
        for n in range(len(can_bin_data[i])):
            b=str(can_bin_data[i][n])
            can_frame_matrix.append(b)
            b=''
    print (can_frame_matrix,len(can_frame_matrix))
    #Complementa com zeros para fechar os 64 bits
    while len(can_frame_matrix) < 64:
        can_frame_matrix.append('0')
    print (can_frame_matrix,len(can_frame_matrix))
    
    #Separa os bits em bytes na ordem do protocolo
    can_bin_data = []
    for i in range(7,len(can_frame_matrix),8):
        bin_data = ''
        for n in range(i,i-8,-1):
            bin_data = bin_data + str(can_frame_matrix[n])
        can_bin_data.append(bin_data)
    print(can_bin_data)

    #Converte os dados binários para hexadecimal
    can_hex_data = []
    for i in range(len(can_bin_data)):
        can_hex_data.append(hex(int(can_bin_data[i],2)))
    print(can_hex_data)

Pt_Edrv_Des_1([['Pt_nrChksAct',48],['Pt_nrAlvCntrAct',10],['Pt_stOperModDesEdrv',10],['Pt_tqDesEdrv',209],['Pt_tqMinEdrv',186],['Pt_nDesEdrv',11200]])
