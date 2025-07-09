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
            desc = 'enInvalid (无效)&#10;enRelayAdhesionFault（继电器故障）&#10;enHallFault（霍尔故障）&#10;enOTA（OTA）&#10;enVehSpeed（车速超过）&#10;enManualInterupt（手动中断）&#10;enVoltFault（电压故障）&#10;enLearnOverTime(学习超时)&#10;enMotorRunOverTime_H(高度电机运行超时)&#10;enMotorRunOverTime_L(坐垫电机运行超时)&#10;enMotorRunOverTime_B(靠背电机运行超时)&#10;enMotorRunOverTime_F(腿托电机运行超时)&#10;enDescStop(诊断停止)&#10;,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
