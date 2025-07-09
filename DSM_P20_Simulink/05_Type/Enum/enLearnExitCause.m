%% Create enLearnExitCause enum

classdef enLearnExitCause < Simulink.IntEnumType

    enumeration
        enInvalid(0) 
        enRelayAdhesionFault(1)
        enHallFault(2)
        enOTA(3)
        enVehSpeed(4)
        enManualInterupt(5)
        enVoltFault(6)
        enLearnOverTime(7)
        enMotorRunOverTime_H(8)
        enMotorRunOverTime_L(9)
        enMotorRunOverTime_B(10)
        enMotorRunOverTime_F(11)
        enDescStop(12)
        enCfgW_ADJUST(13)
        enCfgW_MEMORY(14)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enLearnExitCause.enInvalid;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'enInvalid (��Ч)&#10;enRelayAdhesionFault���̵������ϣ�&#10;enHallFault���������ϣ�&#10;enOTA��OTA��&#10;enVehSpeed�����ٳ�����&#10;enManualInterupt���ֶ��жϣ�&#10;enVoltFault����ѹ���ϣ�&#10;enLearnOverTime(ѧϰ��ʱ)&#10;enMotorRunOverTime_H(�߶ȵ�����г�ʱ)&#10;enMotorRunOverTime_L(���������г�ʱ)&#10;enMotorRunOverTime_B(����������г�ʱ)&#10;enMotorRunOverTime_F(���е�����г�ʱ)&#10;enDescStop(���ֹͣ)&#10;,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
